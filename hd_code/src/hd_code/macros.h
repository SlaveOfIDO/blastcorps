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

#endif
