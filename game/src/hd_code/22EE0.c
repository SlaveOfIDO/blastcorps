#include "common.h"
#include "functions.h"
#include "macros.h"
#include "variables.h"
#include <PR/libaudio.h>
#include <PR/sched.h>

void func_hd_code_80261068();                          /* extern */
void func_hd_code_802611F0();                          /* extern */
void func_hd_code_80261284();                          /* extern */
void func_hd_code_802613C8();                          /* extern */
void func_hd_code_80261528();                          /* extern */

/**
 * @file audi.c
 * This file contains audio code. Starts main audio thread, handles some audio
 * DMA.
 *
 * This is heavily borrowed from the 007 decomp audi.c
 */
// Proposed file name: audio.c (the assert strings in this file reference
// "audio.c"). All functions here are already named (am* audio manager).
// Note: amMain also drives the music driver's per-frame state machines from
// the audio thread - the fade, tune push/pop, auto-pop and tempo-restore
// functions from 1C460.c run here, once per audio frame.

// 0x5622 = 22050
#define OUTPUT_RATE                    0x5622

#ifdef REFRESH_PAL
/* PAL */
#define MAYBE_FRAME_RATE                   50
#else
/* NTSC */
#define MAYBE_FRAME_RATE                   60
#endif


#define FRAMES_PER_FIELD_AS_POW2            1
#define AUDIO_FRAME_MESSAGE_QUEUE_SIZE      8
#define AUDIO_REPLY_MESSAGE_QUEUE_SIZE      8
#define AUDIO_DMA_IO_QUEUE_SIZE            72
#define AUDIO_DMA_QUEUE_SIZE               72
#define AUDIO_DMA_MAX_BUFFER_LENGTH     0x200

#define NUMBER_OUTPUT_BUFFERS               3
#define NUMBER_ACMD_LISTS                   2
#define MAX_ACMD_SIZE                    2750
#define NUMBER_DMA_BUFFERS                 72
#define EXTRA_SAMPLES                    0x25
#define AUDIO_FRAME_MESSAGE_QUEUE_SIZE      8
#define AUDIO_REPLY_MESSAGE_QUEUE_SIZE      8

#define MAIN_QUIT_MESSAGE                  10
#define AUDIO_MANAGER_COUNT_INTERVAL     0xf0

extern long long int rspbootTextStart[];
extern long long int gsp3DTextStart[];
extern long long int aspMainTextStart[];
extern long long int aspMainDataStart[];
extern u8 sp_audi[];

/**
 * Copied from the n64devkit audio examples.
 * sizeof(struct DMABuffer_s) == 0x14 (20)
 */
typedef struct DMABuffer_s {
    /**
     * 0x0.
     */
    ALLink node;

    /**
     * 0x8.
     */
    int startAddr;

    /**
     * 0xc.
     */
    u32 lastFrame;

    /**
     * 0x10.
     */
    u8* ptr;
} DMABuffer;

/**
 * Copied from the n64devkit audio examples.
 * sizeof(struct DMAState_s) == 0xc (12).
 */
typedef struct DMAState_s {
    /**
     * This was defined (in the devkit) as u8 (and code expects a byte), but the size
     * of the struct and offset for firstUsed seems to make this u32/s32.
     * I'm adding the union to make this explicit.
     * 0x0.
     */
    union {
        u8 initialized;
        s32 _unusedAlign;
    } u;

    /**
     * 0x4.
     */
    DMABuffer *firstUsed;

    /**
     * 0x8.
     */
    DMABuffer *firstFree;
} DMAState;

/**
 * Copied from the n64devkit audio examples.
 */
typedef union AudioMessage_u {
    struct {
        s16 type;
    } gen;

    struct {
        s16 type;
        struct AudioInfo_s *info;
    } done;

    OSScMsg app;
} AudioMessage;

/**
* Modified from n64devkit example.
* sizeof(struct _DMAState) == 0xc (12).
*/
typedef struct AudioInfo_s {
    /**
    * Output data pointer.
    * 0x0.
    */
    s16 *data;

    /**
     * # of samples synthesized in this frame
     * 0x4.
     */
    s16 frameSamples;

    /**
     * scheduler structure
     * 0x8
     */
    OSScTask task;
} AudioInfo;

