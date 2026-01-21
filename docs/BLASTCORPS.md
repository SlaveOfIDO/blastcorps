# Blast Corps Decompilation Documentation

BlastCorps uses libultra 2.0D and F3D Beta.

libultra 2.0D is stated as a version string in the ROM binary and exceptasm has no __osPiIntTable.
This ROM uses F3D Beta (f3db) because gSPPerspNormalize is used in the F3D Beta version.

## Symbols

labels:
- [0x80000308, "osRomBase"]
- [0x8001C700, "n_alSeqpDelete"]
- [0x8002E480, "n_alSynFreeFX"]
- [0x80056024, "osSyncPrintf"]
- [0x8008FA90, "osPiRawReadIo"]
- [0x8008FAF0, "osCreateThread"]
- [0x8008FC40, "osStartThread"]
- [0x8008FD90, "osDpSetStatus"]
- [0x8008FDA0, "osCreatePiManager"]
- [0x8008FF20, "osSetThreadPri"]
- [0x80090000, "osSendMesg"]
- [0x80090150, "osRecvMesg"]
- [0x80090290, "osViBlack"]
- [0x80090300, "osGetTime"]
- [0x800903BC, "__ull_rem"]
- [0x800903F8, "__ull_div"]
- [0x80090434, "__ll_lshift"]
- [0x8009049C, "__ll_div"]
- [0x800904F8, "__ll_mul"]
- [0x80090528, "__ull_divremi"]
- [0x80090588, "__ll_mod"]
- [0x80090624, "__ll_rshift"]
- [0x80090650, "n_alSeqpGetState"]
- [0x80090660, "osVirtualToPhysical"]
- [0x80090760, "guTranslateF"]
- [0x800907A8, "guTranslate"]
- [0x80090800, "guOrthoF"]
- [0x80090954, "guFrustum"]
- [0x800909C0, "guPerspectiveF"]
- [0x80090BF0, "guPerspective"]
- [0x80090C50, "guRotateF"]
- [0x80090DE4, "guAlign"]
- [0x80090EE0, "guMtxCatF"]
- [0x80091150, "guMtxIdentF"]
- [0x800911D8, "guMtxIdent"]
- [0x80091208, "guMtxL2F"]
- [0x800912C0, "guScaleF"]
- [0x80091314, "guRotateRPY"]
- [0x80091360, "guLookAtReflectF"]
- [0x800917A0, "guLookAtReflect"]
- [0x80091830, "guLookAtF"]
- [0x80091AE8, "guLookAt"]
- [0x80091B60, "__sinf"]
- [0x80091D20, "osCreateMesgQueue"]
- [0x80091D90, "osViSetSpecialFeatures"]
- [0x80092030, "osDestroyThread"]
- [0x800922A0, "sprintf"]
- [0x800923B0, "alEvtqFlushType"]
- [0x8009245C, "alEvtqFlush"]
- [0x800924CC, "alEvtqPostEvent"]
- [0x800925F0, "alEvtqNextEvent"]
- [0x8009267C, "alEvtqNew"]
- [0x800926F0, "alUnlink"]
- [0x80092720, "alLink"]
- [0x80092744, "alClose"]
- [0x8009277C, "alInit"]
- [0x800927B0, "alSynAddPlayer"]
- [0x80092800, "_allocatePVoice"]
- [0x800928E8, "alSynAllocVoice"]
- [0x80092A30, "alSynSetVol"]
- [0x80092AD0, "alSynStartVoice"]
- [0x80092B60, "alSynSetPan"]
- [0x80092BF0, "alSynSetPitch"]
- [0x80092C80, "alSynSetFXMix"]
- [0x80092D20, "alSynStopVoice"]
- [0x80092DA0, "alSynFreeVoice"]
- [0x80092E50, "alCents2Ratio"]
- [0x80092EA0, "osSetIntMask"]
- [0x80092F00, "alSeqpStop"]
- [0x80092F30, "alCSeqGetLoc"]
- [0x80092FD0, "alCSeqSetLoc"]
- [0x8009318C, "__dummy"]
- [0x80093194, "alCSeqNextEvent"]
- [0x8009348C, "alCSeqNew"]
- [0x800935A0, "alCSeqNewMarker"]
- [0x8009370C, "alSeqGetTicks"]
- [0x80093714, "alCSeqSecToTicks"]
- [0x80093810, "alCSeqTicksToSec"]
- [0x8009387C, "__alCSeqNextDelta"]
- [0x800939F0, "alSeqpSetSeq"]
- [0x80093A30, "alSeqpPlay"]
- [0x80093A60, "alSeqpSetVol"]
- [0x80093AE0, "alSeqpSetTempo"]
- [0x80093CA4, "alBnkfNew"]
- [0x80093DA8, "alSeqFileNew"]
- [0x80093DF0, "__CSPPostNextSeqEvent"]
- [0x80094EB0, "alCSPNew"]
- [0x80095020, "alSeqpSetBank"]
- [0x800950E0, "coss"]
- [0x800953A0, "osAiSetNextBuffer"]
- [0x80095468, "_timeToSamples"]
- [0x800954C0, "_freePVoice"]
- [0x800954F8, "_collectPVoices"]
- [0x80095558, "__freeParam"]
- [0x80095570, "__allocParam"]
- [0x80095830, "alSynNew"]
- [0x80095B30, "osPiStartDma"]
- [0x80095C5C, "__f_to_ll"]
- [0x80095C78, "__d_to_ull"]
- [0x80095D18, "__f_to_ull"]
- [0x80095DB4, "__ll_to_d"]
- [0x80095DCC, "__ll_to_f"]
- [0x80095DE4, "__ull_to_d"]
- [0x80095E18, "__ull_to_f"]
- [0x800961B0, "osViSetMode"]
- [0x80096220, "osSetEventMesg"]
- [0x80096290, "osViSetEvent"]
- [0x80096310, "osViGetCurrentFramebuffer"]
- [0x80096390, "osViSwapBuffer"]
- [0x800963E0, "osSetTimer"]
- [0x800964C0, "osSpTaskYielded"]
- [0x8009665C, "osSpTaskLoad"]
- [0x800967BC, "osSpTaskStartGo"]
- [0x80096800, "osSpTaskYield"]
- [0x80096820, "guMtxXFML"]
- [0x80096880, "guMtxCatL"]
- [0x80096ADC, "__osContGetInitData"]
- [0x80096BAC, "__osPackRequestData"]
- [0x80096CA0, "osContSetCh"]
- [0x80096D10, "osContStartReadData"]
- [0x80096DD4, "osContGetReadData"]
- [0x80097090, "osContStartQuery"]
- [0x80097114, "osContGetQuery"]
- [0x80097140, "guNormalize"]
- [0x800971E0, "__osGetSR"]
- [0x80097200, "__osSpRawReadIo"]
- [0x80097250, "__osSpRawWriteIo"]
- [0x800979B8, "__osPopThread"]
- [0x800979C8, "__osDispatchThread"]
- [0x80097B90, "__osRestoreInt"]
- [0x80097BF0, "__osSiCreateAccessQueue"]
- [0x80097C40, "__osSiGetAccess"]
- [0x80097C84, "__osSiRelAccess"]
- [0x80097CB0, "osGetThreadPri"]
- [0x80097CD0, "osPiRawStartDma"]
- [0x80097DB0, "__osDevMgrMain"]
- [0x80097FBC, "__osTimerInterrupt"]
- [0x80098134, "__osSetTimerIntr"]
- [0x800981A8, "__osInsertTimer"]
- [0x80098330, "__osProbeTLB"]
- [0x800983F0, "_Printf"]
- [0x800995AC, "strlen"]
- [0x800995D4, "strchr"]
- [0x80099704, "__resetPerfChanState"]
- [0x80099784, "__initFromBank"]
- [0x80099840, "__vsDelta"]
- [0x80099864, "__vsVol"]
- [0x800998EC, "__seqpReleaseVoice"]
- [0x80099A18, "__voiceNeedsNoteKill"]
- [0x80099AC0, "__unmapVoice"]
- [0x80099B30, "__postNextSeqEvent"]
- [0x80099C84, "__vsPan"]
- [0x80099CCC, "__lookupVoice"]
- [0x80099D40, "__mapVoice"]
- [0x80099DB0, "__lookupSoundQuick"]
- [0x8009ACF0, "__seqpStopOsc"]
- [0x8009ADF4, "__initChanState"]
- [0x8009AE64, "alSeqpNew"]
- [0x8009AFF0, "alSynStartVoiceParams"]
- [0x8009B0E0, "__osViSwapContext"]
- [0x8009B470, "alSaveNew"]
- [0x8009B4B4, "alMainBusNew"]
- [0x8009B508, "alAuxBusNew"]
- [0x8009B55C, "alResampleNew"]
- [0x8009B5E4, "alLoadNew"]
- [0x8009B68C, "alEnvmixerNew"]
- [0x8009B730, "init_lpfilter"]
- [0x8009BBF0, "alSynAllocFX"]
- [0x8009BCC0, "alMainBusPull"]
- [0x8009BDE0, "alLoadParam"]
- [0x8009BFB4, "alRaw16Pull"]
- [0x8009C48C, "alAdpcmPull"]
- [0x8009CA1C, "alResamplePull"]
- [0x8009CC58, "_frexpf"]
- [0x8009CD44, "alEnvmixerParam"]
- [0x8009D840, "alAuxBusPull"]
- [0x8009D954, "alSavePull"]
- [0x8009D9E0, "osJamMesg"]
- [0x8009DB30, "osPiGetCmdQueue"]
- [0x8009DB48, "MusPtrBankGetCurrent"]
- [0x8009DEE0, "__osSpRawStartDma"]
- [0x8009DFA0, "__osSiRawStartDma"]
- [0x8009E110, "__osSiDeviceBusy"]
- [0x8009E3D8, "kdebugserver"]
- [0x8009E5C0, "__osSyncPutChars"]
- [0x8009E700, "_Litob"]
- [0x8009EA00, "_Ldtob"]
- [0x8009F7D0, "alSeqGetLoc"]
- [0x8009F7EC, "alSeqSetLoc"]
- [0x8009F864, "alSeqNextEvent"]
- [0x8009F9E8, "alSeqNewMarker"]
- [0x8009FB08, "alSeqSecToTicks"]
- [0x8009FBEC, "alSeqTicksToSec"]
- [0x8009FC40, "__alSeqNextDelta"]
- [0x8009FD18, "alSeqNew"]
- [0x8009FDF0, "alSynSetPriority"]
- [0x8009FE00, "alFilterNew"]
- [0x8009FEC8, "_filterBuffer"]
- [0x8009FF80, "_saveBuffer"]
- [0x800A0108, "_loadBuffer"]
- [0x800A0294, "_loadOutputBuffer"]
- [0x800A06D0, "alFxParam"]
- [0x800A06E8, "alFxPull"]
- [0x800A0A40, "__osAtomicDec"]
- [0x800A0AA0, "lldiv"]
- [0x800A0BA0, "ldiv"]
- [0x80260DFC, "n_alSynRemovePlayer"]
- [0x802D42B0, "osCreateThread"]
- [0x802D4400, "osStartThread"]
- [0x802D46E0, "osSetThreadPri"]
- [0x802D47C0, "osSendMesg"]
- [0x802D4910, "osRecvMesg"]
- [0x802D4B7C, "__ull_rem"]
- [0x802D4BB8, "__ull_div"]
- [0x802D4C5C, "__ll_div"]
- [0x802D4CB8, "__ll_mul"]
- [0x802D4E20, "osVirtualToPhysical"]
- [0x802D4EA0, "osWritebackDCache"]
- [0x802D4FC0, "guFrustumF"]
- [0x802D5180, "guPerspectiveF"]
- [0x802D5410, "guAlignF"]
- [0x802D5600, "guMtxXFMF"]
- [0x802D56A0, "guMtxCatF"]
- [0x802D5810, "guMtxF2L"]
- [0x802D5910, "guMtxIdentF"]
- [0x802D59C8, "guMtxL2F"]
- [0x802D5A80, "guRotateRPYF"]
- [0x802D5B20, "guLookAtReflectF"]
- [0x802D5FE0, "sqrtf"]
- [0x802D5FF0, "guLookAtF"]
- [0x802D6320, "sinf"]
- [0x802D64E0, "osCreateMesgQueue"]
- [0x802D6740, "osInvalDCache"]
- [0x802D68F0, "cosf"]
- [0x802D6ACC, "sprintf_text_006C"]
- [0x802D6B10, "alHeapDBAlloc"]
- [0x802D6C8C, "alEvtqPostEvent"]
- [0x802D6E3C, "alEvtqNew"]
- [0x802D6EB0, "alUnlink"]
- [0x802D6EE0, "alLink"]
- [0x802D6F70, "alSynAddPlayer"]
- [0x802D6FC0, "_allocatePVoice"]
- [0x802D71F0, "alSynSetVol"]
- [0x802D7660, "osSetIntMask"]
- [0x802D7830, "cseq_text_0140"]
- [0x802D78F4, "cseq_text_0204"]
- [0x802D7954, "alCSeqNextEvent"]
- [0x802D7C4C, "alCSeqNew"]
- [0x802D803C, "__alCSeqNextDelta"]
- [0x802D8370, "bnkf_text_0010"]
- [0x802D905C, "csplayer_text_0A90"]
- [0x802D9820, "osGetCount"]
- [0x802D9830, "sins"]
- [0x802D9C28, "_timeToSamples"]
- [0x802D9C80, "_freePVoice"]
- [0x802D9D30, "__allocParam"]
- [0x802D9FF0, "alSynNew"]
- [0x802DA9E0, "osSetEventMesg"]
- [0x802DAD00, "sptask_text_0000"]
- [0x802DB29C, "__osContGetInitData"]
- [0x802DB36C, "__osPackRequestData"]
- [0x802DB63C, "contreaddata_text_017C"]
- [0x802DB900, "guNormalize"]
- [0x802DC0A0, "__osEnqueueAndYield"]
- [0x802DC130, "__osEnqueueThread"]
- [0x802DC178, "__osPopThread"]
- [0x802DC188, "__osDispatchThread"]
- [0x802DC2C8, "__osCleanupThread"]
- [0x802DC330, "__osDisableInt"]
- [0x802DC350, "__osRestoreInt"]
- [0x802DC370, "__osDequeueThread"]
- [0x802DC3B0, "__osPiCreateAccessQueue"]
- [0x802DC470, "osGetThreadPri"]
- [0x802DC490, "osPiRawStartDma"]
- [0x802DC570, "__osDevMgrMain"]
- [0x802DC8F4, "__osSetTimerIntr"]
- [0x802DC968, "__osInsertTimer"]
- [0x802DCAF0, "__osProbeTLB"]
- [0x802DCBB0, "_Printf"]
- [0x802DD3DC, "xprintf_text_082C"]
- [0x802DDD40, "memcpy"]
- [0x802DDD94, "strchr"]
- [0x802DDDE0, "alCopy"]
- [0x802DDE60, "alSynDelete"]
- [0x802DDE70, "__setInstChanState"]
- [0x802DDEC4, "__resetPerfChanState"]
- [0x802DEE8C, "seqplayer_text_101C"]
- [0x802DF5B4, "__initChanState"]
- [0x802DFC00, "__osAiDeviceBusy"]
- [0x802DFC30, "alSaveNew"]
- [0x802DFC74, "alMainBusNew"]
- [0x802DFCC8, "alAuxBusNew"]
- [0x802DFD1C, "alResampleNew"]
- [0x802DFDA4, "alLoadNew"]
- [0x802DFE4C, "alEnvmixerNew"]
- [0x802DFF90, "alFxNew"]
- [0x802E03B0, "alSynAllocFX"]
- [0x802E0450, "alMainBusParam"]
- [0x802E0480, "alMainBusPull"]
- [0x802E05A0, "alLoadParam"]
- [0x802E0774, "alRaw16Pull"]
- [0x802E0B20, "load_text_0580"]
- [0x802E0C4C, "alAdpcmPull"]
- [0x802E10F0, "alResampleParam"]
- [0x802E11DC, "alResamplePull"]
- [0x802E1504, "alEnvmixerParam"]
- [0x802E194C, "alEnvmixerPull"]
- [0x802E1FD0, "alAuxBusParam"]
- [0x802E2000, "alAuxBusPull"]
- [0x802E20E0, "alSaveParam"]
- [0x802E2114, "alSavePull"]
- [0x802E21A0, "osJamMesg"]
- [0x802E22F0, "osPiGetCmdQueue"]
- [0x802E2330, "__osSpGetStatus"]
- [0x802E2650, "__osSpSetStatus"]
- [0x802E2660, "__osSpSetPc"]
- [0x802E26A0, "__osSpRawStartDma"]
- [0x802E2730, "__osSpDeviceBusy"]
- [0x802E2760, "__osSiRawStartDma"]
- [0x802E2860, "__osSiGetAccess"]
- [0x802E28A4, "__osSiRelAccess"]
- [0x802E28D0, "__osSiDeviceBusy"]
- [0x802E2B20, "kdebugserver_text_0220"]
- [0x802E2B6C, "kdebugserver_text_026C"]
- [0x802E2EB0, "__osSetCompare"]
- [0x802E37C0, "xldtob_text_0600"]
- [0x802E38A0, "xldtob_text_06E0"]
- [0x802E3FAC, "alSeqSetLoc"]
- [0x802E3FC8, "alSeqGetTicks"]
- [0x802E3FD8, "seq_text_0048"]
- [0x802E4024, "alSeqNextEvent"]
- [0x802E4400, "__alSeqNextDelta"]
- [0x802E4458, "seq_text_04AC"]
- [0x802E44A8, "seq_text_04FC"]
- [0x802E45B0, "alSynSetPriority"]
- [0x802E45C0, "alFilterNew"]
- [0x802E45E0, "_doModFunc"]
- [0x802E4688, "_filterBuffer"]
- [0x802E4740, "_saveBuffer"]
- [0x802E48C8, "_loadBuffer"]
- [0x802E4A54, "_loadOutputBuffer"]
- [0x802E4E90, "alFxParam"]
- [0x802E51F0, "__osGetCause"]
- [0x802E5200, "__osAtomicDec"]
- [0x802E5260, "lldiv"]
- [0x802E5360, "ldiv"]
- [0x803065A0, "__osPiDevMgr"]
- [0x803065A8, "player_bss_003C"]
- [0x803065C0, "alGlobals"]
- [0x80306E30, "__osViCurr"]
- [0x80306E34, "__osViNext"]
- [0x80306E40, "aisetnextbuf_data_0000"]
- [0x80307768, "__osRunQueue"]
- [0x8030776C, "__osActiveQueue"]
- [0x80307770, "__osRunningThread"]
- [0x80307780, "__osPiAccessQueueEnabled"]
- [0x80307790, "__osTimerList"]
- [0x803077A0, "xprintf_data_0000"]
- [0x803077C4, "xprintf_data_0024"]
- [0x80307B30, "kdebugserver_data_0000"]
- [0x80307B34, "kdebugserver_data_0004"]
- [0x80307B38, "kdebugserver_data_0008"]
- [0x80307B44, "__osRdbWriteOK"]
- [0x80307B50, "xlitob_data_0000"]
- [0x80307B64, "xlitob_data_0014"]
- [0x8030D9F0, "perspective_rodata_0000"]
- [0x8030DA00, "rotate_rodata_0000"]
- [0x8030DA10, "lookatref_rodata_0000"]
- [0x8030DA20, "sinf_rodata_0000"]
- [0x8030DA48, "sinf_rodata_0028"]
- [0x8030DA50, "sinf_rodata_0030"]
- [0x8030DA58, "sinf_rodata_0038"]
- [0x8030DA60, "sinf_rodata_0040"]
- [0x8030DAC0, "cents2ratio_rodata_0000"]
- [0x8030DAC4, "cents2ratio_rodata_0004"]
- [0x8030DAD0, "__osRcpImTable"]
- [0x8030DB50, "cseq_rodata_0000"]
- [0x8030DB58, "cseq_rodata_0008"]
- [0x8030DC60, "__osViCurr"]
- [0x8030DC68, "__osViNext"]
- [0x8030DDA0, "synthesizer_rodata_0000"]
- [0x8030DDB0, "llcvt_rodata_0000"]
- [0x8030DDB8, "llcvt_rodata_0008"]
- [0x8030DE10, "__libm_qnan_f"]
- [0x8030DE20, "xprintf_rodata_0000"]
- [0x8030DE24, "xprintf_rodata_0004"]
- [0x8030DE2C, "xprintf_rodata_000C"]
- [0x8030E1B8, "resample_rodata_0028"]
- [0x8030E1C0, "resample_rodata_0030"]
- [0x8030E2F0, "xldtob_rodata_0000"]
- [0x8030E338, "xldtob_rodata_0048"]
- [0x8030E33C, "xldtob_rodata_004C"]
- [0x8030E348, "xldtob_rodata_0058"]
- [0x8030E350, "seq_rodata_0000"]
- [0x8030E358, "seq_rodata_0008"]
- [0x8030EEC0, "__osThreadTail"]
- [0x80313104, "__osPiDevMgr"]
- [0x803FCD90, "pimgr_bss_0000"]
- [0x803FCF40, "pimgr_bss_01B0"]
- [0x803FDF40, "pimgr_bss_11B0"]
- [0x803FDF58, "pimgr_bss_11C8"]
- [0x803FDF60, "rotate_bss_0000"]
- [0x803FE4BC, "__osContPifRam"]
- [0x803FE624, "__osCurrentTime"]
- [0x803FF180, "__osEventStateTab"]
- [0x803FF240, "__osContPifRam"]
- [0x803FF280, "__osContLastCmd"]
- [0x803FF281, "__osMaxControllers"]
- [0x803FF2D0, "siacs_bss_0000"]
- [0x803FF2D8, "__osPiAccessQueue"]
- [0x803FF318, "__osBaseCounter"]
- [0x803FF320, "__osTimerCounter"]
- [0x803FF350, "kdebugserver_bss_0000"]


