/***************************************************************************
 * mgl.h is part of Math Graphic Library
 * Copyright (C) 2007 Alexey Balakin <balakin@appl.sci-nnov.ru>            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef _MGL_H_
#define _MGL_H_

#include "mgl2/define.h"
#include "mgl2/mgl_cf.h"
#include "mgl2/data.h"
//-----------------------------------------------------------------------------
/// Wrapper class for all graphics
class mglGraph
{
protected:
	HMGL gr;
public:
	inline mglGraph(int kind=0, int width=600, int height=400)
	{
		if(kind==-1)	gr=NULL;
#if MGL_HAVE_OPENGL
		else if(kind==1)	gr=mgl_create_graph_gl();
#endif
		else	gr=mgl_create_graph(width, height);
	}
	inline mglGraph(const mglGraph &graph)
	{	gr = graph.gr;	mgl_use_graph(gr,1);	}
	inline mglGraph(HMGL graph)
	{	gr = graph;		mgl_use_graph(gr,1);	}
	virtual ~mglGraph()
	{	if(mgl_use_graph(gr,-1)<1)	mgl_delete_graph(gr);	}
	/// Get pointer to internal mglCanvas object
	inline HMGL Self()	{	return gr;	}
	/// Set default parameter for plotting
	inline void DefaultPlotParam()	{	mgl_set_def_param(gr);	}
	/// Set name of plot for saving filename
	inline void SetPlotId(const char *id)	{	mgl_set_plotid(gr,id);	}

	/// Set the transparency on/off.
	inline void Alpha(bool enable)			{	mgl_set_alpha(gr, enable);	}
	/// Set default value of alpha-channel
	inline void SetAlphaDef(mreal alpha)	{	mgl_set_alpha_default(gr, alpha);	}
	/// Set the transparency type (0 - usual, 1 - glass, 2 - lamp)
	inline void SetTranspType(int type)		{	mgl_set_transp_type(gr, type);}

	/// Set the using of light on/off.
	inline void Light(bool enable)			{	mgl_set_light(gr, enable);	}
	/// Switch on/off the specified light source.
	inline void Light(int n,bool enable)	{	mgl_set_light_n(gr, n, enable);	}
	/// Use diffusive light (only for local light sources)
	inline void SetDifLight(bool dif)		{	mgl_set_light_dif(gr, dif);	}
	/// Add a light source.
	inline void AddLight(int n, mglPoint p, char col='w', mreal bright=0.5, mreal ap=0)
	{	mgl_add_light_ext(gr, n, p.x, p.y, p.z, col, bright, ap);	}
	inline void AddLight(int n, mglPoint r, mglPoint p, char col='w', mreal bright=0.5, mreal ap=0)
	{	mgl_add_light_loc(gr, n, r.x, r.y, r.z, p.x, p.y, p.z, col, bright, ap);	}
	/// Set ambient light brightness
	inline void SetAmbient(mreal i)			{	mgl_set_ambbr(gr, i);	}
	/// Set the fog distance or switch it off (if d=0).
	inline void Fog(mreal d, mreal dz=0.25)	{	mgl_set_fog(gr, d, dz);		}

	/// Set relative width of rectangles in Bars, Barh, BoxPlot
	inline void SetBarWidth(mreal width)	{	mgl_set_bar_width(gr, width);	}
	/// Set size of marks
	inline void SetMarkSize(mreal size)		{	mgl_set_mark_size(gr, size);	}
	/// Set size of arrows
	inline void SetArrowSize(mreal size)	{	mgl_set_arrow_size(gr, size);	}
	/// Set number of mesh lines
	inline void SetMeshNum(int num)			{	mgl_set_meshnum(gr, num);		}

	/// Set cutting for points outside of bounding box
	inline void SetCut(bool cut)			{	mgl_set_cut(gr, cut);	}
	/// Set additional cutting box
	inline void SetCutBox(mglPoint p1, mglPoint p2)
	{	mgl_set_cut_box(gr, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);	}
	/// Set the cutting off condition (formula)
	inline void CutOff(const char *EqC)	{	mgl_set_cutoff(gr, EqC);	}

	/// Set default font size
	inline void SetFontSize(mreal size)		{	mgl_set_font_size(gr, size);	}
	/// Set default font style and color
	inline void SetFontDef(const char *fnt)		{	mgl_set_font_def(gr, fnt);	}
	/// Set FontSize by size in pt and picture DPI (default is 16 pt for dpi=72)
	virtual void SetFontSizePT(mreal pt, int dpi=72){	SetFontSize(pt*27.f/dpi);	}
	/// Set FontSize by size in centimeters and picture DPI (default is 0.56 cm = 16 pt)
	inline void SetFontSizeCM(mreal cm, int dpi=72)	{	SetFontSizePT(cm*28.45f,dpi);	}
	/// Set FontSize by size in inch and picture DPI (default is 0.22 in = 16 pt)
	inline void SetFontSizeIN(mreal in, int dpi=72)	{	SetFontSizePT(in*72.27f,dpi);	}
	/// Load font from file
	inline void LoadFont(const char *name, const char *path=NULL)
	{	mgl_load_font(gr, name, path);	}
	/// Copy font from another mglGraph instance
	inline void CopyFont(mglGraph *GR)		{	mgl_copy_font(gr, GR->Self());}
	/// Restore font
	inline void RestoreFont()				{	mgl_restore_font(gr);	}
	/// Set to use or not text rotation
	inline void SetRotatedText(bool rotated)	{	mgl_set_rotated_text(gr, rotated);	}

	/// Set default palette
	inline void SetPalette(const char *colors)	{	mgl_set_palette(gr, colors);	}
	/// Set default color scheme
	inline void SetDefScheme(const char *sch)	{	mgl_set_def_sch(gr, sch);	}

	/// Get last warning code
	inline int  GetWarn()			{	return mgl_get_warn(gr);}
	/// Set warning code ant fill message
	inline void SetWarn(int code, const char *info)	{	mgl_set_warn(gr,code,info);	}
	/// Set buffer for warning messages
	inline const char *Message()	{	return mgl_get_mess(gr);	}

	/// Set range in direction dir as [v1, v2]
	inline void SetRange(char dir, mreal v1, mreal v2)
	{	mgl_set_range_val(gr, dir, v1, v2);	}
	/// Set range in direction dir as minimal and maximal values of data a
	inline void SetRange(char dir, const mglDataA &dat, bool add=false)
	{	mgl_set_range_dat(gr, dir, &dat, add);	}
	/// Set values of mglGraph::Min and mglGraph::Max as minimal and maximal values of datas
	inline void SetRanges(const mglDataA &xx, const mglDataA &yy, const mglDataA &zz, const mglDataA &cc)
	{	mgl_set_range_dat(gr,'x',&xx,0);	mgl_set_range_dat(gr,'y',&yy,0);
		mgl_set_range_dat(gr,'z',&zz,0);	mgl_set_range_dat(gr,'c',&cc,0);	}
	/// Set values of mglGraph::Min and mglGraph::Max as minimal and maximal values of datas
	inline void SetRanges(const mglDataA &xx, const mglDataA &yy, const mglDataA &zz)
	{	mgl_set_range_dat(gr,'x',&xx,0);	mgl_set_range_dat(gr,'y',&yy,0);
		mgl_set_range_dat(gr,'z',&zz,0);	mgl_set_range_dat(gr,'c',&zz,0);	}
	/// Set values of mglGraph::Min and mglGraph::Max as minimal and maximal values of datas
	inline void SetRanges(const mglDataA &xx, const mglDataA &yy)
	{	mgl_set_range_dat(gr,'x',&xx,0);	mgl_set_range_dat(gr,'y',&yy,0);	}
	/// Set values of mglGraph::Min and mglGraph::Max
	inline void SetRanges(mreal x1, mreal x2, mreal y1, mreal y2, mreal z1=0, mreal z2=0)
	{	mgl_set_ranges(gr, x1, x2, y1, y2, z1, z2);	}
	/// Set values of mglGraph::Min and mglGraph::Max
	inline void SetRanges(mglPoint p1, mglPoint p2)
	{	mgl_set_ranges(gr, p1.x, p2.x, p1.y, p2.y, p1.z, p2.z);	}
	/// Set axis origin
	inline void SetOrigin(mglPoint p)
	{	mgl_set_origin(gr, p.x, p.y, p.z);	}
	inline void SetOrigin(mreal x0, mreal y0, mreal z0=NaN)
	{	mgl_set_origin(gr, x0, y0, z0);	}

	/// Set the transformation formulas for coordinate
	inline void SetFunc(const char *EqX, const char *EqY, const char *EqZ=NULL, const char *EqA=NULL)
	{	mgl_set_func(gr, EqX, EqY, EqZ, EqA);	}
	/// Set one of predefined transformation rule
	inline void SetCoor(int how)		{	mgl_set_coor(gr, how);	}
	/// Set to draw Ternary axis (triangle like axis, grid and so on)
	inline void Ternary(int val)		{	mgl_set_ternary(gr, val);	}

	/// Set to use or not tick labels rotation
	inline void SetTickRotate(bool val)	{	mgl_set_tick_rotate(gr,val);	}
	/// Set to use or not tick labels skipping
	inline void SetTickSkip(bool val)	{	mgl_set_tick_skip(gr,val);	}
	/// Set tick length
	inline void SetTickLen(mreal len, mreal stt=1)
	{	mgl_set_tick_len(gr, len, stt);	}
	/// Set axis and ticks style
	inline void SetAxisStl(const char *stl="k", const char *tck=0, const char *sub=0)
	{	mgl_set_axis_stl(gr, stl, tck, sub);	}

	/// Set time templates for ticks
	inline void SetTicksTime(char dir, mreal d=0, const char *t="")
	{	mgl_set_ticks_time(gr,dir,d,t);	}
	/// Set ticks text (\n separated). Use "" to disable this feature.
	inline void SetTicksVal(char dir, const char *lbl, bool add=false)
	{	mgl_set_ticks_str(gr,dir,lbl,add);	}
	inline void SetTicksVal(char dir, const wchar_t *lbl, bool add=false)
	{	mgl_set_ticks_wcs(gr,dir,lbl,add);	}
	/// Set ticks position and text (\n separated). Use "" to disable this feature.
	inline void SetTicksVal(char dir, const mglDataA &v, const char *lbl, bool add=false)
	{	mgl_set_ticks_val(gr,dir,&v,lbl,add);	}
	inline void SetTicksVal(char dir, const mglDataA &v, const wchar_t *lbl, bool add=false)
	{	mgl_set_ticks_valw(gr,dir,&v,lbl,add);	}
	/// Set the ticks parameters
	inline void SetTicks(char dir, mreal d=0, int ns=0, mreal org=NaN)
	{	mgl_set_ticks(gr, dir, d, ns, org);	}
	/// Auto adjust ticks
	inline void Adjust(const char *dir="xyzc")
	{	mgl_adjust_ticks(gr, dir);	}
	/// Set templates for ticks
	inline void SetTickTempl(char dir, const char *t)
	{	mgl_set_tick_templ(gr,dir,t);	}
	inline void SetTickTempl(char dir, const wchar_t *t)
	{	mgl_set_tick_templw(gr,dir,t);	}
	/// Tune ticks
	inline void SetTuneTicks(int tune, mreal fact_pos=1.15)
	{	mgl_tune_ticks(gr, tune, fact_pos);	}
	/// Set additional shift of tick labels
	inline void SetTickShift(mglPoint p)
	{	mgl_set_tick_shift(gr,p.x,p.y,p.z,p.c);	}
	/// Set to use UTC time instead of local time
	inline void SetTimeUTC(bool enable)
	{	mgl_set_flag(gr,enable, MGL_USE_GMTIME);	}
	
	/// Put further plotting in some region of whole frame surface.
	inline void SubPlot(int nx,int ny,int m,const char *style="<>_^", mreal dx=0, mreal dy=0)
	{	mgl_subplot_d(gr, nx, ny, m, style, dx, dy);	}
	/// Like SubPlot bot "join" several cells
	inline void MultiPlot(int nx,int ny,int m, int dx, int dy, const char *style="<>_^")
	{	mgl_multiplot(gr, nx, ny, m, dx, dy, style);	}
	/// Put further plotting in some region of whole frame surface.
	inline void InPlot(mreal x1,mreal x2,mreal y1,mreal y2, bool rel=true)
	{	if(rel)	mgl_relplot(gr, x1, x2, y1, y2);
		else	mgl_inplot(gr, x1, x2, y1, y2);	}
	/// Put further plotting in column cell of previous subplot
	inline void ColumnPlot(int num, int ind, mreal d=0)
	{	mgl_columnplot(gr,num,ind,d);	}
	/// Put further plotting in matrix cell of previous subplot
	inline void GridPlot(int nx, int ny, int ind, mreal d=0)
	{	mgl_gridplot(gr,nx,ny,ind,d);	}
	/// Put further plotting in cell of stick rotated on angles tet, phi
	inline void StickPlot(int num, int i, mreal tet, mreal phi)
	{	mgl_stickplot(gr,num,i,tet,phi);	}

	/// Set PlotFactor
	inline void SetPlotFactor(mreal val)
	{	mgl_set_plotfactor(gr,val);	}
	/// Push transformation matrix into stack
	inline void Push()	{	mgl_mat_push(gr);	}
	/// Pop transformation matrix from stack
	inline void Pop()	{	mgl_mat_pop(gr);	}
	
	/// Add title for current subplot/inplot
	inline 	void Title(const char *title,const char *stl="",mreal size=-2)
	{	mgl_title(gr,title,stl,size);	}
	inline 	void Title(const wchar_t *title,const char *stl="",mreal size=-2)
	{	mgl_titlew(gr,title,stl,size);	}
	/// Set aspect ratio for further plotting.
	inline void Aspect(mreal Ax,mreal Ay,mreal Az=1)
	{	mgl_aspect(gr, Ax, Ay, Az);		}
	/// Rotate a further plotting.
	inline void Rotate(mreal TetX,mreal TetZ=0,mreal TetY=0)
	{	mgl_rotate(gr, TetX, TetZ, TetY);	}
	/// Rotate a further plotting around vector {x,y,z}.
	inline void RotateN(mreal Tet,mreal x,mreal y,mreal z)
	{	mgl_rotate_vector(gr, Tet, x, y, z);	}
	/// Set perspective (in range [0,1)) for plot. Set to zero for switching off.
	inline void Perspective(mreal val)
	{	mgl_perspective(gr, val);	}
	/// Set angle of view independently from Rotate().
	inline void View(mreal TetX,mreal TetZ=0,mreal TetY=0)
	{	mgl_view(gr, TetX, TetZ, TetY);	}
	/// Zoom in or zoom out (if Zoom(0, 0, 1, 1)) a part of picture
	inline void Zoom(mreal x1, mreal y1, mreal x2, mreal y2)
	{	mgl_zoom(gr, x1, y1, x2, y2);	}

	/// Set size of frame in pixels. Normally this function is called internaly.
	inline void SetSize(int width, int height)	{	mgl_set_size(gr, width, height);	}
	/// Set plot quality
	inline void SetQuality(int qual=MGL_DRAW_NORM)	{	mgl_set_quality(gr, qual);	}
	/// Start group of objects
	inline void StartGroup(const char *name)		{	mgl_start_group(gr, name);	}
	/// End group of objects
	inline void EndGroup()	{	mgl_end_group(gr);	}
	/// Highlight next group
	inline void Highlight(int id)	{	mgl_highlight(gr, id);	}

	/// Show currently produced image
	inline void ShowImage(const char *viewer, bool keep=0)
	{	mgl_show_image(gr, viewer, keep);	}
	/// Write the frame in file (depending extension, write current frame if fname is empty)
	inline void WriteFrame(const char *fname=0,const char *descr="")
	{	mgl_write_frame(gr, fname, descr);	}
	/// Write the frame in file using JPEG format
	inline void WriteJPEG(const char *fname,const char *descr="")
	{	mgl_write_jpg(gr, fname, descr);	}
	/// Write the frame in file using PNG format with transparency
	inline void WritePNG(const char *fname,const char *descr="", bool alpha=true)
	{	if(alpha)	mgl_write_png(gr, fname, descr);
		else	mgl_write_png_solid(gr, fname, descr);	}
	/// Write the frame in file using BMP format
	inline void WriteBMP(const char *fname,const char *descr="")
	{	mgl_write_bmp(gr, fname, descr);	}
	/// Write the frame in file using BMP format
	inline void WriteTGA(const char *fname,const char *descr="")
	{	mgl_write_tga(gr, fname, descr);	}
	/// Write the frame in file using PostScript format
	inline void WriteEPS(const char *fname,const char *descr="")
	{	mgl_write_eps(gr, fname, descr);	}
	/// Write the frame in file using LaTeX format
	inline void WriteTEX(const char *fname,const char *descr="")
	{	mgl_write_tex(gr, fname, descr);	}
	/// Write the frame in file using PostScript format as bitmap
	inline void WriteBPS(const char *fname,const char *descr="")
	{	mgl_write_bps(gr, fname, descr);	}
	/// Write the frame in file using SVG format
	inline void WriteSVG(const char *fname,const char *descr="")
	{	mgl_write_svg(gr, fname, descr);	}
	/// Write the frame in file using GIF format (only for current frame!)
	inline void WriteGIF(const char *fname,const char *descr="")
	{	mgl_write_gif(gr, fname, descr);	}

	/// Write the frame in file using OBJ format
	inline void WriteOBJ(const char *fname,const char *descr="",bool use_png=true)
	{	mgl_write_obj(gr, fname, descr, use_png);	}
	/// Write the frame in file using XYZ format
	inline void WriteXYZ(const char *fname,const char *descr="")
	{	mgl_write_xyz(gr, fname, descr);	}
	/// Write the frame in file using STL format (faces only)
	inline void WriteSTL(const char *fname,const char *descr="")
	{	mgl_write_stl(gr, fname, descr);	}
	/// Write the frame in file using OFF format
	inline void WriteOFF(const char *fname,const char *descr="", bool colored=false)
	{	mgl_write_off(gr, fname, descr,colored);	}
//	/// Write the frame in file using X3D format
//	inline void WriteX3D(const char *fname,const char *descr="")
//	{	mgl_write_x3d(gr, fname, descr);	}
	/// Write the frame in file using PRC format
	inline void WritePRC(const char *fname,const char *descr="",bool make_pdf=true)
	{	mgl_write_prc(gr, fname, descr, make_pdf);	}

	/// Create new frame.
	inline void NewFrame()		{	mgl_new_frame(gr);	}
	/// Finish frame drawing
	inline void EndFrame()		{	mgl_end_frame(gr);	}
	/// Get the number of created frames
	inline int GetNumFrame()	{	return mgl_get_num_frame(gr);	}
	/// Reset frames counter (start it from zero)
	inline void ResetFrames()	{	mgl_reset_frames(gr);	}
	/// Start write frames to cinema using GIF format
	inline void StartGIF(const char *fname, int ms=100)
	{	mgl_start_gif(gr, fname,ms);	}
	/// Stop writing cinema using GIF format
	inline void CloseGIF()		{	mgl_close_gif(gr);	}
	/// Export points and primitives in file using MGLD format
	inline void ExportMGLD(const char *fname, const char *descr=0)
	{	mgl_export_mgld(gr, fname, descr);	}
	/// Import points and primitives from file using MGLD format
	inline void ImportMGLD(const char *fname, bool add=false)
	{	mgl_import_mgld(gr, fname, add);	}

	/// Copy RGB values into array which is allocated by user
	inline void GetRGB(char *imgdata, int imglen)
	{
		long w=mgl_get_width(gr), h=mgl_get_height(gr);
		if(imglen>=3*w*h)	memcpy(imgdata, mgl_get_rgb(gr),3*w*h);
	}
	inline const unsigned char *GetRGB()		{	return mgl_get_rgb(gr);	}
	/// Copy RGBA values into array which is allocated by user
	inline void GetRGBA(char *imgdata, int imglen)
	{
		long w=mgl_get_width(gr), h=mgl_get_height(gr);
		if(imglen>=4*w*h)	memcpy(imgdata, mgl_get_rgba(gr),4*w*h);
	}
	inline const unsigned char *GetRGBA()	{	return mgl_get_rgba(gr);	}
	/// Copy BGRN values into array which is allocated by user
	inline void GetBGRN(unsigned char *imgdata, int imglen)
	{
		long w=mgl_get_width(gr), h=mgl_get_height(gr), i;
		const unsigned char *buf=mgl_get_rgb(gr);
		if(imglen>=4*w*h)	for(i=0;i<w*h;i++)
		{
			imgdata[4*i]   = buf[3*i+2];
			imgdata[4*i+1] = buf[3*i+1];
			imgdata[4*i+2] = buf[3*i];
			imgdata[4*i+3] = 255;
		}
	}
	/// Get width of the image
	inline int GetWidth()	{	return mgl_get_width(gr);	}
	/// Get height of the image
	inline int GetHeight()	{	return mgl_get_height(gr);}
	/// Calculate 3D coordinate {x,y,z} for screen point {xs,ys}
	inline mglPoint CalcXYZ(int xs, int ys)
	{
		mreal x,y,z;
		mgl_calc_xyz(gr,xs,ys,&x,&y,&z);
		return mglPoint(x,y,z);
	}
	/// Calculate screen point {xs,ys} for 3D coordinate {x,y,z}
	inline mglPoint CalcScr(mglPoint p)
	{
		int xs,ys;
		mgl_calc_scr(gr,p.x,p.y,p.z,&xs,&ys);
		return mglPoint(xs,ys);
	}
	/// Set object/subplot id
	inline void SetObjId(int id)		{	mgl_set_obj_id(gr,id);	}
	/// Get object id
	inline int GetObjId(long x,long y)	{	return mgl_get_obj_id(gr,x,y);	}
	/// Get subplot id
	inline int GetSplId(long x,long y)	{	return mgl_get_spl_id(gr,x,y);	}

	/// Combine plots from 2 canvases. Result will be saved into this
	inline void Combine(const mglGraph *g)	{	mgl_combine_gr(gr,g->gr);	}
	/// Send graphical information to node id using MPI
	inline void MPI_Send(int id)	{	mgl_mpi_send(gr,id);	}
	/// Receive graphical information from node id using MPI
	inline void MPI_Recv(int id)	{	mgl_mpi_recv(gr,id);	}

	/// Clear up the frame
	inline void Clf(mreal r, mreal g, mreal b)	{	mgl_clf_rgb(gr, r, g, b);	}
	inline void Clf()	{	mgl_clf(gr);	}
	/// Draws the point (ball) at position {x,y,z} with color c
	inline void Ball(mglPoint p, char c)
	{	char s[3]={'.',c,0};	mgl_mark(gr, p.x, p.y, p.z, s);	}
	/// Draws the mark at position p
	inline void Mark(mglPoint p, const char *mark)
	{	mgl_mark(gr, p.x, p.y, p.z, mark);	}
	/// Draws the line between points by specified pen
	inline void Line(mglPoint p1, mglPoint p2, const char *pen="B",int n=2)
	{	mgl_line(gr, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, pen, n);	}
	/// Draws the spline curve between points by specified pen
	inline void Curve(mglPoint p1, mglPoint d1, mglPoint p2, mglPoint d2, const char *pen="B", int n=100)
	{	mgl_curve(gr, p1.x, p1.y, p1.z, d1.x, d1.y, d1.z, p2.x, p2.y, p2.z, d2.x, d2.y, d2.z, pen, n);	}
	/// Draws the 3d error box e for point p
	inline void Error(mglPoint p, mglPoint e, const char *pen="k")
	{	mgl_error_box(gr, p.x, p.y, p.z, e.x, e.y, e.z, pen);	}

	/// Draws the face between points with color stl (include interpolation up to 4 colors).
	inline void Face(mglPoint p1, mglPoint p2, mglPoint p3, mglPoint p4, const char *stl="r")
	{	mgl_face(gr, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z, p4.x, p4.y, p4.z, stl);	}
	/// Draws the face in y-z plane at point p with color stl (include interpolation up to 4 colors).
	inline void FaceX(mglPoint p, mreal wy, mreal wz, const char *stl="w", mreal dx=0, mreal dy=0)
	{	mgl_facex(gr, p.x, p.y, p.z, wy, wz, stl, dx, dy);	}
	/// Draws the face in x-z plane at point p with color stl (include interpolation up to 4 colors).
	inline void FaceY(mglPoint p, mreal wx, mreal wz, const char *stl="w", mreal dx=0, mreal dy=0)
	{	mgl_facey(gr, p.x, p.y, p.z, wx, wz, stl, dx, dy);	}
	/// Draws the face in x-y plane at point p with color stl (include interpolation up to 4 colors).
	inline void FaceZ(mglPoint p, mreal wx, mreal wy, const char *stl="w", mreal dx=0, mreal dy=0)
	{	mgl_facez(gr, p.x, p.y, p.z, wx, wy, stl, dx, dy);	}
	/// Draws the drop at point p in direction d with color col and radius r
	inline void Drop(mglPoint p, mglPoint d, mreal r, const char *col="r", mreal shift=1, mreal ap=1)
	{	mgl_drop(gr, p.x, p.y, p.z, d.x, d.y, d.z, r, col, shift, ap);	}
	/// Draws the sphere at point p with color col and radius r
	inline void Sphere(mglPoint p, mreal r, const char *col="r")
	{	mgl_sphere(gr, p.x, p.y, p.z, r, col);	}
	/// Draws the cone between points p1,p2 with radius r1,r2 with style stl
	inline void Cone(mglPoint p1, mglPoint p2, mreal r1, mreal r2=-1, const char *stl="r@")
	{	mgl_cone(gr, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z,r1,r2,stl);	}
	/// Draws the ellipse between points p1,p2 with color stl and width r
	inline void Ellipse(mglPoint p1, mglPoint p2, mreal r, const char *stl="r")
	{	mgl_ellipse(gr, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, r,stl);	}
	/// Draws the circle at point p with color stl and radius r
	inline void Circle(mglPoint p, mreal r, const char *stl="r")
	{	mgl_ellipse(gr, p.x, p.y, p.z, p.x, p.y, p.z, r,stl);	}
	/// Draws the rhomb between points p1,p2 with color stl and width r
	inline void Rhomb(mglPoint p1, mglPoint p2, mreal r, const char *stl="r")
	{	mgl_rhomb(gr, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, r,stl);	}

	/// Print text in position p with specified font
	inline void Putsw(mglPoint p,const wchar_t *text,const char *font=":C",mreal size=-1)
	{	mgl_putsw(gr, p.x, p.y, p.z, text, font, size);	}
	inline void Puts(mglPoint p,const char *text,const char *font=":C",mreal size=-1)
	{	mgl_puts(gr, p.x, p.y, p.z, text, font, size);	}
	inline void Putsw(mreal x, mreal y,const wchar_t *text,const char *font=":AC",mreal size=-1)
	{	mgl_putsw(gr, x, y, 0, text, font, size);	}
	inline void Puts(mreal x, mreal y,const char *text,const char *font=":AC",mreal size=-1)
	{	mgl_puts(gr, x, y, 0, text, font, size);	}
	/// Print text in position p along direction d with specified font
	inline void Putsw(mglPoint p, mglPoint d, const wchar_t *text, const char *font=":L", mreal size=-1)
	{	mgl_putsw_dir(gr, p.x, p.y, p.z, d.x, d.y, d.z, text, font, size);	}
	inline void Puts(mglPoint p, mglPoint d, const char *text, const char *font=":L", mreal size=-1)
	{	mgl_puts_dir(gr, p.x, p.y, p.z, d.x, d.y, d.z, text, font, size);	}

	/// Print text along the curve
	inline void Text(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *text, const char *font="", const char *opt="")
	{	mgl_text_xyz(gr, &x, &y, &z, text, font, opt);	}
	inline void Text(const mglDataA &x, const mglDataA &y, const char *text, const char *font="", const char *opt="")
	{	mgl_text_xy(gr, &x, &y, text, font, opt);	}
	inline void Text(const mglDataA &y, const char *text, const char *font="", const char *opt="")
	{	mgl_text_y(gr, &y, text, font, opt);	}
	inline void Text(const mglDataA &x, const mglDataA &y, const mglDataA &z, const wchar_t *text, const char *font="", const char *opt="")
	{	mgl_textw_xyz(gr, &x, &y, &z, text, font, opt);	}
	inline void Text(const mglDataA &x, const mglDataA &y, const wchar_t *text, const char *font="", const char *opt="")
	{	mgl_textw_xy(gr, &x, &y, text, font, opt);	}
	inline void Text(const mglDataA &y, const wchar_t *text, const char *font="", const char *opt="")
	{	mgl_textw_y(gr, &y, text, font, opt);	}

	/// Draws bounding box outside the plotting volume with color \a c.
	inline void Box(const char *col="", bool ticks=true)
	{	mgl_box_str(gr, col, ticks);	}
	/// Draw axises with ticks in directions determined by string parameter \a dir.
	inline void Axis(const char *dir="xyzt", const char *stl="")
	{	mgl_axis(gr, dir,stl);	}
	/// Draw grid lines perpendicular to direction determined by string parameter \a dir.
	inline void Grid(const char *dir="xyzt",const char *pen="B")
	{	mgl_axis_grid(gr, dir, pen);	}
	/// Print the label \a text for axis \a dir.
	inline void Label(char dir, const char *text, mreal pos=+1, mreal shift=0)
	{	mgl_label_ext(gr, dir, text, pos, shift);	}
	inline void Label(char dir, const wchar_t *text, mreal pos=+1, mreal shift=0)
	{	mgl_labelw_ext(gr, dir, text, pos, shift);	}

	/// Draw colorbar at edge of axis
	inline void Colorbar(const char *sch="")
	{	mgl_colorbar(gr, sch);	}
	inline void Colorbar(const char *sch,mreal x,mreal y,mreal w=1,mreal h=1)
	{	mgl_colorbar_ext(gr, sch, x,y,w,h);	}
	/// Draw colorbar with manual colors at edge of axis
	inline void Colorbar(const mglDataA &val, const char *sch="")
	{	mgl_colorbar_val(gr, &val, sch);	}
	inline void Colorbar(const mglDataA &val, const char *sch,mreal x,mreal y,mreal w=1,mreal h=1)
	{	mgl_colorbar_val_ext(gr, &val, sch, x,y,w,h);	}

	/// Add string to legend
	inline void AddLegend(const char *text,const char *style)
	{	mgl_add_legend(gr, text, style);	}
	inline void AddLegend(const wchar_t *text,const char *style)
	{	mgl_add_legendw(gr, text, style);	}
	/// Clear saved legend string
	inline void ClearLegend()
	{	mgl_clear_legend(gr);	}
	/// Draw legend of accumulated strings at position {x,y}
	inline void Legend(mreal x, mreal y, const char *font="#", mreal size=-0.8, mreal llen=0)
	{	mgl_legend_pos(gr, x, y, font, size, llen);	}
	/// Draw legend of accumulated strings
	inline void Legend(int where=3, const char *font="#", mreal size=-0.8, mreal llen=0)
	{	mgl_legend(gr, where, font, size, llen);	}
	/// Set number of marks in legend sample
	inline void SetLegendMarks(int num)		{	mgl_set_legend_marks(gr, num);	}

	/// Draw usual curve {x,y,z}
	inline void Plot(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_plot_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Plot(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_plot_xy(gr, &x, &y, pen,opt);	}
	inline void Plot(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_plot(gr, &y, pen,opt);	}
	/// Draw tape(s) which rotates as (bi-)normales of curve {x,y,z}
	inline void Tape(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_tape_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Tape(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_tape_xy(gr, &x, &y, pen,opt);	}
	inline void Tape(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_tape(gr, &y, pen,opt);	}
	/// Draw radar chart (plot in curved coordinates)
	inline void Radar(const mglDataA &a, const char *pen="", const char *opt="")
	{	mgl_radar(gr, &a, pen, opt);	}
	/// Draw stairs for points in arrays {x,y,z}
	inline void Step(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_step_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Step(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_step_xy(gr, &x, &y, pen, opt);	}
	inline void Step(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_step(gr, &y, pen, opt);	}
	/// Draw curve {x,y,z} which is colored by c (like tension plot)
	inline void Tens(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &c, const char *pen="", const char *opt="")
	{	mgl_tens_xyz(gr, &x, &y, &z, &c, pen, opt);	}
	inline void Tens(const mglDataA &x, const mglDataA &y, const mglDataA &c, const char *pen="", const char *opt="")
	{	mgl_tens_xy(gr, &x, &y, &c, pen, opt);	}
	inline void Tens(const mglDataA &y, const mglDataA &c, const char *pen="", const char *opt="")
	{	mgl_tens(gr, &y, &c, pen, opt);	}
	/// Fill area between curve {x,y,z} and axis plane
	inline void Area(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_area_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Area(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_area_xy(gr, &x, &y, pen, opt);	}
	inline void Area(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_area(gr, &y, pen, opt);	}
	/// Fill area between curves y1 and y2 specified parametrically
	inline void Region(const mglDataA &y1, const mglDataA &y2, const char *pen="", const char *opt="")
	{	mgl_region(gr, &y1, &y2, pen, opt);	}
	inline void Region(const mglDataA &x, const mglDataA &y1, const mglDataA &y2, const char *pen="", const char *opt="")
	{	mgl_region_xy(gr, &x, &y1, &y2, pen, opt);	}
	/// Draw vertical lines from points {x,y,z} to axis plane
	inline void Stem(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_stem_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Stem(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_stem_xy(gr, &x, &y, pen, opt);	}
	inline void Stem(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_stem(gr, &y, pen, opt);	}

	/// Draw vertical bars from points {x,y,z} to axis plane
	inline void Bars(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_bars_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Bars(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_bars_xy(gr, &x, &y, pen, opt);	}
	inline void Bars(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_bars(gr, &y, pen, opt);	}
	/// Draw horizontal bars from points {x,y} to axis plane
	inline void Barh(const mglDataA &y, const mglDataA &v, const char *pen="", const char *opt="")
	{	mgl_barh_yx(gr, &y, &v, pen, opt);	}
	inline void Barh(const mglDataA &v, const char *pen="", const char *opt="")
	{	mgl_barh(gr, &v, pen, opt);	}
	/// Draw chart for data a
	inline void Chart(const mglDataA &a, const char *colors="", const char *opt="")
	{	mgl_chart(gr, &a, colors,opt);	}
	/// Draw box-plot (special 5-value plot used in statistic)
	inline void BoxPlot(const mglDataA &x, const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_boxplot_xy(gr, &x, &y, pen,opt);	}
	inline void BoxPlot(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_boxplot(gr, &y, pen,opt);	}
	/// Draw candle plot
	inline void Candle(const mglDataA &x, const mglDataA &v1, const mglDataA &v2, const mglDataA &y1, const mglDataA &y2, const char *pen="", const char *opt="")
	{	mgl_candle_xyv(gr, &x, &v1, &v2, &y1, &y2, pen, opt);	}
	inline void Candle(const mglDataA &v1, const mglDataA &v2, const mglDataA &y1, const mglDataA &y2, const char *pen="", const char *opt="")
	{	mgl_candle_yv(gr, &v1, &v2, &y1, &y2, pen, opt);	}
	inline void Candle(const mglDataA &v1, const mglDataA &v2, const char *pen="", const char *opt="")
	{	mgl_candle_yv(gr, &v1, &v2, NULL, NULL, pen, opt);	}
	inline void Candle(const mglDataA &y, const mglDataA &y1, const mglDataA &y2, const char *pen="", const char *opt="")
	{	mgl_candle(gr, &y, &y1, &y2, pen, opt);	}
	inline void Candle(const mglDataA &y, const char *pen="", const char *opt="")
	{	mgl_candle(gr, &y, NULL, NULL, pen, opt);	}
	/// Draw cones from points {x,y,z} to axis plane
	inline void Cones(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *pen="@", const char *opt="")
	{	mgl_cones_xyz(gr, &x, &y, &z, pen, opt);	}
	inline void Cones(const mglDataA &x, const mglDataA &z, const char *pen="@", const char *opt="")
	{	mgl_cones_xz(gr, &x, &z, pen, opt);	}
	inline void Cones(const mglDataA &z, const char *pen="@", const char *opt="")
	{	mgl_cones(gr, &z, pen, opt);	}

	/// Draw error boxes {ex,ey} at points {x,y}
	inline void Error(const mglDataA &y, const mglDataA &ey, const char *pen="", const char *opt="")
	{	mgl_error(gr, &y, &ey, pen, opt);	}
	inline void Error(const mglDataA &x, const mglDataA &y, const mglDataA &ey, const char *pen="", const char *opt="")
	{	mgl_error_xy(gr, &x, &y, &ey, pen, opt);	}
	inline void Error(const mglDataA &x, const mglDataA &y, const mglDataA &ex, const mglDataA &ey, const char *pen="", const char *opt="")
	{	mgl_error_exy(gr, &x, &y, &ex, &ey, pen, opt);	}
	/// Draw marks with size r at points {x,y,z}
	inline void Mark(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &r, const char *pen, const char *opt="")
	{	mgl_mark_xyz(gr, &x, &y, &z, &r, pen, opt);	}
	inline void Mark(const mglDataA &x, const mglDataA &y, const mglDataA &r, const char *pen, const char *opt="")
	{	mgl_mark_xy(gr, &x, &y, &r, pen, opt);	}
	inline void Mark(const mglDataA &y, const mglDataA &r, const char *pen, const char *opt="")
	{	mgl_mark_y(gr, &y, &r, pen, opt);	}
	/// Draw textual marks with size r at points {x,y,z}
	inline void TextMark(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &r, const char *text, const char *fnt="", const char *opt="")
	{	mgl_textmark_xyzr(gr, &x, &y, &z, &r, text, fnt, opt);	}
	inline void TextMark(const mglDataA &x, const mglDataA &y, const mglDataA &r, const char *text, const char *fnt="", const char *opt="")
	{	mgl_textmark_xyr(gr, &x, &y, &r, text, fnt, opt);	}
	inline void TextMark(const mglDataA &y, const mglDataA &r, const char *text, const char *fnt="", const char *opt="")
	{	mgl_textmark_yr(gr, &y, &r, text, fnt, opt);	}
	inline void TextMark(const mglDataA &y, const char *text, const char *fnt="", const char *opt="")
	{	mgl_textmark(gr, &y, text, fnt, opt);	}
	inline void TextMark(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &r, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_textmarkw_xyzr(gr, &x, &y, &z, &r, text, fnt, opt);	}
	inline void TextMark(const mglDataA &x, const mglDataA &y, const mglDataA &r, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_textmarkw_xyr(gr, &x, &y, &r, text, fnt, opt);	}
	inline void TextMark(const mglDataA &y, const mglDataA &r, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_textmarkw_yr(gr, &y, &r, text, fnt, opt);	}
	inline void TextMark(const mglDataA &y, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_textmarkw(gr, &y, text, fnt, opt);	}

	/// Draw labels for points coordinate(s) at points {x,y,z}
	inline void Label(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *text, const char *fnt="", const char *opt="")
	{	mgl_label_xyz(gr, &x, &y, &z, text, fnt, opt);	}
	inline void Label(const mglDataA &x, const mglDataA &y, const char *text, const char *fnt="", const char *opt="")
	{	mgl_label_xy(gr, &x, &y, text, fnt, opt);	}
	inline void Label(const mglDataA &y, const char *text, const char *fnt="", const char *opt="")
	{	mgl_label_y(gr, &y, text, fnt, opt);	}
	inline void Label(const mglDataA &x, const mglDataA &y, const mglDataA &z, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_labelw_xyz(gr, &x, &y, &z, text, fnt, opt);	}
	inline void Label(const mglDataA &x, const mglDataA &y, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_labelw_xy(gr, &x, &y, text, fnt, opt);	}
	inline void Label(const mglDataA &y, const wchar_t *text, const char *fnt="", const char *opt="")
	{	mgl_labelw_y(gr, &y, text, fnt, opt);	}

	/// Draw tube with radius r for points in arrays {x,y,z}
	inline void Tube(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &r, const char *pen="", const char *opt="")
	{	mgl_tube_xyzr(gr, &x, &y, &z, &r, pen, opt);	}
	inline void Tube(const mglDataA &x, const mglDataA &y, const mglDataA &z, mreal r, const char *pen="", const char *opt="")
	{	mgl_tube_xyz(gr, &x, &y, &z, r, pen, opt);	}
	inline void Tube(const mglDataA &x, const mglDataA &y, const mglDataA &r, const char *pen="", const char *opt="")
	{	mgl_tube_xyr(gr, &x, &y, &r, pen, opt);	}
	inline void Tube(const mglDataA &x, const mglDataA &y, mreal r, const char *pen="", const char *opt="")
	{	mgl_tube_xy(gr, &x, &y, r, pen, opt);	}
	inline void Tube(const mglDataA &y, const mglDataA &r, const char *pen="", const char *opt="")
	{	mgl_tube_r(gr, &y, &r, pen, opt);	}
	inline void Tube(const mglDataA &y, mreal r, const char *pen="", const char *opt="")
	{	mgl_tube(gr, &y, r, pen, opt);	}
	/// Draw surface of curve {r,z} rotatation around axis
	inline void Torus(const mglDataA &r, const mglDataA &z, const char *pen="", const char *opt="")
	{	mgl_torus(gr, &r, &z, pen,opt);	}

	/// Draw mesh lines for 2d data specified parametrically
	inline void Mesh(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_mesh_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Mesh(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_mesh(gr, &z, stl, opt);	}
	/// Draw mesh lines for 2d data specified parametrically
	inline void Fall(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_fall_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Fall(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_fall(gr, &z, stl, opt);	}
	/// Draw belts for 2d data specified parametrically
	inline void Belt(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_belt_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Belt(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_belt(gr, &z, stl, opt);	}
	/// Draw surface for 2d data specified parametrically with color proportional to z
	inline void Surf(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_surf_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Surf(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_surf(gr, &z, stl, opt);	}
	/// Draw grid lines for density plot of 2d data specified parametrically
	inline void Grid(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_grid_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Grid(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_grid(gr, &z, stl, opt);	}
	/// Draw vertical tiles for 2d data specified parametrically
	inline void Tile(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_tile_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Tile(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_tile(gr, &z, stl, opt);	}
	/// Draw density plot for 2d data specified parametrically
	inline void Dens(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_dens_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Dens(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_dens(gr, &z, stl, opt);	}
	/// Draw vertical boxes for 2d data specified parametrically
	inline void Boxs(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_boxs_xy(gr, &x, &y, &z, stl, opt);	}
	inline void Boxs(const mglDataA &z, const char *stl="", const char *opt="")
	{	mgl_boxs(gr, &z, stl, opt);	}

	/// Draw contour lines for 2d data specified parametrically
	inline void Cont(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_cont_xy_val(gr, &v, &x, &y, &z, sch, opt);	}
	inline void Cont(const mglDataA &v, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_cont_val(gr, &v, &z, sch, opt);	}
	inline void Cont(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_cont_xy(gr, &x, &y, &z, sch, opt);	}
	inline void Cont(const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_cont(gr, &z, sch, opt);	}
	/// Draw solid contours for 2d data specified parametrically
	inline void ContF(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contf_xy_val(gr, &v, &x, &y, &z, sch, opt);	}
	inline void ContF(const mglDataA &v, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contf_val(gr, &v, &z, sch, opt);	}
	inline void ContF(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contf_xy(gr, &x, &y, &z, sch, opt);	}
	inline void ContF(const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contf(gr, &z, sch, opt);	}
	/// Draw solid contours for 2d data specified parametrically with manual colors
	inline void ContD(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contd_xy_val(gr, &v, &x, &y, &z, sch, opt);	}
	inline void ContD(const mglDataA &v, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contd_val(gr, &v, &z, sch, opt);	}
	inline void ContD(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contd_xy(gr, &x, &y, &z, sch, opt);	}
	inline void ContD(const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contd(gr, &z, sch, opt);	}
	/// Draw contour lines for 2d data specified parametrically
	inline void ContV(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contv_xy_val(gr, &v, &x, &y, &z, sch, opt);	}
	inline void ContV(const mglDataA &v, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contv_val(gr, &v, &z, sch, opt);	}
	inline void ContV(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contv_xy(gr, &x, &y, &z, sch, opt);	}
	inline void ContV(const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_contv(gr, &z, sch, opt);	}
	/// Draw axial-symmetric isosurfaces for 2d data specified parametrically
	inline void Axial(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_axial_xy_val(gr, &v, &x, &y, &z, sch,opt);	}
	inline void Axial(const mglDataA &v, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_axial_val(gr, &v, &z, sch, opt);	}
	inline void Axial(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_axial_xy(gr, &x, &y, &z, sch, opt);	}
	inline void Axial(const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_axial(gr, &z, sch, opt);	}

	/// Draw grid lines for density plot at slice for 3d data specified parametrically
	inline void Grid3(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *stl="", mreal sVal=-1, const char *opt="")
	{	mgl_grid3_xyz(gr, &x, &y, &z, &a, stl, sVal, opt);	}
	inline void Grid3(const mglDataA &a, const char *stl="", mreal sVal=-1, const char *opt="")
	{	mgl_grid3(gr, &a, stl, sVal, opt);	}
	/// Draw density plot at slice for 3d data specified parametrically
	inline void Dens3(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *stl="", mreal sVal=-1, const char *opt="")
	{	mgl_dens3_xyz(gr, &x, &y, &z, &a, stl, sVal, opt);	}
	inline void Dens3(const mglDataA &a, const char *stl="", mreal sVal=-1, const char *opt="")
	{	mgl_dens3(gr, &a, stl, sVal, opt);	}

	/// Draw isosurface(s) for 3d data specified parametrically
	inline void Surf3(mreal Val, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *stl="", const char *opt="")
	{	mgl_surf3_xyz_val(gr, Val, &x, &y, &z, &a, stl, opt);	}
	inline void Surf3(mreal Val, const mglDataA &a, const char *stl="", const char *opt="")
	{	mgl_surf3_val(gr, Val, &a, stl, opt);	}
	inline void Surf3(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *stl="", const char *opt="")
	{	mgl_surf3_xyz(gr, &x, &y, &z, &a, stl, opt);	}
	inline void Surf3(const mglDataA &a, const char *stl="", const char *opt="")
	{	mgl_surf3(gr, &a, stl, opt);	}

	/// Draw a semi-transparent cloud for 3d data
	inline void Cloud(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *stl="", const char *opt="")
	{	mgl_cloud_xyz(gr, &x, &y, &z, &a, stl, opt);	}
	inline void Cloud(const mglDataA &a, const char *stl="", const char *opt="")
	{	mgl_cloud(gr, &a, stl, opt);	}

	/// Draw contour lines at slice for 3d data specified parametrically
	inline void Cont3(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_cont3_xyz_val(gr, &v, &x, &y, &z, &a, sch, sVal, opt);	}
	inline void Cont3(const mglDataA &v, const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_cont3_val(gr, &v, &a, sch, sVal, opt);	}
	inline void Cont3(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_cont3_xyz(gr, &x, &y, &z, &a, sch, sVal, opt);	}
	inline void Cont3(const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_cont3(gr, &a, sch, sVal, opt);	}

	/// Draw solid contours at slice for 3d data specified parametrically
	inline void ContF3(const mglDataA &v, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_contf3_xyz_val(gr, &v, &x, &y, &z, &a, sch, sVal, opt);	}
	inline void ContF3(const mglDataA &v, const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_contf3_val(gr, &v, &a, sch, sVal, opt);	}
	inline void ContF3(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_contf3_xyz(gr, &x, &y, &z, &a, sch, sVal, opt);	}
	inline void ContF3(const mglDataA &a, const char *sch="", mreal sVal=-1, const char *opt="")
	{	mgl_contf3(gr, &a, sch, sVal, opt);	}

	/// Draw several isosurfaces for 3d beam in curvilinear coordinates
	inline void Beam(const mglDataA &tr, const mglDataA &g1, const mglDataA &g2, const mglDataA &a, mreal r, const char *stl=0, int flag=0, int num=3)
	{	mgl_beam(gr, &tr,&g1,&g2,&a,r,stl,flag,num);	}
	inline void Beam(mreal val, const mglDataA &tr, const mglDataA &g1, const mglDataA &g2, const mglDataA &a, mreal r, const char *stl=NULL, int flag=0)
	{	mgl_beam_val(gr,val,&tr,&g1,&g2,&a,r,stl,flag);	}

	/// Draw vertical tiles with variable size for 2d data specified parametrically
	inline void TileS(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &r, const char *stl="", const char *opt="")
	{	mgl_tiles_xy(gr, &x, &y, &z, &r, stl, opt);	}
	inline void TileS(const mglDataA &z, const mglDataA &r, const char *stl="", const char *opt="")
	{	mgl_tiles(gr, &z, &r, stl, opt);	}
	/// Draw surface for 2d data specified parametrically with color proportional to c
	inline void SurfC(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &c, const char *sch="", const char *opt="")
	{	mgl_surfc_xy(gr, &x, &y, &z, &c, sch,opt);	}
	inline void SurfC(const mglDataA &z, const mglDataA &c, const char *sch="", const char *opt="")
	{	mgl_surfc(gr, &z, &c, sch,opt);	}
	/// Draw surface for 2d data specified parametrically with alpha proportional to c
	inline void SurfA(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &c, const char *sch="", const char *opt="")
	{	mgl_surfa_xy(gr, &x, &y, &z, &c, sch,opt);	}
	inline void SurfA(const mglDataA &z, const mglDataA &c, const char *sch="", const char *opt="")
	{	mgl_surfa(gr, &z, &c, sch,opt);	}
	/// Color map of matrix a to matrix b, both matrix can parametrically depend on coordinates
	inline void Map(const mglDataA &x, const mglDataA &y, const mglDataA &a, const mglDataA &b, const char *sch="", const char *opt="")
	{	mgl_map_xy(gr, &x, &y, &a, &b, sch, opt);	}
	inline void Map(const mglDataA &a, const mglDataA &b, const char *sch="", const char *opt="")
	{	mgl_map(gr, &a, &b, sch, opt);	}
	/// Draw density plot for spectra-gramm specified parametrically
	inline void STFA(const mglDataA &x, const mglDataA &y, const mglDataA &re, const mglDataA &im, int dn, const char *sch="", const char *opt="")
	{	mgl_stfa_xy(gr, &x, &y, &re, &im, dn, sch, opt);	}
	inline void STFA(const mglDataA &re, const mglDataA &im, int dn, const char *sch="", const char *opt="")
	{	mgl_stfa(gr, &re, &im, dn, sch, opt);	}

	/// Draw isosurface(s) for 3d data specified parametrically with alpha proportional to b
	inline void Surf3A(mreal Val, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3a_xyz_val(gr, Val, &x, &y, &z, &a, &b, stl, opt);	}
	inline void Surf3A(mreal Val, const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3a_val(gr, Val, &a, &b, stl, opt);	}
	inline void Surf3A(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3a_xyz(gr, &x, &y, &z, &a, &b, stl, opt);	}
	inline void Surf3A(const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3a(gr, &a, &b, stl, opt);	}
	/// Draw isosurface(s) for 3d data specified parametrically with color proportional to b
	inline void Surf3C(mreal Val, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3c_xyz_val(gr, Val, &x, &y, &z, &a, &b, stl,opt);	}
	inline void Surf3C(mreal Val, const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3c_val(gr, Val, &a, &b, stl, opt);	}
	inline void Surf3C(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3c_xyz(gr, &x, &y, &z, &a, &b, stl, opt);	}
	inline void Surf3C(const mglDataA &a, const mglDataA &b, const char *stl="", const char *opt="")
	{	mgl_surf3c(gr, &a, &b, stl, opt);	}

	/// Plot dew drops for vector field {ax,ay} parametrically depended on coordinate {x,y}
	inline void Dew(const mglDataA &x, const mglDataA &y, const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_dew_xy(gr, &x, &y, &ax, &ay, sch, opt);	}
	inline void Dew(const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_dew_2d(gr, &ax, &ay, sch, opt);	}
	/// Plot vectors at position {x,y,z} along {ax,ay,az} with length/color proportional to |a|
	inline void Traj(const mglDataA &x, const mglDataA &y, const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_traj_xy(gr, &x, &y, &ax, &ay, sch, opt);	}
	inline void Traj(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_traj_xyz(gr, &x, &y, &z, &ax, &ay, &az, sch, opt);	}
	/// Plot vector field {ax,ay,ay} parametrically depended on coordinate {x,y,z} with length/color proportional to |a|
	inline void Vect(const mglDataA &x, const mglDataA &y, const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_vect_xy(gr, &x, &y, &ax, &ay, sch, opt);	}
	inline void Vect(const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_vect_2d(gr, &ax, &ay, sch, opt);	}
	inline void Vect(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_vect_xyz(gr, &x, &y, &z, &ax, &ay, &az, sch, opt);	}
	inline void Vect(const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_vect_3d(gr, &ax, &ay, &az, sch, opt);	}

	/// Plot flows for vector field {ax,ay,ay} parametrically depended on coordinate {x,y,z} with color proportional to |a|
	inline void Flow(const mglDataA &x, const mglDataA &y, const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_flow_xy(gr, &x, &y, &ax, &ay, sch, opt);	}
	inline void Flow(const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_flow_2d(gr, &ax, &ay, sch, opt);	}
	inline void Flow(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_flow_xyz(gr, &x, &y, &z, &ax, &ay, &az, sch, opt);	}
	inline void Flow(const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_flow_3d(gr, &ax, &ay, &az, sch, opt);	}
	/// Plot flow from point p for vector field {ax,ay,ay} parametrically depended on coordinate {x,y,z} with color proportional to |a|
	inline void FlowP(mglPoint p, const mglDataA &x, const mglDataA &y, const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_flowp_xy(gr, p.x, p.y, p.z, &x, &y, &ax, &ay, sch, opt);	}
	inline void FlowP(mglPoint p, const mglDataA &ax, const mglDataA &ay, const char *sch="", const char *opt="")
	{	mgl_flowp_2d(gr, p.x, p.y, p.z, &ax, &ay, sch, opt);	}
	inline void FlowP(mglPoint p, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_flowp_xyz(gr, p.x, p.y, p.z, &x, &y, &z, &ax, &ay, &az, sch, opt);	}
	inline void FlowP(mglPoint p, const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", const char *opt="")
	{	mgl_flowp_3d(gr, p.x, p.y, p.z, &ax, &ay, &az, sch, opt);	}

	/// Plot flows for gradient of scalar field phi parametrically depended on coordinate {x,y,z}
	inline void Grad(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &phi, const char *sch="", const char *opt="")
	{	mgl_grad_xyz(gr,&x,&y,&z,&phi,sch,opt);	}
	inline void Grad(const mglDataA &x, const mglDataA &y, const mglDataA &phi, const char *sch="", const char *opt="")
	{	mgl_grad_xy(gr,&x,&y,&phi,sch,opt);	}
	inline void Grad(const mglDataA &phi, const char *sch="", const char *opt="")
	{	mgl_grad(gr,&phi,sch,opt);	}

	/// Plot flow pipes for vector field {ax,ay,ay} parametrically depended on coordinate {x,y,z} with color proportional to |a|
	inline void Pipe(const mglDataA &x, const mglDataA &y, const mglDataA &ax, const mglDataA &ay, const char *sch="", mreal r0=0.05, const char *opt="")
	{	mgl_pipe_xy(gr, &x, &y, &ax, &ay, sch, r0, opt);	}
	inline void Pipe(const mglDataA &ax, const mglDataA &ay, const char *sch="", mreal r0=0.05, const char *opt="")
	{	mgl_pipe_2d(gr, &ax, &ay, sch, r0, opt);	}
	inline void Pipe(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", mreal r0=0.05, const char *opt="")
	{	mgl_pipe_xyz(gr, &x, &y, &z, &ax, &ay, &az, sch, r0, opt);	}
	inline void Pipe(const mglDataA &ax, const mglDataA &ay, const mglDataA &az, const char *sch="", mreal r0=0.05, const char *opt="")
	{	mgl_pipe_3d(gr, &ax, &ay, &az, sch, r0, opt);	}

	/// Draw density plot for data at x = sVal
	inline void DensX(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_dens_x(gr, &a, stl, sVal, opt);	}
	/// Draw density plot for data at y = sVal
	inline void DensY(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_dens_y(gr, &a, stl, sVal, opt);	}
	/// Draw density plot for data at z = sVal
	inline void DensZ(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_dens_z(gr, &a, stl, sVal, opt);	}
	/// Draw contour plots for data at x = sVal
	inline void ContX(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_cont_x(gr, &a, stl, sVal, opt);	}
	inline void ContX(const mglDataA &v, const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_cont_x_val(gr, &v, &a, stl, sVal, opt);	}
	/// Draw contour plots for data at y = sVal
	inline void ContY(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_cont_y(gr, &a, stl, sVal, opt);	}
	inline void ContY(const mglDataA &v, const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_cont_y_val(gr, &v, &a, stl, sVal, opt);	}
	/// Draw contour plots for data at z = sVal
	inline void ContZ(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_cont_z(gr, &a, stl, sVal, opt);	}
	inline void ContZ(const mglDataA &v, const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_cont_z_val(gr, &v, &a, stl, sVal, opt);	}
	/// Draw solid contour plots for data at x = sVal
	inline void ContFX(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_contf_x(gr, &a, stl, sVal, opt);	}
	inline void ContFX(const mglDataA &v, const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_contf_x_val(gr, &v, &a, stl, sVal, opt);	}
	/// Draw solid contour plots for data at y = sVal
	inline void ContFY(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_contf_y(gr, &a, stl, sVal, opt);	}
	inline void ContFY(const mglDataA &v, const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_contf_y_val(gr, &v, &a, stl, sVal, opt);	}
	/// Draw solid contour plots for data at z = sVal
	inline void ContFZ(const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_contf_z(gr, &a, stl, sVal, opt);	}
	inline void ContFZ(const mglDataA &v, const mglDataA &a, const char *stl="", mreal sVal=NaN, const char *opt="")
	{	mgl_contf_z_val(gr, &v, &a, stl, sVal, opt);	}

	/// Draw curve for formula with x in range [Min.x, Max.x]
	inline void FPlot(const char *fy, const char *stl="", const char *opt="")
	{	mgl_fplot(gr, fy, stl, opt);	}
	/// Draw curve for formulas parametrically depended on t in range [0,1]
	inline void FPlot(const char *fx, const char *fy, const char *fz, const char *stl, const char *opt="")
	{	mgl_fplot_xyz(gr, fx, fy, fz, stl, opt);	}
	/// Draw surface by formula with x,y in range [Min, Max]
	inline void FSurf(const char *fz, const char *stl="", const char *opt="")
	{	mgl_fsurf(gr, fz, stl, opt);	}
	/// Draw surface by formulas parametrically depended on u,v in range [0,1]
	inline void FSurf(const char *fx, const char *fy, const char *fz, const char *stl, const char *opt="")
	{	mgl_fsurf_xyz(gr, fx, fy, fz, stl, opt);	}

	/// Draw triangle mesh for points in arrays {x,y,z} with specified color c.
	inline void TriPlot(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &c, const char *sch="", const char *opt="")
	{	mgl_triplot_xyzc(gr, &nums, &x, &y, &z, &c, sch, opt);	}
	inline void TriPlot(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_triplot_xyz(gr, &nums, &x, &y, &z, sch, opt);	}
	inline void TriPlot(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const char *sch="", const char *opt="")
	{	mgl_triplot_xy(gr, &nums, &x, &y, sch, opt);	}
	/// Draw quad mesh for points in arrays {x,y,z} with specified color c.
	inline void QuadPlot(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &c, const char *sch="", const char *opt="")
	{	mgl_quadplot_xyzc(gr, &nums, &x, &y, &z, &c, sch, opt);	}
	inline void QuadPlot(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_quadplot_xyz(gr, &nums, &x, &y, &z, sch, opt);	}
	inline void QuadPlot(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const char *sch="", const char *opt="")
	{	mgl_quadplot_xy(gr, &nums, &x, &y, sch, opt);	}

	/// Draw contour lines for triangle mesh for points in arrays {x,y,z}.
	inline void TriCont(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_tricont_xyc(gr, &nums, &x, &y, &z, sch, opt);	}
	inline void TriContV(const mglDataA &v, const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_tricont_xycv(gr, &v, &nums, &x, &y, &z, sch, opt);	}
	inline void TriCont(const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", const char *opt="")
	{	mgl_tricont_xyzc(gr, &nums, &x, &y, &z, &a, sch, opt);	}
	inline void TriContV(const mglDataA &v, const mglDataA &nums, const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", const char *opt="")
	{	mgl_tricont_xyzcv(gr, &v, &nums, &x, &y, &z, &a, sch, opt);	}

	/// Draw dots in points {x,y,z}.
	inline void Dots(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_dots(gr, &x, &y, &z, sch, opt);	}
	/// Draw semitransparent dots in points {x,y,z}.
	inline void Dots(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *sch="", const char *opt="")
	{	mgl_dots_a(gr, &x, &y, &z, &a, sch, opt);	}
	/// Draw surface reconstructed for points in arrays {x,y,z}.
	inline void Crust(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *sch="", const char *opt="")
	{	mgl_crust(gr, &x, &y, &z, sch, opt);	}

	/// Fit data along x-direction for each data row. Return array with values for found formula.
	inline mglData Fit(const mglDataA &y, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_1(gr, &y, eq,var,0, opt));	}
	inline mglData Fit(const mglDataA &y, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_1(gr, &y, eq, var, &ini, opt));	}
	/// Fit data along x-, y-directions for each data slice. Return array with values for found formula.
	inline mglData Fit2(const mglDataA &z, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_2(gr, &z, eq, var,0, opt));	}
	inline mglData Fit2(const mglDataA &z, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_2(gr, &z, eq, var, &ini, opt));	}
	/// Fit data along along all directions. Return array with values for found formula.
	inline mglData Fit3(const mglDataA &a, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_3(gr, &a, eq, var,0, opt));	}
	inline mglData Fit3(const mglDataA &a, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_3(gr, &a, eq, var, &ini, opt));	}
	/// Fit data along x-direction for each data row. Return array with values for found formula.
	inline mglData Fit(const mglDataA &x, const mglDataA &y, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_xy(gr, &x, &y, eq, var,0, opt));	}
	inline mglData Fit(const mglDataA &x, const mglDataA &y, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_xy(gr, &x, &y, eq, var, &ini, opt));	}
	/// Fit data along x-, y-directions for each data slice. Return array with values for found formula.
	inline mglData Fit(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_xyz(gr, &x, &y, &z, eq, var,0, opt));	}
	inline mglData Fit(const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_xyz(gr, &x, &y, &z, eq, var, &ini, opt));	}
	/// Fit data along along all directions. Return array with values for found formula.
	inline mglData Fit(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_xyza(gr, &x, &y, &z, &a, eq, var,0, opt));	}
	inline mglData Fit(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_xyza(gr, &x, &y, &z, &a, eq,var, &ini, opt));	}
	/// Fit data with dispersion s along x-direction for each data row. Return array with values for found formula.
	inline mglData FitS(const mglDataA &y, const mglDataA &s, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_ys(gr, &y, &s, eq, var,0, opt));	}
	inline mglData FitS(const mglDataA &y, const mglDataA &s, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_ys(gr, &y, &s, eq, var, &ini, opt));	}
	inline mglData FitS(const mglDataA &x, const mglDataA &y, const mglDataA &s, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_xys(gr, &x, &y, &s, eq, var,0, opt));	}
	inline mglData FitS(const mglDataA &x, const mglDataA &y, const mglDataA &s, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_xys(gr, &x, &y, &s, eq, var, &ini, opt));	}
	/// Fit data with dispersion s along x-, y-directions for each data slice. Return array with values for found formula.
	inline mglData FitS(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &s, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_xyzs(gr, &x, &y, &z, &s, eq, var,0, opt));	}
	inline mglData FitS(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &s, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_xyzs(gr, &x, &y, &z, &s, eq, var, &ini, opt));	}
	/// Fit data with dispersion s along all directions. Return array with values for found formula.
	inline mglData FitS(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const mglDataA &s, const char *eq, const char *var, const char *opt="")
	{	return mglData(true,mgl_fit_xyzas(gr, &x, &y, &z, &a, &s, eq, var,0, opt));	}
	inline mglData FitS(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const mglDataA &s, const char *eq, const char *var, mglData &ini, const char *opt="")
	{	return mglData(true,mgl_fit_xyzas(gr, &x, &y, &z, &a, &s, eq, var, &ini, opt));	}
	/// Print fitted last formula (with coefficients)
	inline void PutsFit(mglPoint p, const char *prefix=0, const char *font=0, mreal size=-1)
	{	mgl_puts_fit(gr, p.x, p.y, p.z, prefix, font, size);	}
	/// Get last fitted formula
	inline const char *GetFit()
	{	return mgl_get_fit(gr);	}

	/// Solve PDE with x,y,z in range [Min, Max]
	inline mglData PDE(const char *ham, const mglDataA &ini_re, const mglDataA &ini_im, mreal dz=0.1, mreal k0=100, const char *opt="")
	{	return mglData(true,mgl_pde_solve(gr,ham,&ini_re,&ini_im,dz,k0, opt));	}
	/// Fill data by formula with x,y,z in range [Min, Max]
	inline void Fill(mglData &u, const char *eq, const char *opt="")
	{	mgl_data_fill_eq(gr, &u, eq, 0, 0, opt);	}
	inline void Fill(mglData &u, const char *eq, const mglDataA &v, const char *opt="")
	{	mgl_data_fill_eq(gr, &u, eq, &v, 0, opt);	}
	inline void Fill(mglData &u, const char *eq, const mglDataA &v, const mglDataA &w, const char *opt="")
	{	mgl_data_fill_eq(gr, &u, eq, &v, &w, opt);	}

	/// Set the data by triangulated surface values assuming x,y,z in range [Min, Max]
	inline void DataGrid(mglData &d, const mglDataA &x, const mglDataA &y, const mglDataA &z, const char *opt="")
	{	mgl_data_grid(gr,&d,&x,&y,&z,opt);	}
	
	/// Make histogram (distribution) of data. This function do not plot data.
	inline mglData Hist(const mglDataA &x, const mglDataA &a, const char *opt="")
	{	return mglData(true, mgl_hist_x(gr, &x, &a, opt));	}
	inline mglData Hist(const mglDataA &x, const mglDataA &y, const mglDataA &a, const char *opt="")
	{	return mglData(true, mgl_hist_xy(gr, &x, &y, &a, opt));	}
	inline mglData Hist(const mglDataA &x, const mglDataA &y, const mglDataA &z, const mglDataA &a, const char *opt="")
	{	return mglData(true, mgl_hist_xyz(gr, &x, &y, &z, &a, opt));	}

	inline void Compression(bool){}		// NOTE: Add later -- IDTF
	/// Set the preference for vertex color on/off (for formats that support it, now only PRC does).
	inline void VertexColor(bool enable)	{	mgl_set_flag(gr,enable, MGL_PREFERVC);	}
	/// Render only front side of surfaces for dubugging purposes (for formats that support it, now only PRC does).
	inline void DoubleSided(bool enable)	{	mgl_set_flag(gr,!enable, MGL_ONESIDED);	}
	inline void TextureColor(bool){}	// NOTE: Add later -- IDTF
};
//-----------------------------------------------------------------------------
/// Callback function for asking user a question. Result shouldn't exceed 1024.
extern void (*mgl_ask_func)(const wchar_t *quest, wchar_t *res);
//-----------------------------------------------------------------------------
/// Wrapper class for MGL parsing
class mglParse
{
	HMPR pr;
public:
	mglParse(HMPR p)		{	pr = p;		mgl_use_parser(pr,1);	}
	mglParse(mglParse &p)	{	pr = p.pr;	mgl_use_parser(pr,1);	}
	mglParse(bool setsize=false)
	{	pr=mgl_create_parser();	mgl_parser_allow_setsize(pr, setsize);	}
	~mglParse()	{	if(mgl_use_parser(pr,-1)<1)	mgl_delete_parser(pr);	}
	inline HMPR Self()	{	return pr;	}
	inline int Parse(mglGraph *gr, const char *str, int pos)
	{	return mgl_parse(gr->Self(), pr, str, pos);	}
	inline int Parse(mglGraph *gr, const wchar_t *str, int pos)
	{	return mgl_parsew(gr->Self(), pr, str, pos);	}
	inline void Execute(mglGraph *gr, const char *str)
	{	mgl_parse_text(gr->Self(), pr, str);	}
	inline void Execute(mglGraph *gr, const wchar_t *str)
	{	mgl_parsew_text(gr->Self(), pr, str);	}
	inline void Execute(mglGraph *gr, FILE *fp, bool print=false)
	{	mgl_parse_file(gr->Self(), pr, fp, print);	}
	inline int CmdType(const char *name)
	{	return mgl_cmd_type(pr, name);	}
	inline const char *CmdFormat(const char *name)
	{	return mgl_cmd_frmt(pr, name);	}
	inline const char *CmdDesc(const char *name)
	{	return mgl_cmd_desc(pr, name);	}

	inline void AddParam(int id, const char *str)	{	mgl_add_param(pr, id, str);	}
	inline void AddParam(int id, const wchar_t *str){	mgl_add_paramw(pr, id, str);	}
	inline void RestoreOnce()	{	mgl_restore_once(pr);	}
	inline void AllowSetSize(bool allow)	{	mgl_parser_allow_setsize(pr, allow);	}

	/*===!!! NOTE !!! You must not delete obtained data arrays !!!===============*/
	inline mglData *AddVar(const char *name)	{	return mgl_add_var(pr, name);	}
	/*===!!! NOTE !!! You must not delete obtained data arrays !!!===============*/
	inline mglData *FindVar(const char *name)	{	return mgl_find_var(pr, name);	}
	inline void DeleteVar(const char *name)		{	mgl_del_var(pr, name);		}
	inline void Stop()	{	mgl_parser_stop(pr);	}
};
//-----------------------------------------------------------------------------
/// Wrapper class expression evaluating
class mglExpr
{
	HMEX ex;
public:
	mglExpr(const char *expr)		{	ex = mgl_create_expr(expr);	}
	~mglExpr()	{	mgl_delete_expr(ex);	}
	inline mreal Eval(mreal x, mreal y=0, mreal z=0)
	{	return mgl_expr_eval(ex,x,y,z);	}
	inline mreal Diff(char dir, mreal x, mreal y=0, mreal z=0)
	{	return mgl_expr_diff(ex,dir, x,y,z);	}
#ifndef SWIG
	inline mreal Eval(mreal var[26])
	{	return mgl_expr_eval_v(ex,var);	}
	inline mreal Diff(char dir, mreal var[26])
	{	return mgl_expr_diff_v(ex,dir, var);	}
#endif
};
//-----------------------------------------------------------------------------
#endif
