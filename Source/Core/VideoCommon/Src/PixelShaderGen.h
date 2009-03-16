// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef GCOGL_PIXELSHADER
#define GCOGL_PIXELSHADER

#include "Common.h"

#define I_COLORS "color"
#define I_KCOLORS "k"
#define I_ALPHA "alphaRef"
#define I_TEXDIMS "texdim"
#define I_ZBIAS "czbias"
#define I_INDTEXSCALE "cindscale"
#define I_INDTEXMTX "cindmtx"
#define I_FOG "cfog"

#define C_COLORS 0
#define C_KCOLORS (C_COLORS+4)
#define C_ALPHA (C_KCOLORS+4)
#define C_TEXDIMS (C_ALPHA+1)
#define C_ZBIAS (C_TEXDIMS+8)
#define C_INDTEXSCALE (C_ZBIAS+2)
#define C_INDTEXMTX (C_INDTEXSCALE+2)
#define C_FOG (C_INDTEXMTX+6)
#define C_ENVCONST_END (C_FOG+2)

#define C_COLORMATRIX (C_FOG+2)

class PIXELSHADERUID
{
public:
	u32 values[5+32+6+11];
	u16 tevstages, indstages;

	PIXELSHADERUID() {
		memset(values, 0, (5+32+6+11) * 4);
		tevstages = indstages = 0;
	}
	PIXELSHADERUID(const PIXELSHADERUID& r)
	{
		tevstages = r.tevstages;
		indstages = r.indstages;
		int N = tevstages + indstages + 4;
		_assert_(N <= 5+32+6+11);
		for (int i = 0; i < N; ++i) 
			values[i] = r.values[i];
	}
	int GetNumValues() const {
		return tevstages + indstages + 3; // numTevStages*3/2+1
	}
	bool operator <(const PIXELSHADERUID& _Right) const
	{
		if (values[0] < _Right.values[0])
			return true;
		else if (values[0] > _Right.values[0])
			return false;
		int N = GetNumValues();
		for (int i = 1; i < N; ++i) {
			if (values[i] < _Right.values[i])
				return true;
			else if (values[i] > _Right.values[i])
				return false;
		}
		return false;
	}
	bool operator ==(const PIXELSHADERUID& _Right) const
	{
		if (values[0] != _Right.values[0])
			return false;
		int N = GetNumValues();
		for (int i = 1; i < N; ++i) {
			if (values[i] != _Right.values[i])
				return false;
		}
		return true;
	}
};

const char *GeneratePixelShader(u32 texture_mask, bool has_zbuffer_target, bool bRenderZToCol0, bool dstAlphaEnable, bool HLSL = false);
void GetPixelShaderId(PIXELSHADERUID &, u32 s_texturemask, u32 zbufrender, u32 zBufRenderToCol0, u32 dstAlphaEnable);

#endif
