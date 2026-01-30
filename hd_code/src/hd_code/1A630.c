#include <PR/libaudio.h>

#include "common.h"
#include "variables.h"
#include "snd.h"

ALMicroTime sndPlayerVoiceHandler(void *node);
void sndDisposeSound(ALSoundState*);                     /* extern */
void sndCreatePitchEvent(ALSoundState*);                     /* extern */
void sndRemoveEvents(ALEventQueue *evtq, ALSoundState *state, u16 eventType);
s32 sndCountAllocList(s16 *allocListCount, s16 *freeListCount);                /* extern */
void alSynStartVoice(ALSynth *s, ALVoice *voice, ALWaveTable *w);           /* extern */
void alSynSetPan(ALSynth *s, ALVoice *voice, ALPan pan);            /* extern */
void alSynSetPitch(ALSynth *s, ALVoice *voice, f32 ratio);           /* extern */
void alSynSetFXMix(ALSynth *s, ALVoice *voice, u8 fxmix);           /* extern */
ALSoundState *sndPlaySfx(struct ALBankAlt_s *soundBank, s16 soundIndex, ALSoundState *pendingState);
void sndHandleEvent(ALSndPlayer *sndp, ALSndpEvent *event);
ALSoundState *sndSetupSound(struct ALBankAlt_s *, ALSound *);            /* extern */
void sndCreatePostEvent(ALSoundState *state, s16 eventType, s32 arg2);
void sndUnlinkClearSound(ALSoundState *state);

extern ALSndPlayer *g_sndPlayerPtr;
extern s16* g_sndSfxSlotVolume;
extern s16 g_sndAllocatedVoicesCount;
ALLink D_hd_code_802E8CE0;
extern ALLink *D_hd_code_802E8CE8;

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

  D_hd_code_802E8CE8 = g_sndPlayerPtr->sndState;

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
                            tstate = (ALSoundState*)D_hd_code_802E8CE0.prev;
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

void sndDisposeSound(ALSoundState* state) {
  if (state->unk3e & 4)
  {
    alSynStopVoice(g_sndPlayerPtr->drvr, &state->voice);
    alSynFreeVoice(g_sndPlayerPtr->drvr, &state->voice);
  }

  sndUnlinkClearSound(state);
  sndRemoveEvents(&g_sndPlayerPtr->evtq, state, 0xffff);
}

void sndCreatePitchEvent(ALSoundState *state)
{
  ALSndpEvent evt;
  f32 pitch;

  pitch = (f32) (alCents2Ratio(state->sound->keyMap->detune) * (f32)state->pitch_2c.f);
  evt.pitch.state = state;
  evt.pitch.type = AL_SNDP_PITCH_EVT;

  // TODO: surely there's a better way to match target, especially since there's already a union type used with f32 for pitch.
  evt.unks32.val8 = *(s32*)&pitch;

  alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&evt, DELTA_33_MS);
}

void sndRemoveEvents(ALEventQueue *evtq, ALSoundState *state, u16 eventType)
{
  ALLink              *thisNode;
  ALLink              *nextNode;
  ALEventListItem     *thisItem;
  ALEventListItem     *nextItem;
  ALSndpEvent         *thisEvent;
  OSIntMask           mask;

  mask = osSetIntMask(OS_IM_NONE);

  thisNode = evtq->allocList.next;

  while(thisNode != NULL)
  {
    nextNode = thisNode->next;
    thisItem = (ALEventListItem *)thisNode;
    nextItem = (ALEventListItem *)nextNode;
    thisEvent = (ALSndpEvent *)&thisItem->evt;

    if (thisEvent->common.state == state && (((u16)thisItem->evt.type & (u16)eventType) != 0))
    {
      if (nextItem != NULL)
      {
        nextItem->delta += thisItem->delta;
      }

      alUnlink(thisNode);
      alLink(thisNode, &evtq->freeList);
    }

    thisNode = nextNode;
  }

  osSetIntMask(mask);
}

s32 sndCountAllocList(s16 *allocListCount, s16 *freeListCount)
{
  OSIntMask           mask;
  u16 i;
  u16 j;
  u16 k;
  ALLink *freeListNodeForward;
  ALLink *freeListNodeBackward;
  ALLink *allocListNodeForward;

  mask = osSetIntMask(OS_IM_NONE);

  freeListNodeForward = D_hd_code_802E8CE0.next;
  freeListNodeBackward =  D_hd_code_802E8CE8;
  allocListNodeForward =  D_hd_code_802E8CE0.prev;

  for (i = 0; freeListNodeForward != NULL; freeListNodeForward = freeListNodeForward->next)
  {
    i++;
  }


  for (j = 0; freeListNodeBackward != NULL; freeListNodeBackward = freeListNodeBackward->next)
  {
    j++;
  }

  for (k = 0; allocListNodeForward != NULL; allocListNodeForward = allocListNodeForward->prev)
  {
    k++;
  }


  *allocListCount = (s16) j;
  *freeListCount = (s16) i;

  osSetIntMask(mask);

  return k;
}