// Data
u32 g_AudioFrameCount = 0;

u32 g_NextDMa = 0;

u32 g_CurrentAcmdList = 0;

/*
* This macro is used/defined in both libultra and libnaudio
*/
#define ms *(((s32)((f32)44.1)) & ~0x7)

#define CUSTOM_FX_SECTION_COUNT   8
#define CUSTOM_FX_SECTION_SIZE    8
/*
* Following the libultra and libnaudio naming convention ...
*/
s32 CUSTOM_FX_PARAMS_N[CUSTOM_FX_SECTION_COUNT * CUSTOM_FX_SECTION_SIZE + 2] = {

  //  sections	   length
             8,     170 ms,

  //                                           chorus  chorus   filter
  // input    output  fbcoef  ffcoef    gain     rate   depth    coef
      0 ms,     4 ms,   9830,  -9830, 0x0000,  0x0000,  0x00,  0x0000,
      4 ms,     8 ms,   9830,  -9830, 0x2b84,  0x0000,  0x00,  0x2500,
     20 ms,    64 ms,  16384, -16384, 0x11eb,  0x0000,  0x00,  0x3000,
     24 ms,    48 ms,   8192,  -8192, 0x0000,  0x0000,  0x00,  0x0000,
     80 ms,   140 ms,  16384, -16384, 0x11eb,  0x0000,  0x00,  0x3500,
     84 ms,   120 ms,   8192,  -8192, 0x0000,  0x0000,  0x00,  0x0000,
    120 ms,   136 ms,   8192,  -8192, 0x0000,  0x0000,  0x00,  0x0000,
      0 ms,   148 ms,  13000, -13000, 0x0000,  0x017c,  0x0a,  0x4500
};

s32 g_FirstTime = 1;

struct AudioManager_s {

    /**
     * 0.
     */
    Acmd *cmdList[NUMBER_ACMD_LISTS];

    /**
     * 0x8.
     */
    AudioInfo *audioInfo[NUMBER_OUTPUT_BUFFERS];

    /**
    * 0x14.
    */
    u32 numberOutputBuffers;

    /**
     * 0x18.
     */
    OSThread audioThread;

    /**
     * 0x1c8.
     */
    OSMesgQueue frameMessageQueue;

    /**
     * 0x1e0.
     */
    OSMesg frameMessageBuffer[AUDIO_FRAME_MESSAGE_QUEUE_SIZE];

    /**
     * 0x200.
     */
    OSMesgQueue replyMessageQueue;

    /**
     * 0x218.
     */
    OSMesg replyMessageBuffer[AUDIO_REPLY_MESSAGE_QUEUE_SIZE];

    /**
     * 0x238
     */
    ALGlobals g;

};

extern s32 osViClock;
extern s32 D_hd_code_803156A4;
extern s32 D_hd_code_8036772C;

// BSS Begin
u64 pad_80368050;
u64 D_80368058;
OSTime g_StartTime;
OSTime g_EndTime;
struct AudioManager_s g_AudioManager;
OSScClient g_AudioClient;
u8 D_80368308[0x2000]; // stack for amMain / also called sp_audi
DMAState g_DmaState;
DMABuffer g_DmaBuffers[NUMBER_DMA_BUFFERS];
u32 g_MinFrameSize;
s32 g_FrameSize;
u32 g_MaxFrameSize;
s32 g_CommandLength;
OSIoMesg g_DmaIOMessageBuffer[AUDIO_DMA_IO_QUEUE_SIZE];
OSMesgQueue g_DmaMessageQueue;
OSMesg g_DmaMessageBuffer[AUDIO_DMA_QUEUE_SIZE];
s32 D_hd_code_8036AFA0;
// BSS End

// Forward declarations
s32 amDmaCallback(s32 addr, s32 len, void* state);
void amClearDmaBuffers(void);
void amHandleFrameMessage(AudioInfo *info, AudioInfo *lastInfo);
void amHandleDoneMessage(AudioInfo *info);
void amMain(void* arg);
ALDMAproc amDmaNew(DMAState** state);

