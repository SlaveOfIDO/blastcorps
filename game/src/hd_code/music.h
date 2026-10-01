#ifndef MUSIC_H
#define MUSIC_H

extern s32 D_hd_code_8036772C;
extern u8 D_hd_code_80367728;
extern u8 D_hd_code_80367729;
extern u8 D_hd_code_8036772A;
extern s8 D_hd_code_80367730;
extern ALBank* D_hd_code_80367738;
extern ALCSPlayer* g_musicPlayer;
extern s32 D_hd_code_80367740;

void musicPlayTune(u8 sequenceId, f32 sequenceVolume);
void musicSetMasterVolume(f32 volume);

#endif
