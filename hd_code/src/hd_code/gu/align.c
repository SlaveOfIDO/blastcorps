/**************************************************************************
 *									  *
 *		 Copyright (C) 1994, Silicon Graphics, Inc.		  *
 *									  *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *									  *
 **************************************************************************/

#include "guint.h"

/*
 * S = sin (a)
 * C = cos (a)
 * H = sqrt (X*X + Z*Z)
 *
 * [   v   ]  [  C  S        ]  [  1           ]  [ -Z/H  X/H    ]
 *            [ -S  C        ]  [     H  Y     ]  [     1        ]
 *            [        1     ]  [    -Y  H     ]  [ -X/H -Z/H    ]
 *            [           1  ]  [           1  ]  [           1  ]
 *
 */

void guAlignF(float mf[4][4], float a, float x, float y, float z)
{
  static float	dtor = 3.1415926 / 180.0;
  float s, c, u, v;
  volatile float w;

  guNormalize(&x, &y, &z);

  a *= dtor;
  s = sinf(a);
  c = cosf(a);
  u = x * y * (1.0f - c);
  v = y * z * (1.0f - c);
  w = z * x * (1.0f - c);

  guMtxIdentF(mf);

  mf[0][0] = (1.0f - x * x) * c + x * x;
  mf[2][1] = v - x * s;
  mf[1][2] = x * s + v;

  mf[1][1] = (1.0f - y * y) * c + y * y;
  mf[2][0] = y * s + w;
  mf[0][2] = w - y * s;

  mf[2][2] = (1.0f - z * z) * c + z * z;
  mf[1][0] = u - z * s;
  mf[0][1] = z * s + u;

}

void guAlign(Mtx *m, float a, float x, float y, float z)
{
	Matrix	mf;

	guAlignF(mf, a, x, y, z);

	guMtxF2L(mf, m);
}
