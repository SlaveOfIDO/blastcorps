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

#endif