ALSoundState *sndSetupSound(struct ALBankAlt_s *soundBank, ALSound* sound)
{
  ALSoundState *state;
  ALKeyMap *keymap;
  s32 decayTimeFlag;
  OSIntMask mask;

  keymap = sound->keyMap;
  state = (ALSoundState *)D_hd_code_802E8CE8;

  if (state != NULL)
  {
    mask = osSetIntMask(OS_IM_NONE);

    D_hd_code_802E8CE8 = (void *)state->link.next;
    alUnlink(&state->link);

    if (D_hd_code_802E8CE0.next != NULL)
    {
      state->link.next = (void *)D_hd_code_802E8CE0.next;
      state->link.prev = NULL;
      D_hd_code_802E8CE0.next->prev = (void *)state;
      D_hd_code_802E8CE0.next = (void *)state;
    }
    else
    {
      state->link.prev = NULL;
      state->link.next = state->link.prev;
      D_hd_code_802E8CE0.next = (void *)state;
      D_hd_code_802E8CE0.prev = (void *)state;
    }



    decayTimeFlag = (sound->envelope->decayTime == -1);

    state->sound = sound;
    state->priority = decayTimeFlag + 0x40;
    state->playingState = AL_UNKOWN_5;
    state->pitch_2c.f = 1.0f;
    state->unk38 = 2;
    state->unk3e = (keymap->keyMax & (u8)0xf0);
    state->state = NULL;

    if ((state->unk3e & 0x20) != 0)
    {
      state->pitch_28 = alCents2Ratio(((keymap->keyBase * 100) + DEFAULT_SETUP_PITCH_SHIFT));
    }
    else
    {
      state->pitch_28 = alCents2Ratio((((keymap->keyBase * 100) + keymap->detune) + DEFAULT_SETUP_PITCH_SHIFT));
    }

    if (decayTimeFlag)
    {
      state->unk3e |= 2;
    }

    state->fxMix = (u8)AL_DEFAULT_FXMIX;
    state->pan = (u8)AL_PAN_CENTER;
    state->vol = (u16)0x7fff;

    osSetIntMask(mask);
  }

  return state;
}

void sndUnlinkClearSound(ALSoundState *state)
{
  if (state == (ALSoundState *)D_hd_code_802E8CE0.next)
  {
    D_hd_code_802E8CE0.next = state->link.next;
  }

  if (state == (ALSoundState *)D_hd_code_802E8CE0.prev)
  {
    D_hd_code_802E8CE0.prev = state->link.prev;
  }

  alUnlink(&state->link);

  if (D_hd_code_802E8CE8 != NULL)
  {
    state->link.next = D_hd_code_802E8CE8;
    state->link.prev = NULL;
    D_hd_code_802E8CE8->prev = (void *)state;
    D_hd_code_802E8CE8 = state;
  }
  else
  {
    state->link.prev = NULL;
    state->link.next = state->link.prev;
    D_hd_code_802E8CE8 = state;
  }

  if ((state->unk3e & 4) != 0)
  {
    g_sndAllocatedVoicesCount--;
  }

  state->playingState = AL_STOPPED;

  if (state->state != NULL)
  {
    if (state == (ALSoundState *)state->state->link.next)
    {
      state->state->link.next = NULL;
    }

    state->state = NULL;
  }
}

void sndSetPriority(ALSoundState *state, u8 priority)
{
  if (state != NULL)
  {
    state->priority = (s16)priority;
  }
}

u8 sndGetPlayingState(ALSoundState *state)
{
  if (state != NULL)
  {
    return state->playingState;
  }

  return AL_STOPPED;
}

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

void sndDeactivateAllSfxByFlag(u8 flag)
{
  OSIntMask mask;
  ALSndpEvent evt;
  ALSoundState *item;

  mask = osSetIntMask(OS_IM_NONE);

  item = (ALSoundState *)D_hd_code_802E8CE0.next;
  while (item != NULL)
  {
    evt.common.type = AL_SNDP_DEACTIVATE_EVT;
    evt.common.state = item;

    if ((item->unk3e & flag) == flag)
    {
      item->unk3e = (item->unk3e & (~(s16)(0x10)));
      alEvtqPostEvent(&g_sndPlayerPtr->evtq, (ALEvent *)&evt, 0);
    }

    item = (ALSoundState *)item->link.next;
  }

  osSetIntMask(mask);
}

void sndDeactivateAllSfxByFlag_1(void)
{
  sndDeactivateAllSfxByFlag(1);
}

void sndDeactivateAllSfxByFlag_11(void)
{
  sndDeactivateAllSfxByFlag(0x11);
}

void sndDeactivateAllSfxByFlag_3(void)
{
  sndDeactivateAllSfxByFlag(3);
}

void func_hd_code_80260A30(u8 arg0) {
  OSIntMask sp24;
  ALSoundState* sp20;
  s32 sp1C;

  sp24 = osSetIntMask(1U);
  sp1C = 0;
  for(sp20 = (ALSoundState*)D_hd_code_802E8CE0.next; sp20 != NULL; sp20 = sp20->link.next) {
    if ((sp20->sound->keyMap->keyMin & 0x3F) == arg0) {
      sndDeactivate(sp20);
    }
    sp1C += 1;
  }
  osSetIntMask(sp24);
}

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

u16 sndGetSfxSlotVolume(u8 sfxIndex)
{
  return g_sndSfxSlotVolume[sfxIndex];
}

void sndSetSfxSlotVolume(u8 arg0, u16 arg1) {
  OSIntMask sp34;
  ALSoundState* sp30;
  s32 sp2C;
  ALEvent event;

  sp34 = osSetIntMask(1U);
  sp30 = (ALSoundState*)D_hd_code_802E8CE0.next;
  g_sndSfxSlotVolume[arg0] = (s16) arg1;
  sp2C = 0;
  while (sp30 != NULL) {
    if ((sp30->sound->keyMap->keyMin & 0x3F) == arg0) {
      event.type = 0x800;
      event.msg.spseq.seq = sp30;
      alEvtqPostEvent(&g_sndPlayerPtr->evtq, &event, 0);
    }
    sp2C += 1;
    sp30 = sp30->link.next;
  }
  osSetIntMask(sp34);
}