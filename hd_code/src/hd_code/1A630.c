#include <PR/libaudio.h>

#include "common.h"
#include "variables.h"
#include "snd.h"

ALMicroTime sndPlayerVoiceHandler(void *node);
void sndDisposeSound(ALSoundState*);                     /* extern */
void sndCreatePitchEvent(ALSoundState*);                     /* extern */
void sndRemoveEvents(ALEventQueue *evtq, ALSoundState *state, u16 eventType);           /* extern */
s32 sndCountAllocList(s16 *allocListCount, s16 *freeListCount);                /* extern */
void alSynStartVoice(ALSynth *s, ALVoice *voice, ALWaveTable *w);           /* extern */
void alSynSetPan(ALSynth *s, ALVoice *voice, ALPan pan);            /* extern */
void alSynSetPitch(ALSynth *s, ALVoice *voice, f32 ratio);           /* extern */
void alSynSetFXMix(ALSynth *s, ALVoice *voice, u8 fxmix);           /* extern */
ALSoundState *sndPlaySfx(struct ALBankAlt_s *soundBank, s16 soundIndex, ALSoundState *pendingState);
void sndHandleEvent(ALSndPlayer *sndp, ALSndpEvent *event);
ALSoundState *sndSetupSound(struct ALBankAlt_s *, ALSound *);            /* extern */
void sndCreatePostEvent(ALSoundState *state, s16 eventType, s32 arg2);

extern struct S_802E8CE8 D_hd_code_802E8CE0;
extern ALSndPlayer *g_sndPlayerPtr;
extern s16* g_sndSfxSlotVolume;
extern struct S_802E8CE4 D_hd_code_802E8CE4;
extern s16 g_sndAllocatedVoicesCount;

void sndNewPlayerInit(ALSeqpSfxConfig *sfxSeqpConfig)
{
  u32 i;
  u8 *ptr;
  ALEvent evt;
  struct ALSoundState_s *sState;

  /*
   * Init member variables
   */
  g_sndPlayerPtr->maxSounds = sfxSeqpConfig->maybeMaxSounds;
  g_sndPlayerPtr->target = 0;
  g_sndPlayerPtr->frameTime = AL_USEC_PER_FRAME_30FPS;
  ptr = alHeapAlloc(sfxSeqpConfig->heap, 1, sfxSeqpConfig->maybeSndStateCount * sizeof(struct ALSoundState_s));
  g_sndPlayerPtr->sndState = ptr;

  /*
   * init the event queue
   */
  ptr = alHeapAlloc(sfxSeqpConfig->heap, 1, sfxSeqpConfig->maxEvents * sizeof(ALEventListItem));
  alEvtqNew(&g_sndPlayerPtr->evtq, (ALEventListItem *)ptr, sfxSeqpConfig->maxEvents);

  D_hd_code_802E8CE0.g_sndPlayerSoundStatePtr = g_sndPlayerPtr->sndState;

  for(i = 1; i < sfxSeqpConfig->maybeSndStateCount; i++)
  {
    // The compiler says this reassignment matters ...
    sState = (struct ALSoundState_s*)g_sndPlayerPtr->sndState;

    // this works because `ALLink node` is at offset zero.
    alLink((ALLink*)(&sState[i]), (ALLink*)(&sState[i]-1));
  }

  g_sndSfxSlotVolume = alHeapAlloc(sfxSeqpConfig->heap, sizeof(s16), sfxSeqpConfig->slotCount);

  for(i = 0; i < sfxSeqpConfig->slotCount; i++)
  {

    g_sndSfxSlotVolume[i] = (s16)0x7FFF;
  }

  /*
   * add ourselves to the driver
   */
  g_sndPlayerPtr->drvr = &alGlobals->drvr;
  g_sndPlayerPtr->node.next = NULL;
  g_sndPlayerPtr->node.handler = &sndPlayerVoiceHandler;
  g_sndPlayerPtr->node.clientData = g_sndPlayerPtr;
  alSynAddPlayer(g_sndPlayerPtr->drvr, &g_sndPlayerPtr->node);

  /*
   * Start responding to API events
   */
  evt.type = AL_SNDP_API_EVT;
  alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&evt, g_sndPlayerPtr->frameTime);
  g_sndPlayerPtr->nextDelta = alEvtqNextEvent(&g_sndPlayerPtr->evtq, &g_sndPlayerPtr->nextEvent);
}


