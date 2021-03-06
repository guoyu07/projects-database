/***************************************************************************
 * opengl.h is part of Math Graphic Library
 * Copyright (C) 2007 Alexey Balakin <balakin@appl.sci-nnov.ru>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef MGL_CANVAS_GL_H
#define MGL_CANVAS_GL_H
/*****************************************************************************/
#ifdef __cplusplus
#include "mgl2/canvas.h"

class mglCanvasGL : public mglCanvas
{
public:
	mglCanvasGL();
	~mglCanvasGL();

	void SetQuality(int =0)	{	Quality=2;	}
	void Finish(bool fast=true);
	void SetSize(int ,int )	{}
	void View(mreal tetX,mreal tetY,mreal tetZ);
	int NewFrame();
	void EndFrame();

	bool Alpha(bool enable);
	void Fog(mreal d, mreal dz=0.25);
	bool Light(bool enable);
	void Light(int n, bool enable);
	void AddLight(int n,mglPoint r,mglPoint d, char c='w', mreal bright=0.5, mreal ap=0);
	void Clf(mglColor Back=WC);

protected:
	void line_draw(long p1, long p2, mglDrawReg *d);
	void trig_draw(long p1, long p2, long p3, bool anorm, mglDrawReg *d);
	void quad_draw(long p1, long p2, long p3, long p4, mglDrawReg *d);
	void pnt_draw(long p, mglDrawReg *d);

	unsigned char **GetRGBLines(long &w, long &h, unsigned char *&f, bool solid=true);
	void LightScale();
	void set_pen(unsigned style,mreal width);
};
extern "C" {
#endif
/*****************************************************************************/
HMGL mgl_create_graph_gl();
/*****************************************************************************/
uintptr_t mgl_create_graph_gl_();
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
#endif