void amCreateAudioManager(ALSynConfig* alconf, s32 arg1) {
    s32 sp134;
    f32 sp130_fsize;
    s32 sp12C;

    alconf->dmaproc = amDmaNew;
    if (osTvType != 1) {
        osViClock = 0x02E6025C; // VI_MPAL_CLOCK ?
    }
    alconf->outputRate = osAiSetFrequency(OUTPUT_RATE);
    sp130_fsize = (f32) ((alconf->outputRate * 2.0f) / (f32)MAYBE_FRAME_RATE);
    g_FrameSize = sp130_fsize;

    if ((u32)g_FrameSize < sp130_fsize) {
        g_FrameSize++;
    }

    if (g_FrameSize & 0xF) {
        g_FrameSize = (g_FrameSize & ~0xF) + 0x10;
    }
    g_MinFrameSize = g_FrameSize - 0x10;
    g_MaxFrameSize = g_FrameSize + EXTRA_SAMPLES + 0x10;

    if (alconf->fxType == AL_FX_CUSTOM) {
        sp12C = 0;
        {
            s32 sp24[CUSTOM_FX_SECTION_COUNT * CUSTOM_FX_SECTION_SIZE + 2] = CUSTOM_FX_PARAMS_N;
            alconf->params = sp24;
            alInit(&g_AudioManager.g, alconf);
        }
    } else {
        alInit(&g_AudioManager.g, alconf);
    }
    g_DmaBuffers[0].node.prev = NULL;
    g_DmaBuffers[0].node.next = NULL;

    for (sp134=0; (s32)sp134 < NUMBER_DMA_BUFFERS - 1; sp134++)
    {
        alLink((ALLink*)&g_DmaBuffers[sp134+1], (ALLink*)&g_DmaBuffers[sp134]);
        g_DmaBuffers[sp134].ptr = (void*)alHeapDBAlloc(0, 0, alconf->heap, 1, AUDIO_DMA_MAX_BUFFER_LENGTH);
    }
    // last buffer already linked, but still needs buffer
    g_DmaBuffers[sp134].ptr = (void*)alHeapDBAlloc(0, 0, alconf->heap, 1, AUDIO_DMA_MAX_BUFFER_LENGTH);

    for (sp134=0; sp134 < NUMBER_ACMD_LISTS; sp134++)
    {
        g_AudioManager.cmdList[sp134] = (Acmd *)alHeapDBAlloc(0, 0, alconf->heap, 1, MAX_ACMD_SIZE * sizeof(Acmd));
    }

    for (sp134=0; sp134 < NUMBER_OUTPUT_BUFFERS; sp134++)
    {
        g_AudioManager.audioInfo[sp134] = (AudioInfo *)alHeapDBAlloc(0, 0, alconf->heap, 1, sizeof(AudioInfo));
        g_AudioManager.audioInfo[sp134]->data = (s16*)alHeapDBAlloc(0, 0, alconf->heap, 1, g_MaxFrameSize * 4);
    }

    osCreateMesgQueue(&g_AudioManager.replyMessageQueue, g_AudioManager.replyMessageBuffer, 8);
    osCreateMesgQueue(&g_AudioManager.frameMessageQueue, g_AudioManager.frameMessageBuffer, 8);
    osCreateMesgQueue(&g_DmaMessageQueue, g_DmaMessageBuffer, AUDIO_DMA_IO_QUEUE_SIZE);
    osCreateThread(&g_AudioManager.audioThread, 4, amMain, NULL, D_80368308 + 0x2000, arg1);
}

void amStartAudioThread(void)
{
  osStartThread(&g_AudioManager.audioThread);
}

