#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <ultra64.h>
#include "snd.h"
#include "structs.h"

void Thread1(void*);
void Thread3(void*);
extern void func_hd_code_802D4250(u32*, u32*);
extern void func_hd_code_80270AE0(u32*);
void func_hd_code_80257490(u8** arg0, s32 arg1);
u8 func_hd_code_802B01DC();                          /* extern */
u8 func_hd_code_802B1150();                          /* extern */
u8 func_hd_code_802B2EF8();                          /* extern */
u8 func_hd_code_802B45FC();                          /* extern */
u8 func_hd_code_802B5F04();                          /* extern */
u8 func_hd_code_802B76F8();                          /* extern */
u8 func_hd_code_802BB170();                          /* extern */
u8 func_hd_code_802BBE10();                          /* extern */
u8 func_hd_code_802C5508();                          /* extern */
u8 func_hd_code_802C8AF0();                          /* extern */
u8 func_hd_code_802CA140();                          /* extern */
u8 func_hd_code_802CBB60();                          /* extern */
u8 func_hd_code_802CCCD8();                          /* extern */
u8 func_hd_code_802CFA58();                          /* extern */
u8 func_hd_code_802D0B90();                          /* extern */
s32 func_hd_code_8024B418(u8);                       /* extern */
u8 func_hd_code_8024B4B8();                         /* extern */
s32 sndGetPlayingState(s32);                     /* extern */
void func_hd_code_802794E4();                          /* extern */
void func_hd_code_8028B720();                          /* extern */
void func_hd_code_8028F93C();                          /* extern */
void func_hd_code_80292084();                          /* extern */
u8 func_hd_code_802AE888(s32);                      /* extern */
void func_hd_code_802B0254();                          /* extern */
void func_hd_code_802B11B8();                          /* extern */
void func_hd_code_802B2F54();                          /* extern */
void func_hd_code_802B4658();                          /* extern */
void func_hd_code_802B5F60();                          /* extern */
void func_hd_code_802B7754();                          /* extern */
void func_hd_code_802BB1A0();                          /* extern */
void func_hd_code_802BBE2C();                          /* extern */
void func_hd_code_802C5688();                          /* extern */
void func_hd_code_802C8B0C(u8);                        /* extern */
void func_hd_code_802CA1AC();                          /* extern */
void func_hd_code_802CBBBC();                          /* extern */
void func_hd_code_802CCD34();                          /* extern */
void func_hd_code_802CFAB4();                          /* extern */
void func_hd_code_802D0BF8();                          /* extern */
void func_hd_code_802AEEC8();                          /* extern */
void func_hd_code_802B03F4();                          /* extern */
void func_hd_code_802B152C();                          /* extern */
void func_hd_code_802B327C();                          /* extern */
void func_hd_code_802B49AC();                          /* extern */
void func_hd_code_802B6294();                          /* extern */
void func_hd_code_802B7A88();                          /* extern */
void func_hd_code_802BB274();                          /* extern */
void func_hd_code_802BBEB8();                          /* extern */
void func_hd_code_802C5AFC();                          /* extern */
void func_hd_code_802C8BB8(u8);                        /* extern */
void func_hd_code_802CA4E0();                          /* extern */
void func_hd_code_802CBEF0();                          /* extern */
void func_hd_code_802CD068();                          /* extern */
void func_hd_code_802CFDE8();                          /* extern */
void func_hd_code_802D0F98();                          /* extern */
void func_hd_code_802B02A0();                          /* extern */
void func_hd_code_802B2FA0();                          /* extern */
void func_hd_code_802B46C4();                          /* extern */
void func_hd_code_802B5FAC();                          /* extern */
void func_hd_code_802B77A0();                          /* extern */
void func_hd_code_802C5860();                          /* extern */
void func_hd_code_802CBC08();                          /* extern */
void func_hd_code_802CCD80();                          /* extern */
void func_hd_code_802CFB00();                          /* extern */
void func_hd_code_802AB670(u8);                                /* extern */
void func_hd_code_802A467C(u8*, void*, void*, s32);
void* func_hd_code_802D4E20(s32);
void func_hd_code_8025BBE8(u16 arg0, s8 arg1, s8 arg2);
void func_hd_code_80260D7C(f32);                       /* extern */
f32 func_hd_code_80260DF0();                        /* extern */
void func_hd_code_80275270(u64, s32);                   /* extern */
void func_hd_code_80285EF4(s32);                       /* extern */
void func_hd_code_8028B240();                          /* extern */
void func_hd_code_8024E4F4(Gfx** arg0, struct Model1 *arg1, u8 arg2);
void func_hd_code_8024F520(Gfx**, struct Model1*);                        /* extern */
void func_hd_code_8024FC2C(Gfx**, u8);                         /* extern */
void func_hd_code_802502EC(void);                                  /* extern */
void func_hd_code_802507C8(Mtx*, LookAt*, void*);               /* extern */
void func_hd_code_80258B78(Gfx**, struct Model1*);                        /* extern */
void func_hd_code_80259450();                                  /* extern */
void func_hd_code_80259C24(Gfx**, struct Model1*);                        /* extern */
void func_hd_code_80259CCC(struct Model1* arg0, const char* arg1, u16* arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13);
void func_hd_code_8025E2CC(Gfx**, struct Model1*, u8);                    /* extern */
void func_hd_code_8025E67C(Gfx**, struct Model1*, u8);                    /* extern */
s32 func_hd_code_80266248(Gfx**, struct Model1*);                        /* extern */
s32 func_hd_code_8026A378(s32, s8*);                          /* extern */
s32 func_hd_code_802701A8(void**, s32*);                        /* extern */
Gfx* func_hd_code_80271FD0(Gfx*, struct Model1*, s32, s16, s32, s32*); /* extern */
void func_hd_code_80274B40(Gfx**, struct Model1*, u8, s32, s32);            /* extern */
s32 areWeFading();                                /* extern */
s32 func_hd_code_80275478(struct Model1*, Gfx**, s32);                   /* extern */
s32 func_hd_code_80276E50(void**, s32*, u8, s32, s32, s32);     /* extern */
s32 func_hd_code_80278324(Gfx**, s32*, u8);                    /* extern */
s32 func_hd_code_80279EE8(void**, s32*, u8);                    /* extern */
s32 func_hd_code_8027C4C8(void**, s32*);                        /* extern */
s32 func_hd_code_8027F1F8(Gfx**, u8, s32);                     /* extern */
s32 func_hd_code_80280F34(Gfx**, u8);                        /* extern */
s32 func_hd_code_80281E44(void**);                            /* extern */
s32 func_hd_code_80282224(void**, u8);                        /* extern */
s32 func_hd_code_8028273C(Gfx**, u8);                        /* extern */
s32 func_hd_code_80282C80(Gfx**, struct Model1*, s32, s32, s32, s32, s32, s32); /* extern */
s32 func_hd_code_8028376C(Gfx**, struct Model1*, u8, s32, s32, s32, s32); /* extern */
s32 func_hd_code_80285CC0();                                  /* extern */
s32 func_hd_code_80286C60(Gfx**, s32*, u8, u8);                /* extern */
s32 func_hd_code_80287530(void**, s32*, u8, u8);                /* extern */
s32 func_hd_code_80287C68(void**, s32*, u8, u8);                /* extern */
s32 func_hd_code_80288DF0(void**, u8);                        /* extern */
s32 func_hd_code_8028CB30(void**, s32*);                        /* extern */
s32 func_hd_code_8028E9E4(void**, s32*);                        /* extern */
s32 func_hd_code_802917B0(void**, s32*);                        /* extern */
s32 func_hd_code_80292EB8(void**, s32*);                        /* extern */
s32 func_hd_code_80295120(Gfx**, struct Model1*);                        /* extern */
s32 func_hd_code_802976E8(void**);                            /* extern */
s32 func_hd_code_802A45D4(s32);                                 /* extern */
void* func_hd_code_802CEEFC(void*, u8, void*, void*);       /* extern */
void func_hd_code_802D4F68(Mtx*, f32, f32, f32);                    /* extern */
void func_hd_code_802D4F20(f32 m[4][4], f32, f32, f32);         /* extern */
void func_hd_code_802AC61C(s32, s32, s32, u8, s32);     /* extern */
f32 func_hd_code_80254E54(f32, f32, f32, f32, f32, f32); /* extern */
void func_hd_code_80255034(s32, f32, s32*, s32*);      /* extern */
void func_hd_code_80255190();                          /* extern */
f32 func_hd_code_802574F0(f32);                     /* extern */
f32 func_hd_code_80257514(f32);                     /* extern */
s32 func_hd_code_802A56C4();                        /* extern */
s32 func_hd_code_802AD7D4(s32);                     /* extern */
void func_hd_code_802CE4F0(s32, s32, s32);             /* extern */
void func_hd_code_802CE5BC(s32, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_802D5F60(Mtx*, LookAt*, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* extern */
f32 sqrtf(f32);                     /* extern */
void func_hd_code_802D62A8(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32); /* extern */
u8 func_hd_code_80255628();                         /* extern */
s32 func_hd_code_802AC4C4(s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_80261588();                          /* extern */
void func_hd_code_80270D20(void*, void*, s32, s32, s32);      /* extern */
void func_hd_code_80270E50(void*, void*, void*, s32, s32);        /* extern */
void func_hd_code_80284DB0();                          /* extern */
u8 func_hd_code_8028A370();                         /* extern */
void func_hd_code_8028FC10();                          /* extern */
void InitiateDma(void*, void*, s32*, u8, s32, s32);           /* extern */
void func_801F7850();                                  /* extern */
void func_hd_code_802559F8(Gfx* gfx, s32* arg1);
void func_hd_code_802592F0();                          /* extern */
u8 func_hd_code_80261A44(u64);                 /* extern */
void func_hd_code_8026A8BC();                          /* extern */
void func_hd_code_8026A974();                          /* extern */
void func_hd_code_8026B118(s32);                         /* extern */
void func_hd_code_80272C50();                          /* extern */
void func_hd_code_80278E3C();                          /* extern */
void func_hd_code_8028A42C();                          /* extern */
void func_hd_code_8028AE88();                          /* extern */
void func_hd_code_8028B3E0();                          /* extern */
void func_hd_code_80297530(s32);                       /* extern */
void func_hd_code_802A0700();                          /* extern */
void LoadLevel(u32 arg0, void* arg1, s32* arg2);                         /* extern */
void func_hd_code_80257234();                          /* extern */
void func_hd_code_8025BD98();                          /* extern */
s32 func_hd_code_80262150(s32);                       /* extern */
s32 func_hd_code_802621DC(s32);                       /* extern */
s32 func_hd_code_80262238(s32);                       /* extern */
s32 func_hd_code_80262320(s32);                       /* extern */
s32 func_hd_code_80264C20(s32);                       /* extern */
s32 func_hd_code_80268664(s32);                       /* extern */
s32 func_hd_code_8026A988();                          /* extern */
s32 func_hd_code_8026F92C(u64);                 /* extern */
s32 func_hd_code_80270ECC(s32*, s32*);                    /* extern */
s32 func_hd_code_802729F0(s32, s32);                  /* extern */
s8 func_hd_code_80272C5C(s32*, s32, s32, s32, s32, f32);    /* extern */
s32 func_hd_code_80275430();                          /* extern */
s32 func_hd_code_802775C0();                          /* extern */
s32 func_hd_code_8027BE4C();                          /* extern */
s32 func_hd_code_8027E344(s32);                       /* extern */
s32 func_hd_code_802807D8(s32);                       /* extern */
s32 func_hd_code_80281A70(s32);                       /* extern */
s32 func_hd_code_802821D0();                          /* extern */
s32 func_hd_code_80282728();                          /* extern */
void func_hd_code_80285110(s32);                         /* extern */
s32 func_hd_code_80285190();                          /* extern */
s32 func_hd_code_80286A00();                          /* extern */
s32 func_hd_code_802873AC();                          /* extern */
s32 func_hd_code_80287AE4();                          /* extern */
s32 func_hd_code_80288220();                          /* extern */
s32 func_hd_code_80292240();                          /* extern */
s32 func_hd_code_80294E30();                          /* extern */
s32 func_hd_code_80294E88();                          /* extern */
s32 func_hd_code_80294EB8();                          /* extern */
s32 func_hd_code_802979E0(s32);                       /* extern */
s32 func_hd_code_802A1674(u8*, s32);                   /* extern */
s32 func_hd_code_802A56C4();                          /* extern */
s32 func_hd_code_802A5FA8();                          /* extern */
void func_hd_code_802C1DD0(s32);                       /* extern */
s32 func_hd_code_802CE840();                          /* extern */
void func_hd_code_802CF628();                          /* extern */


s32 func_801E7000();                                /* extern */
void func_801E7598();                                  /* extern */
void func_801E8C40(u8);                                /* extern */
void func_801E8DCC(u8);                                /* extern */
void func_801E8EB8(u8, s32);                             /* extern */
void func_801EA108(u8, s32, s32);                          /* extern */
void func_801EA4B8();                                  /* extern */
void func_801EA6E8();                                  /* extern */
void func_801EA93C(char*, u32*, s32, s32, void*);               /* extern */
void func_801EC288(u8);                                /* extern */
void func_801EC30C(u8);                                /* extern */
void func_801ECC8C();                                  /* extern */
void func_801ECE9C();                                  /* extern */
void func_801ED790();                                  /* extern */
u8 func_801EE800(u8*, s32, s32);                        /* extern */
s8 func_801EF1E0();                                 /* extern */
void func_801EF380(s32);                                 /* extern */
void func_801EF4AC();                                  /* extern */
void func_801F55D8();                                  /* extern */
void func_801F6F18();                                  /* extern */
void func_801F8228();                                  /* extern */
void func_801F8530(s32);                               /* extern */
void func_801F8980();                                  /* extern */
void func_801FE018(s32);                                 /* extern */
void func_801FE990();                                  /* extern */
void func_80200714(s32);                                 /* extern */
void func_80201240(s32);                               /* extern */
s32 func_80201E80();                                /* extern */
void func_hd_code_802475D8();                          /* extern */
void func_hd_code_80255AD0();                          /* extern */
void func_hd_code_80255D34();                          /* extern */
void func_hd_code_80255DC8();                          /* extern */
void func_hd_code_80256A34(s32*);                        /* extern */
void func_hd_code_8025B2B8();                          /* extern */
void func_hd_code_8025B9D0(s32, s32*);                 /* extern */
void func_hd_code_8025BB38();                          /* extern */
void func_hd_code_8025BB50();                          /* extern */
void func_hd_code_8025D184();                          /* extern */
void sndDeactivateAllSfxByFlag_1();                          /* extern */
void sndSetSfxSlotVolume(s32, s32);                      /* extern */
void func_hd_code_80260E80();                          /* extern */
void func_hd_code_80260EE0(u8);                         /* extern */
void func_hd_code_8026101C();                          /* extern */
u8 func_hd_code_80261A44(u64);                 /* extern */
void func_hd_code_80261E9C(u64);                  /* extern */
void func_hd_code_80261FB0(u8);                        /* extern */
void func_hd_code_80264AEC();                          /* extern */
void func_hd_code_802661EC();                          /* extern */
extern void guFrustum(Mtx *m, float l, float r, float b, float t,
                      float n, float f, float scale);
extern void guFrustumF(float mf[4][4], float l, float r, float b, float t,
                       float n, float f, float scale);

void func_hd_code_8026B8F8();                          /* extern */
s32 func_hd_code_8026F92C(u64);                 /* extern */
void func_hd_code_80285110(s32);                         /* extern */
u8 func_hd_code_80285814();                         /* extern */
void func_hd_code_80285A78(s32*, s32*);                /* extern */
s32 func_hd_code_8028604C(s32);                     /* extern */
void func_hd_code_802860F0();                          /* extern */
void func_hd_code_80286330();                          /* extern */
s32 func_hd_code_8028653C();                        /* extern */
void func_hd_code_8028B3E0();                          /* extern */
void func_hd_code_80295E50();                          /* extern */
void func_hd_code_80297960();                          /* extern */
void func_hd_code_80297ECC();                          /* extern */
void func_hd_code_80299C0C();                          /* extern */
void func_hd_code_80299C20();                          /* extern */
void func_hd_code_80299E10(s32);                         /* extern */
void func_hd_code_8029A130();                          /* extern */
void func_hd_code_802A0700();                          /* extern */
void func_hd_code_802C1DD0(s32);                       /* extern */
s32 record_status(s32*);                      /* extern */
void func_hd_code_802CF5B0();                          /* extern */
u64 func_hd_code_802D4BB8(u64, u64);          /* extern */
void func_hd_code_802AFFD4();                          /* extern */
void func_hd_code_802B1228();                          /* extern */
void func_hd_code_802B2D7C();                          /* extern */
void func_hd_code_802B448C();                          /* extern */
void func_hd_code_802B5CD8();                          /* extern */
void func_hd_code_802B76AC();                          /* extern */
void func_hd_code_802BB054();                          /* extern */
void func_hd_code_802BBDC8();                          /* extern */
void func_hd_code_802C5714();                          /* extern */
void func_hd_code_802C8AB0();                          /* extern */
void func_hd_code_802C9F54();                          /* extern */
void func_hd_code_802CBA94();                          /* extern */
void func_hd_code_802CCC8C();                          /* extern */
void func_hd_code_802CFA0C();                          /* extern */
void func_hd_code_802D0C68();                          /* extern */
void LoadLevelTodo40(s32);                             /* extern */
void func_hd_code_8024A348();                          /* extern */
void func_hd_code_8024A92C(u32);                       /* extern */
void func_hd_code_8024ADD8();                          /* extern */
void func_hd_code_8024AE2C();                          /* extern */
void func_hd_code_8024B188();                          /* extern */
void func_hd_code_8024B5E8();                          /* extern */
void func_hd_code_8024B618();                          /* extern */
void func_hd_code_8024B7AC();                          /* extern */
void func_hd_code_8024B8F4(void*, void*);              /* extern */
void func_hd_code_8024BDA4(u16*);                      /* extern */
Gfx* func_hd_code_8024C404(Gfx*, struct Model1*, s32*);        /* extern */
Gfx* func_hd_code_8024C414(struct Model1*, s32*);             /* extern */
void func_hd_code_802559F8(Gfx*, s32*);                 /* extern */
void func_hd_code_80258544(struct Texture* arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 *arg5, s32 *arg6, s32 *arg7);
void func_hd_code_8025C5D0();                          /* extern */
s32 func_hd_code_8025C878(Gfx* arg0, void* arg1, u8 arg2, s32* arg3);    /* extern */
void func_hd_code_80261570(f32);                         /* extern */
void func_hd_code_80262BF4();                          /* extern */
s32 func_hd_code_802639B4(s32, void*, s32*);        /* extern */
void func_hd_code_8026420C();                          /* extern */
void func_hd_code_8026510C();                          /* extern */
void func_hd_code_802683E0();                          /* extern */
void func_hd_code_802688C4(s32);                       /* extern */
void func_hd_code_8026A9B4();                          /* extern */
s32 func_hd_code_8026B10C();                        /* extern */
s32 func_hd_code_8026BBD0(s32, void*, s32*);        /* extern */
void func_hd_code_8026FEC4();                          /* extern */
s32 func_hd_code_80274BF0(void*, s32);              /* extern */
void func_hd_code_80275390(u64);                      /* extern */
void func_hd_code_80277620(u32);                       /* extern */
void func_hd_code_802794A4();                          /* extern */
void func_hd_code_80279514(s32, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_80279778(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_8027D810(s32);                       /* extern */
void func_hd_code_8027E9B8(u8);                        /* extern */
void func_hd_code_80281CE4();                          /* extern */
void func_hd_code_80284E54(Gfx*, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_80285AB0(s32);                         /* extern */
void func_hd_code_802886A0();                          /* extern */
void func_hd_code_8028A3E4();                          /* extern */
void func_hd_code_8028A470();                          /* extern */
void func_hd_code_8028C874(u8);                        /* extern */
void func_hd_code_8028DF14(u8);                        /* extern */
void func_hd_code_8028F794(u8);                        /* extern */
void func_hd_code_802906C0(u8);                        /* extern */
void func_hd_code_80291FAC(u8);                        /* extern */
void func_hd_code_80292830();                          /* extern */
void func_hd_code_80294F00();                          /* extern */
void func_hd_code_80295C70(s32, s32, s32);             /* extern */
s32 func_hd_code_80295EFC(void*, s32, s32, s32, s32); /* extern */
void func_hd_code_80297804(s32, s32, s32);             /* extern */
s32 func_hd_code_8029A1A8(s32*, s32);                 /* extern */
s32 func_hd_code_8029A518(void*, s32);              /* extern */
void func_hd_code_8029DDC8();                          /* extern */
void func_hd_code_8029E0AC();                          /* extern */
void func_hd_code_802A4CDC(s32, s32, s32, s32, void*); /* extern */
void func_hd_code_802A5720();                          /* extern */
void func_hd_code_802A57AC();                          /* extern */
void func_hd_code_802A64A4();                          /* extern */
void func_hd_code_802AEEC8();                          /* extern */
void func_hd_code_802B8794();                          /* extern */
void func_hd_code_802B899C();                          /* extern */
void func_hd_code_802B8AE4();                          /* extern */
void func_hd_code_802BA148();                          /* extern */
void func_hd_code_802BA354();                          /* extern */
void func_hd_code_802BC5E0();                          /* extern */
void func_hd_code_802BCA2C();                          /* extern */
void func_hd_code_802BD1F8(void*, void*, void*, void*, void*, void*, void*, void*); /* extern */
void func_hd_code_802C0574();                          /* extern */
s8 func_hd_code_802C1AA0();                         /* extern */
s32 func_hd_code_802C1B9C();                        /* extern */
void func_hd_code_802C2054();                          /* extern */
void func_hd_code_802CF1A4();                          /* extern */
void func_hd_code_802D291C();                          /* extern */
s32 func_hd_code_802D4E10(struct S_802D4E10* arg0);                     /* extern */
void sndDeactivate(s32);                       /* extern */
void func_hd_code_80260DFC();                          /* extern */
void func_hd_code_80261040();                          /* extern */
s32 func_hd_code_8026A610(s32, s32, s32, s32);      /* extern */
s32 func_hd_code_8026AD30(u8);                       /* extern */
void func_hd_code_8026AF6C(u16);                         /* extern */
s32 func_hd_code_8026B10C();                        /* extern */
void func_hd_code_80277EDC(s32, s32, s32, s32);                /* extern */
u8 func_hd_code_8024AFA8(s32);                              /* extern */
s32 sndGetPlayingState(s32);                             /* extern */
ALSoundState *sndPlaySfx(struct ALBankAlt_s *soundBank, u16 soundIndex, ALSoundState *pendingState);
void func_hd_code_802794E4();                                  /* extern */
void func_hd_code_8028B720();                                  /* extern */
void func_hd_code_8028F6B4(u8);                                /* extern */
void func_hd_code_80291ED8(u8);                                /* extern */
void func_hd_code_802AB478(u8);                                /* extern */
s32 func_hd_code_802AB878(u8);                              /* extern */
void func_hd_code_802AE860();                                  /* extern */
void func_hd_code_8026AF6C(u16);                         /* extern */
void sndDeactivateAllSfxByFlag_1();                          /* extern */
void func_hd_code_802C1DD0(s32);                       /* extern */
void func_hd_code_80261570(f32);                         /* extern */
s32 func_hd_code_8026B10C();                        /* extern */
s32 areWeFading();                                /* extern */
u8 func_hd_code_8027EED8(s32, s32, s16*);           /* extern */
u8 func_hd_code_802ABEDC(s32, s32, s32);            /* extern */
void func_hd_code_802D4F68(Mtx*, f32, f32, f32);                    /* extern */
void func_hd_code_80284E54(Gfx*, s32, s32, s32, s32, s32); /* extern */
void func_hd_code_8025B070();
void* func_hd_code_8025B0B8(u16);                     /* extern */
s16 func_hd_code_8025B498(u16 arg0, u16 arg1, u8* arg2, s32 arg3);     /* extern */
void func_hd_code_802597D8(u8*, u8*, s32);               /* extern */
void func_hd_code_8025946C(Gfx**, struct Model1*);     /* extern */
void func_hd_code_80259824(Gfx**, struct Model1*);   /* extern */
void func_hd_code_80259EC4(s32 arg0, u8* sp44_a1, u16* sp48_a2, u8 arg3, s32 arg4, f32 arg5, s32 arg6, f32 arg7, s32 arg8, u8 sp67, u8 sp44_a10, u8 sp44_a11, u8 sp44_a12, u8 sp44_a13, u8 sp44_a14, u8 sp44_a15, u8 sp44_a16, u8 sp44_a17, u8 sp44_a18, u8 sp44_a19, u8 sp48_a20, u8 sp48_a21, u8 sp48_a22, u8 sp48_a23, u8 sp48_a24, u8 sp48_a25);
s32 func_hd_code_8025C30C();                        /* extern */
void func_hd_code_8025C5A0();                          /* extern */
void func_hd_code_802994F8();                          /* extern */
void func_hd_code_802A1040(u16, void*, s32);             /* extern */
void proutSprintf(u8*, const char*, ...);                       /* extern */
void func_hd_code_80275270(u64, s32);                   /* extern */
void func_hd_code_80275390(u64);                      /* extern */
s32 areWeFading();                                /* extern */
void func_hd_code_802AFC28(s32);                       /* extern */
void func_hd_code_802B0D70(s32);                       /* extern */
void func_hd_code_802B2988(s32);                       /* extern */
void func_hd_code_802B40D4(s32);                       /* extern */
void func_hd_code_802B58C8(s32);                       /* extern */
void func_hd_code_802B7308(s32);                       /* extern */
void func_hd_code_802C80A0(s32);                       /* extern */
void func_hd_code_802CB660(s32);                       /* extern */
void func_hd_code_802D2524(s32);                       /* extern */
void func_hd_code_802B2D7C();                          /* extern */
void func_hd_code_802AFFD4();                          /* extern */
void func_hd_code_802B1228();                          /* extern */
void func_hd_code_802D0C68();                          /* extern */
void func_hd_code_802B448C();                          /* extern */
void func_hd_code_802B5CD8();                          /* extern */
void func_hd_code_802C5714();                          /* extern */
void func_hd_code_802C9F54();                          /* extern */
s32 func_hd_code_8025B300(u8*);                     /* extern */
void InitiateDma(void*, void*, s32*, u8, s32, s32);           /* extern */
void func_hd_code_80257490(u8** arg0, s32 arg1);
s8 func_hd_code_80272C5C(s32*, s32, s32, s32, s32, f32);    /* extern */
void func_hd_code_802A1040(u16, void*, s32);             /* extern */
void proutSprintf(u8*, const char*, ...);                       /* extern */
void func_hd_code_80275270(u64, s32);                   /* extern */
void func_hd_code_80275390(u64);                      /* extern */
s32 areWeFading();                                /* extern */
void func_hd_code_802AFC28(s32);                       /* extern */
void func_hd_code_802B0D70(s32);                       /* extern */
void func_hd_code_802B2988(s32);                       /* extern */
void func_hd_code_802B40D4(s32);                       /* extern */
void func_hd_code_802B58C8(s32);                       /* extern */
void func_hd_code_802B7308(s32);                       /* extern */
void func_hd_code_802C80A0(s32);                       /* extern */
void func_hd_code_802CB660(s32);                       /* extern */
void func_hd_code_802D2524(s32);                       /* extern */
void func_hd_code_802B2D7C();                          /* extern */
void func_hd_code_802AFFD4();                          /* extern */
void func_hd_code_802B1228();                          /* extern */
void func_hd_code_802D0C68();                          /* extern */
void func_hd_code_802B448C();                          /* extern */
void func_hd_code_802B5CD8();                          /* extern */
void func_hd_code_802C5714();                          /* extern */
void func_hd_code_802C9F54();                          /* extern */
s32 func_hd_code_8025B300(u8*);                     /* extern */
void InitiateDma(void*, void*, s32*, u8, s32, s32);           /* extern */
void func_hd_code_80257490(u8** arg0, s32 arg1);
s8 func_hd_code_80272C5C(s32*, s32, s32, s32, s32, f32);    /* extern */
s32 func_hd_code_8025D2B4(Gfx* arg0, void* arg1, s32* arg2);
void func_hd_code_8025E1E0(Gfx**);                      /* extern */
void sndDeactivateAllSfxByFlag_11();                          /* extern */
void sndDeactivateAllSfxByFlag_3();                          /* extern */
void func_hd_code_80260E2C();                          /* extern */
s32 func_hd_code_8026205C(s32);                        /* extern */
void func_hd_code_80278318();                          /* extern */

#endif