/**
 * 89DC    70007DDC
 *
 * Almost identical to \n64devkit\ultra\usr\src\pr\libsrc\libultra\audio\sndplayer.c
 * method ALMicroTime _sndpVoiceHandler(void *node).
 */
ALMicroTime sndPlayerVoiceHandler(void *node)
{
  ALSndPlayer *sndp = (ALSndPlayer *) node;
  ALSndpEvent evt;

  do
  {
    switch (sndp->nextEvent.type)
    {
      case (AL_SNDP_API_EVT):
        evt.common.type = (s16)AL_SNDP_API_EVT;
        alEvtqPostEvent(&sndp->evtq, (ALEvent *)&evt, sndp->frameTime);
        break;

      default:
        sndHandleEvent(sndp, (ALSndpEvent *)&sndp->nextEvent);
        break;
    }

    sndp->nextDelta = alEvtqNextEvent(&sndp->evtq, &sndp->nextEvent);

  } while (sndp->nextDelta == 0);

  sndp->curTime += sndp->nextDelta;

  return sndp->nextDelta;
}


void sndHandleEvent(ALSndPlayer *sndp, ALSndpEvent *event)
{
    ALVoiceConfig vc;                   // sp 0xa8
    ALSound *snd;                       // sp 0xa4
    ALKeyMap *keyMap;                   // sp 0xa0
    s32 sp9C;                           // sp 0x9c
    ALPan pan;                          // sp 0x9b
    ALSndpEvent stopEvent;              // sp 0x8c
    ALSndpEvent evt;                    // sp 0x7c
    ALMicroTime delta;                  // sp 0x74
    s32 sp70;                           // sp 0x70
    s32 sp6c;                           // sp 0x6c
    s32 sp68;                           // sp 0x68
    s32 compare_result;                 // sp 0x64
    s32 msgtype;                        // sp 0x60
    s32 done_state;                     // sp 0x5c
    s32 sp58;                           // sp 0x58
    s32 allocVoiceSuccess;              // sp 0x54
    ALSoundState *state;                // sp 0x50
    ALSoundState *nextState;            // sp 0x4c
    u16 sp4A;                           // sp 0x4A
    u16 sp48;                           // sp 0x48
    ALSoundState *tstate;               // sp 0x44
    ALEvent playAllocEvent;             // sp 0x38
    ALSoundState *sp30;                 // sp 0x30

    sp9C = 0;
    done_state = 1;
    allocVoiceSuccess = 0;
    nextState = NULL;

    while (1)
    {
        if (nextState)
        {
            evt.common.state = state;
            evt.common.type = event->common.type;
            evt.unks32.val8 = event->unks32.val8;
            event = (ALSndpEvent *)&evt;
        }

        state = event->common.state;
        snd = state->sound;

        if (snd == NULL)
        {
            sndCountAllocList(&sp4A, &sp48);
            func_hd_code_8029A7E4("Bad soundState: voices =%d, states free =%d, states busy =%d, type %d data %x\n", g_sndAllocatedVoicesCount, sp4A, sp48, (s32) event->common.type, event->playSfx.soundIndex);
            return;
        }

        keyMap = snd->keyMap;
        nextState = (ALSoundState *)state->link.next;

        switch (event->common.type)
        {
            case (AL_SNDP_PLAY_EVT):
            {
                if ((state->playingState == AL_UNKOWN_5) || (state->playingState == AL_UNKOWN_4))
                {
                    if (state->playingState == 1) {
                        func_hd_code_8029A7E4("playing a playing sound\n");
                    }

                    // comment copied from sndplayer: effect buss 0
                    vc.fxBus = 0;
                    vc.priority = state->priority;
                    vc.unityPitch = 0;
                    //voice = &state->voice;

                    compare_result = ((s32)g_sndAllocatedVoicesCount >= sndp->maxSounds);

                    if ((!compare_result) || (state->unk3e & 0x50))
                    {
                        allocVoiceSuccess = alSynAllocVoice(sndp->drvr, &state->voice, &vc);
                    }

                    if (!allocVoiceSuccess)
                    {
                        if ((state->unk3e & 0x52) || (state->unk38 > 0))
                        {
                            state->playingState = AL_UNKOWN_4;
                            state->unk38--;
                            alEvtqPostEvent(&sndp->evtq, (ALEvent*)event, DELTA_33_MS);

                            return;
                        }

                        if (compare_result)
                        {
                            tstate = (ALSoundState*)D_hd_code_802E8CE4.node.next;
                            do
                            {
                                if (!(tstate->unk3e & 0x52)
                                    && (tstate->unk3e & 4)
                                    && (tstate->playingState != AL_UNKOWN_3))
                                {
                                    compare_result = 0;

                                    playAllocEvent.type = AL_SNDP_END_EVT;
                                    playAllocEvent.msg.spbank.bank = tstate; // or something similar
                                    tstate->playingState = AL_UNKOWN_3;



                                    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&playAllocEvent, DELTA_1_MS);
                                    alSynSetVol(sndp->drvr, (ALVoice*)&tstate->voice, 0, DELTA_1_MS);


                                }

                                tstate = (ALSoundState *)tstate->link.prev;
                            }
                            while (compare_result != 0 && tstate != NULL);

                            if (compare_result == 0)
                            {
                                state->unk38 = 2;
                                alEvtqPostEvent(&sndp->evtq, (ALEvent*)event, DELTA_1_MS + 1);
                                return;
                            }

                            sndDisposeSound(state);
                            return;
                        }

                        sndDisposeSound(state);
                        return;
                    }

                    state->unk3e = state->unk3e | 4;
                    alSynStartVoice(sndp->drvr, &state->voice, snd->wavetable);

                    state->playingState = AL_PLAYING;
                    g_sndAllocatedVoicesCount++;

                    delta = (ALMicroTime)((f32)snd->envelope->attackTime / state->pitch_2c.f / state->pitch_28);

                    if (((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->attackVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) <= 0) {
                        sp6c = 0;
                    } else {
                        sp6c = ((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->attackVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) - 1;
                    }

                    alSynSetVol(sndp->drvr, &state->voice, 0, 0);
                    alSynSetVol(sndp->drvr, &state->voice, sp6c, delta);

                    sp68 = state->pan - AL_PAN_CENTER + snd->samplePan;
                    pan = (ALPan) MIN(MAX(sp68, AL_PAN_LEFT), AL_PAN_RIGHT);
                    //pan = (ALPan) MIN(MAX(state->pan - AL_PAN_CENTER + snd->samplePan, AL_PAN_LEFT), AL_PAN_RIGHT);

                    alSynSetPan(sndp->drvr, &state->voice, pan);
                    alSynSetPitch(sndp->drvr, &state->voice, state->pitch_2c.f * state->pitch_28);

                    sp70 = (state->fxMix + (keyMap->keyMax & 0xf)) * 8;
                    sp70 = MIN(AL_VOL_FULL, MAX(AL_DEFAULT_FXMIX, sp70));
                    alSynSetFXMix(sndp->drvr, &state->voice, sp70);

                    stopEvent.common.type = AL_SNDP_DECAY_EVT;
                    stopEvent.common.state = state;
                    delta = (ALMicroTime)((f32)snd->envelope->attackTime / state->pitch_2c.f / state->pitch_28);
                    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&stopEvent, delta);
                }
                else
                {
                    return;
                }
            }
            break;

            case (AL_SNDP_DEACTIVATE_EVT): // fallthrough
            case (AL_SNDP_UNKNOWN_12_EVT): // fallthrough
            case (AL_SNDP_STOP_EVT):
            {
                if (event->common.type != AL_SNDP_UNKNOWN_12_EVT
                    || (state->unk3e & 0x2)
                )
                {
                    switch (state->playingState)
                    {
                        case (AL_PLAYING):
                        {
                            sndRemoveEvents(&sndp->evtq, state, AL_SNDP_DECAY_EVT);

                            delta = (ALMicroTime)((f32)snd->envelope->releaseTime / state->pitch_28 / state->pitch_2c.f);
                            alSynSetVol(sndp->drvr, (ALVoice *)&state->voice, 0, delta);

                            if (delta)
                            {
                                stopEvent.common.type = AL_SNDP_END_EVT;
                                stopEvent.common.state = state;
                                alEvtqPostEvent(&sndp->evtq, (ALEvent *)&stopEvent, delta);
                                state->playingState = AL_STOPPING;
                            }
                            else
                            {
                                sndDisposeSound(state);
                            }
                        }
                        break;

                        case (AL_UNKOWN_4): // fallthrough
                        case (AL_UNKOWN_5):
                        {
                            sndDisposeSound(state);
                        }
                        break;

                        default:
                            // nothing to do
                        break;
                    }

                    if (event->common.type == AL_SNDP_STOP_EVT)
                    {
                        event->common.type = AL_SNDP_UNKNOWN_12_EVT;
                    }
                }
            }
            break;

            case (AL_SNDP_PAN_EVT):
            {
                state->pan = event->pan32.pan32;

                if (state->playingState == AL_PLAYING)
                {
                    sp68 = state->pan - AL_PAN_CENTER + snd->samplePan;
                    pan = (ALPan) MIN(MAX(sp68, AL_PAN_LEFT), AL_PAN_RIGHT);
                    alSynSetPan(sndp->drvr, &state->voice, pan);
                }
            }
            break;

            case (AL_SNDP_PITCH_EVT):
            {
                state->pitch_2c.f = event->pitch.pitch;

                if (state->playingState == AL_PLAYING)
                {
                    alSynSetPitch(sndp->drvr, &state->voice, state->pitch_2c.f * state->pitch_28);

                    if (state->unk3e & 0x20)
                    {
                        sndCreatePitchEvent(state);
                    }
                }
            }
            break;

            case (AL_SNDP_FX_EVT):
            {
                state->fxMix = event->fx32.mix32;

                if (state->playingState == AL_PLAYING)
                {
                    sp70 = (state->fxMix + (keyMap->keyMax & 0xf)) * 8;
                    sp70 = MIN(AL_VOL_FULL, MAX(AL_DEFAULT_FXMIX, sp70));


                    alSynSetFXMix(sndp->drvr, &state->voice, sp70);
                }
            }
            break;

            case (AL_SNDP_VOL_EVT):
            {
                state->vol = event->vol.vol;
                if (state->playingState == AL_PLAYING)
                {
                    if (((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->decayVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) <= 0) {
                        sp6c = 0;
                    } else {
                        sp6c = ((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->decayVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) - 1;
                    }
                    alSynSetVol(sndp->drvr, (ALVoice *)&state->voice, sp6c, DELTA_1_MS);
                }
            }
            break;

            // case 0x20 (AL_SNDP_API_EVT)
            // handled in sndPlayerVoiceHandler

            case (AL_SNDP_RELEASE_EVT):
            {
                if (state->playingState == AL_PLAYING)
                {
                    delta = ((f32)snd->envelope->releaseTime / state->pitch_28 / state->pitch_2c.f);

                    if (((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->decayVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) <= 0) {
                        sp6c = 0;
                    } else {
                        sp6c = ((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->decayVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) - 1;
                    }
                    alSynSetVol(sndp->drvr, &state->voice, sp6c, delta);
                }
            }
            break;

            case (AL_SNDP_DECAY_EVT):
            {
                if ((state->unk3e & 2) == 0)
                {
                    if (((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->decayVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) <= 0) {
                        sp6c = 0;
                    } else {
                        sp6c = ((s32) (g_sndSfxSlotVolume[keyMap->keyMin & 0x3F] * ((s32) (snd->envelope->decayVolume * state->vol * snd->sampleVolume) / 16129)) / 32767) - 1;
                    }

                    delta = (ALMicroTime)((f32)snd->envelope->decayTime / state->pitch_28 / state->pitch_2c.f);
                    alSynSetVol(sndp->drvr, &state->voice, sp6c, delta);

                    stopEvent.common.type = AL_SNDP_STOP_EVT;
                    stopEvent.common.state = state;
                    alEvtqPostEvent(&sndp->evtq, (ALEvent *)&stopEvent, delta);

                    if ((state->unk3e & 0x20) != 0)
                    {
                        sndCreatePitchEvent(state);
                    }
                }
            }
            break;

            case (AL_SNDP_END_EVT):
            {
                sndDisposeSound(state);
            }
            break;

            case (AL_SNDP_PLAY_SFX_EVT):
            {
                if ((state->unk3e & 0x10) != 0)
                {
                    sp30 = sndPlaySfx((struct ALBankAlt_s *)event->playSfx.soundBank, event->playSfx.soundIndex, state->state);
                    sndCreatePostEvent(sp30, 8, state->vol);
                    sndCreatePostEvent(sp30, 4, state->pan);
                    sndCreatePostEvent(sp30, 0x100, state->fxMix);
                    sndCreatePostEvent(sp30, 0x10, state->pitch_2c.s);

                }
            }
            break;

            default:
                func_hd_code_8029A7E4("Nonsense sndp event\n");
            break;
        }

        msgtype = event->common.type & 0x2d1;
        state = nextState;

        if (state != NULL && msgtype == 0)
        {
            done_state = nextState->unk3e & 0x1;
        }

        if (done_state || state == NULL)
        {
            break;
        }
        else if (msgtype == 0)
        {
            continue;
        }
        else
        {
            break;
        }
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndDisposeSound.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndCreatePitchEvent.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndRemoveEvents.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndCountAllocList.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndSetupSound.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndUnlinkClearSound.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndSetPriority.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/sndGetPlayingState.s")

ALSoundState *sndPlaySfx(struct ALBankAlt_s *soundBank, s16 sndId, ALSoundState *pendingState) {
    ALSoundState *newState;  // sp 0x54
    ALSoundState *nextState; // sp 0x50
    ALKeyMap *keyMap;        // sp 0x4C
    ALSound *sound;          // sp 0x48
    s16 eventSndId;          // sp 0x46
    ALMicroTime playSfxDelta; // sp 0x40
    ALMicroTime deltaLoop;
    ALMicroTime deltaTotal;

    nextState = NULL;
    eventSndId = 0;
    deltaTotal = 0;

    if ((sndId == 0) || ((D_hd_code_80358060 == 0) && (sndId == 0xC)) || (((sndId == 0x14) || (sndId == 0x15)) && ((levelno == 0x26) || (levelno == 0x31)))) {
        return 0;
    }

    do
    {


        sound = (soundBank->instArray[0]->soundArray[sndId]);

        newState = sndSetupSound(soundBank, sound);

        if (newState != NULL)
        {
            ALSndpEvent playEvent;

            g_sndPlayerPtr->target = (s32)newState;
            playEvent.common.type = AL_SNDP_PLAY_EVT;
            playEvent.common.state = newState;
            deltaLoop = sound->keyMap->velocityMax * DELTA_33_MS;

            if (newState->unk3e & 0x10)
            {
                newState->unk3e &= (~(s16)(0x10));
                alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&playEvent, deltaTotal + 1);
                playSfxDelta = deltaLoop + 1;
                eventSndId = sndId;
            }
            else
            {
                alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&playEvent, deltaLoop + 1);
            }

            nextState = newState;
        } else {
            func_hd_code_8029A7E4("Sound state allocate failed - sndId %d\n", sndId);
        }

        deltaTotal += deltaLoop;

        keyMap = sound->keyMap;
        sndId = (s16)((s32)keyMap->velocityMin + ((s32)(keyMap->keyMin & 0xC0) * 4));
    } while (sndId != 0 && newState != NULL);

    if (nextState != NULL)
    {
        nextState->unk3e |= 0x1;
        nextState->state = pendingState;

        if (eventSndId != 0)
        {
            ALSndpEvent playSfxEvent;

            nextState->unk3e |= 0x10;

            playSfxEvent.playSfx.type = AL_SNDP_PLAY_SFX_EVT;
            playSfxEvent.playSfx.state = nextState;
            playSfxEvent.playSfx.soundIndex = eventSndId; // types dont match
            playSfxEvent.playSfx.soundBank = soundBank;

            alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&playSfxEvent, playSfxDelta);
        }
    }

    if (pendingState != NULL)
    {
        pendingState->link.next = (void*)nextState;
    }

    return nextState;
}

void sndDeactivate(ALSoundState *state)
{
  ALSndpEvent evt;

  evt.common.type = AL_SNDP_DEACTIVATE_EVT;
  evt.common.state = state;

  if (state != NULL)
  {
    state->unk3e = state->unk3e & (~(u16)(0x10));

    alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&evt, 0);
  } else
  {
    func_hd_code_8029A7E4("WARNING: Attempt to stop NULL sound aborted\n");
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_80260934.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_802609D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_802609F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_80260A10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_80260A30.s")

void sndCreatePostEvent(ALSoundState *state, s16 eventType, s32 arg2) {
  ALSndpEvent evt;

  evt.common.type = eventType;
  evt.common.state = state;
  evt.unks32.val8 = arg2;

  if (state != NULL)
  {
    alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&evt, 0);
    return;
  }
  func_hd_code_8029A7E4("WARNING: Attempt to modify NULL sound aborted\n");
}

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_80260B24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/hd_code/1A630/func_hd_code_80260B40.s")