void amMain(void* arg) {
    s32 sp3C;
    s32 sp38;
    AudioInfo* sp34;
    s32 sp30;

    sp3C = 0;
    sp34 = NULL;
    sp30 = 1;
    osScAddClient(&sc, &g_AudioClient, &g_AudioManager.frameMessageQueue, 2, 2);

    osSendMesg(&g_AudioManager.frameMessageQueue, (void* )5, 0);

    while (!sp3C) {
        osRecvMesg(&g_AudioManager.frameMessageQueue, (void*)&sp38, OS_MESG_BLOCK);
        switch (sp38) {                         /* irregular */
        case 4:
            break;
        case 5:
            if (sc.audioListHead != 0) {
                osSendMesg((OSMesgQueue* ) &sc, (void* )0x29E, 1);
            }
            g_StartTime = osGetTime();
            amHandleFrameMessage(g_AudioManager.audioInfo[g_AudioFrameCount % 3], sp34);
            g_EndTime = osGetTime();
            D_80368058 = g_StartTime;

            if (!sp30) {
                osRecvMesg(&g_AudioManager.replyMessageQueue, (void** ) &sp34, 1);
                amHandleDoneMessage(sp34);
            }
            sp30 = 0;
            if (D_hd_code_8036772A != 0) {
                func_hd_code_802613C8();
            }
            if (D_hd_code_80367728 != 0) {
                func_hd_code_80261068();
            }
            if (D_hd_code_80367729 != 0) {
                func_hd_code_80261284();
            }
            if ((u8) D_hd_code_80367730 == 0) {
                func_hd_code_802611F0();
            }
            if (D_hd_code_8036772C != 0) {
                func_hd_code_80261528();
            }
            break;
        case MAIN_QUIT_MESSAGE:
            sp3C = 1;
            break;
        case 6:
            rmonPrintf("No samples left\n");
            break;
        }
    }
    alClose(&g_AudioManager.g);
}

void amHandleFrameMessage(AudioInfo* info, AudioInfo* lastInfo) {
    s16* outBuffer;
    Acmd *cmdlp;
    u32 sp2C;
    OSScTask* task;

    sp2C = 0;
    amClearDmaBuffers();
    outBuffer = (s16*)osVirtualToPhysical(info->data);
    if (lastInfo != NULL) {
        osAiSetNextBuffer(lastInfo->data, lastInfo->frameSamples * 4);
    }
    sp2C = osAiGetLength() >> 2;
    info->frameSamples = ((g_FrameSize - sp2C) + 0x10 + EXTRA_SAMPLES) & ~0xF;
    if ((u32) info->frameSamples < (u32) g_MinFrameSize) {
        info->frameSamples = (s16) g_MinFrameSize;
    }
    cmdlp = alAudioFrame(g_AudioManager.cmdList[g_CurrentAcmdList], &g_CommandLength, outBuffer, info->frameSamples);
    if (g_CommandLength > MAX_ACMD_SIZE) {
        rmonPrintf(ASSERT_MESSAGE, "cmdLen <= MAX_RSP_CMDS", "audio.c", 0x150);
    }
    task = &info->task;
    info->task.next = NULL;
    task->msg = &g_AudioManager.replyMessageQueue;
    task->unk58 = (s32) info;
    task->flags = 1;
    task->msgQ = (OSMesgQueue* ) &g_AudioClient;
    task->list.t.data_ptr = (u64* ) g_AudioManager.cmdList[g_CurrentAcmdList];
    task->list.t.data_size = ((s32) ((s32)cmdlp - (s32)g_AudioManager.cmdList[g_CurrentAcmdList]) >> 3) * 8;
    task->list.t.type = 2;
    task->list.t.ucode_boot = (u64*)rspbootTextStart;
    task->list.t.ucode_boot_size = (s32)aspMainTextStart - (s32)rspbootTextStart;
    task->list.t.flags = 0;
    task->list.t.ucode = (u64*)aspMainTextStart;
    task->list.t.ucode_data = (u64*)aspMainDataStart;
    task->list.t.ucode_data_size = 0x800;
    task->list.t.yield_data_ptr = NULL;
    task->list.t.yield_data_size = 0;
    osWritebackDCache(task, 0x60);
    osWritebackDCache(task->list.t.data_ptr, (s32) task->list.t.data_size);
    if (osSendMesg(osScGetCmdQ(&sc), (OSMesg)task, OS_MESG_NOBLOCK) == -1) {
        rmonPrintf(ASSERT_MESSAGE, "osSendMesg(osScGetCmdQ(&sc), (OSMesg) t, OS_MESG_NOBLOCK)!=-1", "audio.c", 0x169);
    }
    g_CurrentAcmdList ^= 1;
}

void amHandleDoneMessage(AudioInfo* info) {
  u32 samplesLeft;

  samplesLeft = osAiGetLength() >> 2;
  if ((samplesLeft == 0) && (g_FirstTime == 0)) {
    rmonPrintf("audio: ai out of samples\n");
    g_FirstTime = 0;
  }
}