80000308 osRomBase
80220714 osSyncPrintf
80220BA0 _bzero
80220E70 osPiRawStartDma
80220F50 osPiGetStatus
80220F70 __osGetSR
80220F90 __osSpRawReadIo
80220FE0 __osSpRawWriteIo
80221748 __osPopThread
80221758 __osDispatchThread
80221A8C __ull_rem
80221AC8 __ull_div
80221B04 __ll_lshift
80221B6C __ll_div
80221BC8 __ll_mul
80221BF8 __ull_divremi
80221C58 __ll_mod
80221CF4 __ll_rshift
80221D60 osVirtualToPhysical
80221DE0 __osSpDeviceBusy
80222030 kdebugserver_text_0220
8022207C kdebugserver_text_026C
802220A8 kdebugserver
80222290 __osDequeueThread
802222D0 __osSyncPutChars
80222400 osSetEventMesg
802224D0 osDestroyThread
802225D0 __osProbeTLB
80222690 __osGetCause
802226A0 __osAtomicDec
80222700 __osDisableInt
80222720 __osRestoreInt
80222890 kdebugserver_data_0000
80222894 kdebugserver_data_0004
80222898 kdebugserver_data_0008
802228A8 __osRunQueue
802228AC __osActiveQueue
802228B0 __osRunningThread
802228C4 __osRdbWriteOK
80222960 __osRcpImTable
80224A50 kdebugserver_bss_0000
80224D00 __osEventStateTab
80260DFC n_alSynRemovePlayer
802D42B0 osCreateThread
802D4400 osStartThread
802D46E0 osSetThreadPri
802D47C0 osSendMesg
802D4910 osRecvMesg
802D4B7C __ull_rem
802D4BB8 __ull_div
802D4C5C __ll_div
802D4CB8 __ll_mul
802D4E20 osVirtualToPhysical
802D4EA0 osWritebackDCache
802D4FC0 guFrustumF
802D5180 guPerspectiveF
802D5410 guAlignF
802D5600 guMtxXFMF
802D56A0 guMtxCatF
802D5810 guMtxF2L
802D5910 guMtxIdentF
802D59C8 guMtxL2F
802D5A80 guRotateRPYF
802D5B20 guLookAtReflectF
802D5FE0 sqrtf
802D5FF0 guLookAtF
802D6320 sinf
802D64E0 osCreateMesgQueue
802D6740 osInvalDCache
802D68F0 cosf
802D6ACC sprintf_text_006C
802D6B10 alHeapDBAlloc
802D6C8C alEvtqPostEvent
802D6E3C alEvtqNew
802D6EB0 alUnlink
802D6EE0 alLink
802D6F70 alSynAddPlayer
802D6FC0 _allocatePVoice
802D71F0 alSynSetVol
802D7660 osSetIntMask
802D7830 cseq_text_0140
802D78F4 cseq_text_0204
802D7954 alCSeqNextEvent
802D7C4C alCSeqNew
802D803C __alCSeqNextDelta
802D8370 bnkf_text_0010
802D905C csplayer_text_0A90
802D9820 osGetCount
802D9830 sins
802D9C28 _timeToSamples
802D9C80 _freePVoice
802D9D30 __allocParam
802D9FF0 alSynNew
802DA9E0 osSetEventMesg
802DAD00 sptask_text_0000
802DB29C __osContGetInitData
802DB36C __osPackRequestData
802DB63C contreaddata_text_017C
802DB900 guNormalize
802DC0A0 __osEnqueueAndYield
802DC130 __osEnqueueThread
802DC178 __osPopThread
802DC188 __osDispatchThread
802DC2C8 __osCleanupThread
802DC330 __osDisableInt
802DC350 __osRestoreInt
802DC370 __osDequeueThread
802DC3B0 __osPiCreateAccessQueue
802DC470 osGetThreadPri
802DC490 osPiRawStartDma
802DC570 __osDevMgrMain
802DC8F4 __osSetTimerIntr
802DC968 __osInsertTimer
802DCBB0 _Printf
802DD3DC xprintf_text_082C
802DDD40 memcpy
802DDD94 strchr
802DDDE0 alCopy
802DDE60 alSynDelete
802DDE70 __setInstChanState
802DDEC4 __resetPerfChanState
802DEE8C seqplayer_text_101C
802DF5B4 __initChanState
802DFC00 __osAiDeviceBusy
802DFC30 alSaveNew
802DFC74 alMainBusNew
802DFCC8 alAuxBusNew
802DFD1C alResampleNew
802DFDA4 alLoadNew
802DFE4C alEnvmixerNew
802DFF90 alFxNew
802E03B0 alSynAllocFX
802E0450 alMainBusParam
802E0480 alMainBusPull
802E05A0 alLoadParam
802E0774 alRaw16Pull
802E0B20 load_text_0580
802E0C4C alAdpcmPull
802E10F0 alResampleParam
802E11DC alResamplePull
802E1504 alEnvmixerParam
802E194C alEnvmixerPull
802E1FD0 alAuxBusParam
802E2000 alAuxBusPull
802E20E0 alSaveParam
802E2114 alSavePull
802E21A0 osJamMesg
802E22F0 osPiGetCmdQueue
802E2330 __osSpGetStatus
802E2650 __osSpSetStatus
802E2660 __osSpSetPc
802E26A0 __osSpRawStartDma
802E2730 __osSpDeviceBusy
802E2760 __osSiRawStartDma
802E2860 __osSiGetAccess
802E28A4 __osSiRelAccess
802E28D0 __osSiDeviceBusy
802E2EB0 __osSetCompare
802E37C0 xldtob_text_0600
802E38A0 xldtob_text_06E0
802E3FAC alSeqSetLoc
802E3FC8 alSeqGetTicks
802E3FD8 seq_text_0048
802E4024 alSeqNextEvent
802E4400 __alSeqNextDelta
802E4458 seq_text_04AC
802E44A8 seq_text_04FC
802E45B0 alSynSetPriority
802E45C0 alFilterNew
802E45E0 _doModFunc
802E4688 _filterBuffer
802E4740 _saveBuffer
802E48C8 _loadBuffer
802E4A54 _loadOutputBuffer
802E4E90 alFxParam
802E5260 lldiv
802E5360 ldiv
803065A0 __osPiDevMgr
803065A8 player_bss_003C
803065C0 alGlobals
80306E30 __osViCurr
80306E34 __osViNext
80306E40 aisetnextbuf_data_0000
80307768 __osRunQueue
8030776C __osActiveQueue
80307770 __osRunningThread
80307780 __osPiAccessQueueEnabled
80307790 __osTimerList
803077A0 xprintf_data_0000
803077C4 xprintf_data_0024
80307B50 xlitob_data_0000
80307B64 xlitob_data_0014
8030D9F0 perspective_rodata_0000
8030DA00 rotate_rodata_0000
8030DA10 lookatref_rodata_0000
8030DA20 sinf_rodata_0000
8030DA48 sinf_rodata_0028
8030DA50 sinf_rodata_0030
8030DA58 sinf_rodata_0038
8030DA60 sinf_rodata_0040
8030DAC0 cents2ratio_rodata_0000
8030DAC4 cents2ratio_rodata_0004
8030DAD0 __osRcpImTable
8030DB50 cseq_rodata_0000
8030DB58 cseq_rodata_0008
8030DC60 __osViCurr
8030DC68 __osViNext
8030DDA0 synthesizer_rodata_0000
8030DDB0 llcvt_rodata_0000
8030DDB8 llcvt_rodata_0008
8030DE10 __libm_qnan_f
8030DE20 xprintf_rodata_0000
8030DE24 xprintf_rodata_0004
8030DE2C xprintf_rodata_000C
8030E1B8 resample_rodata_0028
8030E1C0 resample_rodata_0030
8030E2F0 xldtob_rodata_0000
8030E338 xldtob_rodata_0048
8030E33C xldtob_rodata_004C
8030E348 xldtob_rodata_0058
8030E350 seq_rodata_0000
8030E358 seq_rodata_0008
8030EEC0 __osThreadTail
80313104 __osPiDevMgr
803FCD90 pimgr_bss_0000
803FCF40 pimgr_bss_01B0
803FDF40 pimgr_bss_11B0
803FDF58 pimgr_bss_11C8
803FDF60 rotate_bss_0000
803FE4BC __osContPifRam
803FE624 __osCurrentTime
803FF240 __osContPifRam
803FF280 __osContLastCmd
803FF281 __osMaxControllers
803FF2D0 siacs_bss_0000
803FF2D8 __osPiAccessQueue
803FF318 __osBaseCounter
803FF320 __osTimerCounter
80A3A400 n_alSeqpDelete
80A4C180 n_alSynFreeFX
80AAD790 osPiRawReadIo
80AAD7F0 osCreateThread
80AAD940 osStartThread
80AADA90 osDpSetStatus
80AADAA0 osCreatePiManager
80AADC20 osSetThreadPri
80AADD00 osSendMesg
80AADE50 osRecvMesg
80AADF90 osViBlack
80AAE000 osGetTime
80AAE350 n_alSeqpGetState
80AAE460 guTranslateF
80AAE4A8 guTranslate
80AAE500 guOrthoF
80AAE654 guFrustum
80AAE6C0 guPerspectiveF
80AAE8F0 guPerspective
80AAE950 guRotateF
80AAEAE4 guAlign
80AAEBE0 guMtxCatF
80AAEE50 guMtxIdentF
80AAEED8 guMtxIdent
80AAEF08 guMtxL2F
80AAEFC0 guScaleF
80AAF014 guRotateRPY
80AAF060 guLookAtReflectF
80AAF4A0 guLookAtReflect
80AAF530 guLookAtF
80AAF7E8 guLookAt
80AAF860 __sinf
80AAFA20 osCreateMesgQueue
80AAFA90 osViSetSpecialFeatures
80AAFFA0 sprintf
80AB00B0 alEvtqFlushType
80AB015C alEvtqFlush
80AB01CC alEvtqPostEvent
80AB02F0 alEvtqNextEvent
80AB037C alEvtqNew
80AB03F0 alUnlink
80AB0420 alLink
80AB0444 alClose
80AB047C alInit
80AB04B0 alSynAddPlayer
80AB0500 _allocatePVoice
80AB05E8 alSynAllocVoice
80AB0730 alSynSetVol
80AB07D0 alSynStartVoice
80AB0860 alSynSetPan
80AB08F0 alSynSetPitch
80AB0980 alSynSetFXMix
80AB0A20 alSynStopVoice
80AB0AA0 alSynFreeVoice
80AB0B50 alCents2Ratio
80AB0BA0 osSetIntMask
80AB0C00 alSeqpStop
80AB0C30 alCSeqGetLoc
80AB0CD0 alCSeqSetLoc
80AB0E8C __dummy
80AB0E94 alCSeqNextEvent
80AB118C alCSeqNew
80AB12A0 alCSeqNewMarker
80AB140C alSeqGetTicks
80AB1414 alCSeqSecToTicks
80AB1510 alCSeqTicksToSec
80AB157C __alCSeqNextDelta
80AB16F0 alSeqpSetSeq
80AB1730 alSeqpPlay
80AB1760 alSeqpSetVol
80AB17E0 alSeqpSetTempo
80AB19A4 alBnkfNew
80AB1AA8 alSeqFileNew
80AB1AF0 __CSPPostNextSeqEvent
80AB2BB0 alCSPNew
80AB2D20 alSeqpSetBank
80AB2DE0 coss
80AB30A0 osAiSetNextBuffer
80AB3168 _timeToSamples
80AB31C0 _freePVoice
80AB31F8 _collectPVoices
80AB3258 __freeParam
80AB3270 __allocParam
80AB3530 alSynNew
80AB3830 osPiStartDma
80AB395C __f_to_ll
80AB3978 __d_to_ull
80AB3A18 __f_to_ull
80AB3AB4 __ll_to_d
80AB3ACC __ll_to_f
80AB3AE4 __ull_to_d
80AB3B18 __ull_to_f
80AB3EB0 osViSetMode
80AB3F90 osViSetEvent
80AB4010 osViGetCurrentFramebuffer
80AB4090 osViSwapBuffer
80AB40E0 osSetTimer
80AB41C0 osSpTaskYielded
80AB435C osSpTaskLoad
80AB44BC osSpTaskStartGo
80AB4500 osSpTaskYield
80AB4520 guMtxXFML
80AB4580 guMtxCatL
80AB47DC __osContGetInitData
80AB48AC __osPackRequestData
80AB49A0 osContSetCh
80AB4A10 osContStartReadData
80AB4AD4 osContGetReadData
80AB4D90 osContStartQuery
80AB4E14 osContGetQuery
80AB4E40 guNormalize
80AB58F0 __osSiCreateAccessQueue
80AB5940 __osSiGetAccess
80AB5984 __osSiRelAccess
80AB59B0 osGetThreadPri
80AB5AB0 __osDevMgrMain
80AB5CBC __osTimerInterrupt
80AB5E34 __osSetTimerIntr
80AB5EA8 __osInsertTimer
80AB6030 __osProbeTLB
80AB60F0 _Printf
80AB72AC strlen
80AB72D4 strchr
80AB7404 __resetPerfChanState
80AB7484 __initFromBank
80AB7540 __vsDelta
80AB7564 __vsVol
80AB75EC __seqpReleaseVoice
80AB7718 __voiceNeedsNoteKill
80AB77C0 __unmapVoice
80AB7830 __postNextSeqEvent
80AB7984 __vsPan
80AB79CC __lookupVoice
80AB7A40 __mapVoice
80AB7AB0 __lookupSoundQuick
80AB89F0 __seqpStopOsc
80AB8AF4 __initChanState
80AB8B64 alSeqpNew
80AB8CF0 alSynStartVoiceParams
80AB8DE0 __osViSwapContext
80AB9170 alSaveNew
80AB91B4 alMainBusNew
80AB9208 alAuxBusNew
80AB925C alResampleNew
80AB92E4 alLoadNew
80AB938C alEnvmixerNew
80AB9430 init_lpfilter
80AB98F0 alSynAllocFX
80AB99C0 alMainBusPull
80AB9AE0 alLoadParam
80AB9CB4 alRaw16Pull
80ABA18C alAdpcmPull
80ABA71C alResamplePull
80ABA958 _frexpf
80ABAA44 alEnvmixerParam
80ABB540 alAuxBusPull
80ABB654 alSavePull
80ABB6E0 osJamMesg
80ABB830 osPiGetCmdQueue
80ABB848 MusPtrBankGetCurrent
80ABBBE0 __osSpRawStartDma
80ABBCA0 __osSiRawStartDma
80ABBE10 __osSiDeviceBusy
80ABC400 _Litob
80ABC700 _Ldtob
80ABD4D0 alSeqGetLoc
80ABD4EC alSeqSetLoc
80ABD564 alSeqNextEvent
80ABD6E8 alSeqNewMarker
80ABD808 alSeqSecToTicks
80ABD8EC alSeqTicksToSec
80ABD940 __alSeqNextDelta
80ABDA18 alSeqNew
80ABDAF0 alSynSetPriority
80ABDB00 alFilterNew
80ABDBC8 _filterBuffer
80ABDC80 _saveBuffer
80ABDE08 _loadBuffer
80ABDF94 _loadOutputBuffer
80ABE3D0 alFxParam
80ABE3E8 alFxPull
80ABE7A0 lldiv
80ABE8A0 ldiv
