#ifndef _MACROS_H_
#define _MACROS_H_

#define rare_CALC_DXT_4b(width)	\
		(((width)/16 + (1 << G_TX_DXT_FRAC) - 1) / \
					((width)/16))

#define	rare_gDPLoadTextureBlock_4b(pkt, timg, fmt, width, height,	\
		pal, cms, cmt, masks, maskt, shifts, shiftt)		\
{									\
	gDPSetTextureImage(pkt, fmt, G_IM_SIZ_16b, 1, timg);		\
	gDPSetTile(pkt, fmt, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,	\
		cmt, maskt, shiftt, cms, masks, shifts);		\
	gDPLoadSync(pkt);						\
	gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,				\
		(((width)*(height)+3)>>2)-1,				\
		(rare_CALC_DXT_4b(width))); 	                	\
	gDPPipeSync(pkt);						\
	gDPSetTile(pkt, fmt, G_IM_SIZ_4b, ((((width)>>1)+7)>>3), 0,	\
		G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks,	\
		shifts);						\
	gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0,			\
		((width)-1) << G_TEXTURE_IMAGE_FRAC,			\
		((height)-1) << G_TEXTURE_IMAGE_FRAC)			\
}

/*
adapted gSPScisTextureRectangle version for this match.
- Removes the s16 casting
- Removes the `xl < 0 ? ... : 0` ternary
- Removes the `yl < 0 ? ... : 0` ternary
- Subtracts 1 from the gImmp1 RDPHALF_X commands
*/
#define rare_gSPScisTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) \
{                                                                            \
    Gfx *_g = (Gfx *)(pkt);                                                  \
                                                                             \
    _g->words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) |                              \
                    _SHIFTL(MAX((xh),0), 12, 12) |                      \
                    _SHIFTL(MAX((yh),0), 0, 12));                       \
    _g->words.w1 = (_SHIFTL((tile), 24, 3) |                                 \
                    _SHIFTL(MAX((xl),0), 12, 12) |                      \
                    _SHIFTL(MAX((yl),0), 0, 12));                       \
    gImmp1(pkt, (G_RDPHALF_2),                                                 \
                (_SHIFTL(((s) -                                              \
                          (((dsdx) < 0) ?                              \
                            (MAX((((xl)*(dsdx))>>7),0)) :          \
			    (MIN((((xl)*(dsdx))>>7),0)))),    \
			 16, 16) |                                           \
                 _SHIFTL(((t) -                                              \
                          (((dtdy) < 0) ?                              \
                            (MAX((((yl)*(dtdy))>>7),0)) :          \
                            (MIN((((yl)*(dtdy))>>7),0)))),    \
			 0, 16)));                                           \
    gImmp1(pkt, (G_RDPHALF_CONT), (_SHIFTL((dsdx), 16, 16) |                      \
                              _SHIFTL((dtdy), 0, 16)));                      \
}


#define SET_COLOR_VERTEX(VERT, x,y,z, tx, ty, r, g, b, a) (VERT).v.ob[0] = (x);\
(VERT).v.ob[1] = (y);\
(VERT).v.ob[2] = (z);\
(VERT).v.flag = 0;\
(VERT).v.tc[0] = (tx);\
(VERT).v.tc[1] = (ty);\
(VERT).v.cn[0] = (r);\
(VERT).v.cn[1] = (g);\
(VERT).v.cn[2] = (b);\
(VERT).v.cn[3] = (a)

#define ASPECT_RATIO 1.33333333f
#define ASSERT_MESSAGE "\n\a --- ASSERTION FAULT - %s - %s, line %d\n\n"
#endif