s32 amDmaCallback(s32 addr, s32 len, void* state) {
    void* freeBuffer;
    s32 delta;
    s32 addrEnd;
    s32 buffEnd;
    DMABuffer *dmaPtr;
    DMABuffer* lastDmaPtr;
    DMABuffer* prevDmaPtr;
    s32 sp28;

    sp28 = 0;
    lastDmaPtr = NULL;
    dmaPtr = g_DmaState.firstUsed;
    addrEnd = addr + len;
    delta = addr & 1;

    while (dmaPtr) {
        prevDmaPtr = dmaPtr;
        buffEnd = dmaPtr->startAddr + AUDIO_DMA_MAX_BUFFER_LENGTH;
        if ((u32) dmaPtr->startAddr > (u32) addr ) {
            break;
        }
        if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = g_AudioFrameCount;
            freeBuffer = (dmaPtr->ptr + addr) - dmaPtr->startAddr;
            return osVirtualToPhysical(freeBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (DMABuffer*)dmaPtr->node.next;
        sp28++;

    }

    if (sp28 > D_hd_code_8036AFA0) {
        D_hd_code_8036AFA0 = sp28;
    }
    dmaPtr = g_DmaState.firstFree;
    if (g_DmaState.firstFree == NULL) {
        rmonPrintf("OH DEAR - No audio DMA buffers left\n");
    }
    if (dmaPtr == NULL) {
        return osVirtualToPhysical(g_DmaState.firstUsed);
    }
    g_DmaState.firstFree = (DMABuffer*)dmaPtr->node.next;
    alUnlink((ALLink*)dmaPtr);
    if (lastDmaPtr) {
        alLink((ALLink*)dmaPtr, (ALLink*)lastDmaPtr);
    } else if (g_DmaState.firstUsed) {
        lastDmaPtr = g_DmaState.firstUsed;
        g_DmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink*)lastDmaPtr;
        dmaPtr->node.prev = NULL;
        lastDmaPtr->node.prev = (ALLink*)dmaPtr;
    } else {
        g_DmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
    }
    freeBuffer = dmaPtr->ptr;
    addr -= delta;

    dmaPtr->startAddr = (u32) addr;
    dmaPtr->lastFrame = (u32) g_AudioFrameCount;

    osPiStartDma(&g_DmaIOMessageBuffer[g_NextDMa++], OS_MESG_PRI_NORMAL, OS_READ, (u32) addr, freeBuffer, AUDIO_DMA_MAX_BUFFER_LENGTH, &g_DmaMessageQueue);
    return (s32)osVirtualToPhysical(freeBuffer) + delta;
}

ALDMAproc amDmaNew(DMAState** state)
{
  s32 pad;

  if (g_DmaState.u.initialized == 0)
  {
    g_DmaState.firstUsed = NULL;
    g_DmaState.firstFree = g_DmaBuffers;
    g_DmaState.u.initialized = (u8)1U;
  }

  *state = &g_DmaState;
  return &amDmaCallback;
}

void amClearDmaBuffers(void) {
  u32 i;
  OSMesg mesg;
  DMABuffer* dmaPtr;
  DMABuffer* nextPtr;

  for(i = 0; i < g_NextDMa; i++) {
    if (osRecvMesg(&g_DmaMessageQueue, &mesg, 0) == -1) {
      rmonPrintf("Dma not done\n");
    }
  }
  dmaPtr = g_DmaState.firstUsed;
  while (dmaPtr) {
    nextPtr = (DMABuffer*)dmaPtr->node.next;
    if ((u32) (dmaPtr->lastFrame + 1) < (u32) g_AudioFrameCount) {
      if (g_DmaState.firstUsed == dmaPtr) {
        g_DmaState.firstUsed = (DMABuffer*)dmaPtr->node.next;
      }
      alUnlink((ALLink*)dmaPtr);
      if (g_DmaState.firstFree != NULL) {
        alLink((ALLink*)dmaPtr, (ALLink*)g_DmaState.firstFree);
      } else {
        g_DmaState.firstFree = dmaPtr;
        dmaPtr->node.next = NULL;
        dmaPtr->node.prev = NULL;
      }
    }
    dmaPtr = nextPtr;
  }
  g_NextDMa = 0;
  g_AudioFrameCount += 1;
}

