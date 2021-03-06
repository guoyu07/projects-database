/***************************************************************************
 * base.h is part of Math Graphic Library
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
#ifndef _MGL_BASE_H_
#define _MGL_BASE_H_
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
#include <stdint.h>
#endif
#include "mgl2/define.h"
/*****************************************************************************/
#ifdef __cplusplus
#include <vector>
#include <string>
#include "mgl2/type.h"
#include "mgl2/eval.h"
#include "mgl2/font.h"
//-----------------------------------------------------------------------------
class mglBase;
class mglData;
class mglParser;
class mglFormula;
typedef mglBase*  HMGL;
typedef mglData* HMDT;
typedef mglParser* HMPR;
typedef mglFormula* HMEX;
//-----------------------------------------------------------------------------
#if MGL_NO_DATA_A
#define mglDataA mglData
typedef const mglData* HCDT;
#include "mgl2/data.h"
#else
/// Abstract class for data array
class mglDataA
{
public:
	virtual ~mglDataA()	{};
	virtual mreal v(long i,long j=0,long k=0) const = 0;
	virtual mreal vthr(long i) const = 0;
	virtual long GetNx() const = 0;
	virtual long GetNy() const = 0;
	virtual long GetNz() const = 0;
	inline long GetNN() const {	return GetNx()*GetNy()*GetNz();	}
	virtual mreal Maximal() const = 0;
	virtual mreal Minimal() const = 0;
	virtual mreal dvx(long i,long j=0,long k=0) const = 0;
//	{	return i>0 ? (i<GetNx()-1 ? (v(i+1,j,k)-v(i-1,j,k))/2 : v(i,j,k)-v(i-1,j,k)) : v(1,j,k)-v(0,j,k);	}
	virtual mreal dvy(long i,long j=0,long k=0) const = 0;
//	{	return j>0 ? (j<GetNy()-1 ? (v(i,j+1,k)-v(i,j-1,k))/2 : v(i,j,k)-v(i,j-1,k)) : v(i,1,k)-v(i,0,k);	}
	virtual mreal dvz(long i,long j=0,long k=0) const = 0;
//	{	return k>0 ? (k<GetNz()-1 ? (v(i,j,k+1)-v(i,j,k-1))/2 : v(i,j,k)-v(i,j,k-1)) : v(i,j,1)-v(i,j,0);	}
};
#endif
typedef const mglDataA* HCDT;
//-----------------------------------------------------------------------------
inline mreal mgl_d(mreal v,mreal v1,mreal v2) { return v2!=v1?(v-v1)/(v2-v1):NAN; }
//-----------------------------------------------------------------------------
mglPoint GetX(HCDT x, int i, int j, int k=0);
mglPoint GetY(HCDT y, int i, int j, int k=0);
mglPoint GetZ(HCDT z, int i, int j, int k=0);
//-----------------------------------------------------------------------------
/// Structure for simplest primitives
struct mglPrim	// NOTE: use float for reducing memory size
{
	// NOTE: n4 is used as mark; n3 -- as pen style for type=0,1,4
	// NOTE: n3 is used as position of txt,font in Ptxt for type=6
	long n1,n2,n3,n4;	///< coordinates of corners
	int type;	///< primitive type (0-point, 1-line, 2-trig, 3-quad, 4-glyph, 6-text)
	int id;		///< object id
	float z;		///< z-position
	float s;		///< size (if applicable) or fscl
	float w;		///< width (if applicable) or ftet
	float p;

	mglPrim(int t=0)	{	n1=n2=n3=n4=id=0;	z=s=w=p=0;	type = t;	}
};
bool operator<(const mglPrim &a,const mglPrim &b);
bool operator>(const mglPrim &a,const mglPrim &b);
//-----------------------------------------------------------------------------
/// Structure for group of primitives
struct mglGroup
{
	std::vector<long> p;///< list of primitives (not filled!!!)
	int Id;				///< Current list of primitives
	std::string Lbl;	///< Group label
	mglGroup(const char *lbl="", int id=0)	{	Lbl=lbl;	Id=id;	}
};
//-----------------------------------------------------------------------------
/// Structure for text label
struct mglText
{
	std::wstring text;
	std::string stl;
	mreal val;
	mglText(const wchar_t *txt=0, const char *fnt=0, mreal v=0)	{	text=txt;	stl=fnt;	val=v;	}
	mglText(const std::wstring &txt, mreal v=0)	{	text=txt;	val=v;	}
};
//-----------------------------------------------------------------------------
/// Structure for internal point represenatation
struct mglPnt	// NOTE: use float for reducing memory size
{
	float xx,yy,zz;	// original coordinates
	float x,y,z;		// coordinates
	float c,t,ta;	// index in color scheme
	float u,v,w;		// normales
	float r,g,b,a;	// RGBA color
	mglPnt()	{	xx=yy=zz=x=y=z=c=t=ta=u=v=w=r=g=b=a=0;	}
};
inline mglPnt operator+(const mglPnt &a, const mglPnt &b)
{	mglPnt c=a;
	c.x+=b.x;	c.y+=b.y;	c.z+=b.z;	c.u+=b.u;	c.v+=b.v;	c.w+=b.w;
	c.r+=b.r;	c.g+=b.g;	c.b+=b.b;	c.a+=b.a;	return c;	}
inline mglPnt operator-(const mglPnt &a, const mglPnt &b)
{	mglPnt c=a;
	c.x-=b.x;	c.y-=b.y;	c.z-=b.z;	c.u-=b.u;	c.v-=b.v;	c.w-=b.w;
	c.r-=b.r;	c.g-=b.g;	c.b-=b.b;	c.a-=b.a;	return c;	}
inline mglPnt operator*(const mglPnt &a, float b)
{	mglPnt c=a;
	c.x*=b;	c.y*=b;	c.z*=b;	c.u*=b;	c.v*=b;	c.w*=b;
	c.r*=b;	c.g*=b;	c.b*=b;	c.a*=b;	return c;	}
inline mglPnt operator*(float b, const mglPnt &a)
{	mglPnt c=a;
	c.x*=b;	c.y*=b;	c.z*=b;	c.u*=b;	c.v*=b;	c.w*=b;
	c.r*=b;	c.g*=b;	c.b*=b;	c.a*=b;	return c;	}
//-----------------------------------------------------------------------------
struct mglTexture
{
	mglColor col[512];	///< Colors itself
	long n;				///< Number of initial colors along u

	char Sch[260];		///< Color scheme used
	int Smooth;			///< Type of texture (smoothing and so on)
	mreal Alpha;			///< Transparency
	
	mglTexture()	{	n=Smooth=0;	Alpha=1;	}
	mglTexture(const char *cols, int smooth=0,mreal alpha=1)
	{	n=0;	Set(cols,smooth,alpha);	}
	void Clear()	{	n=0;	}
	void Set(const char *cols, int smooth=0,mreal alpha=1);
	void GetC(mreal u,mreal v,mglPnt &p) const;
	inline bool IsSame(const mglTexture &t) const
	{	return n==t.n && !memcmp(col,t.col,512*sizeof(mglColor));	}
	void GetRGBA(unsigned char *f) const;	// Write as BGRA for fastest export to TGA
};
//-----------------------------------------------------------------------------
const mglColor NC(-1,-1,-1);
const mglColor BC( 0, 0, 0);
const mglColor WC( 1, 1, 1);
const mglColor RC( 1, 0, 0);
long mgl_have_color(const char *stl);
//-----------------------------------------------------------------------------
/// Structure for color ID
struct mglColorID
{
	char id;
	mglColor col;
};
extern mglColorID mglColorIds[31];
//-----------------------------------------------------------------------------
/// Base class for canvas which handle all basic drawing
class mglBase
{
public:
	mglBase();
	virtual ~mglBase();

	bool Stop;			///< Flag that execution should be terminated.
	mglPoint Min;		///< Lower edge of bounding box for graphics.
	mglPoint Max;		///< Upper edge of bounding box for graphics.
	mreal ZMin;			///< Adjusted minimal z-value 1D plots
	std::string Mess;	///< Buffer for receiving messages
	int ObjId;			///< object id for mglPrim
	int HighId;			///< object id to be highlited
	std::vector<mglGroup> Grp;	///< List of groups with names -- need for export
	std::string PlotId;	///< Id of plot for saving filename (in GLUT window for example)

	mreal CDef;			///< Default (current) color in texture
	mreal AlphaDef;		///< Default value of alpha channel (transparency)
	mreal BarWidth;		///< Relative width of rectangles in Bars().
	int MeshNum;		///< Set approximate number of lines in Mesh and Grid. By default (=0) it draw all lines.
	char Arrow1, Arrow2;///< Style of arrows at end and at start of curve
	long InUse;			///< Smart pointer (number of users)
	long Flag;			///< Flags for controlling drawing

	inline bool get(long fl) const	{	return Flag&fl;	}
	inline void set(long fl)	{	Flag |= fl;	}
	inline void clr(long fl)	{	Flag &=~fl;	}
	inline void set(bool v,long fl)	{	Flag = v ? Flag|fl : Flag&(~fl);	}

	/// Set values of mglGraph::Min and mglGraph::Max
	inline void SetRanges(mreal x1, mreal x2, mreal y1, mreal y2, mreal z1=0, mreal z2=0, mreal c1=0, mreal c2=0)
	{	SetRanges(mglPoint(x1,y1,z1,c1),mglPoint(x2,y2,z2,c2));	}
	void SetRanges(mglPoint v1, mglPoint v2);
	/// Set values of mglGraph::Cmin and mglGraph::Cmax as minimal and maximal values of data a
	void CRange(HCDT a, bool add = false, mreal fact=0);
	inline void CRange(mreal v1,mreal v2)	{	if(v1!=v2)	{Min.c=v1;	Max.c=v2;	RecalcCRange();}	}
	/// Set values of mglGraph::Min.x and mglGraph::Max.x as minimal and maximal values of data a
	void XRange(HCDT a, bool add = false, mreal fact=0);
	inline void XRange(mreal v1,mreal v2)	{	if(v1!=v2)	{Min.x=v1;	Max.x=v2;	RecalcBorder();}	}
	/// Set values of mglGraph::Min.x and mglGraph::Max.x as minimal and maximal values of data a
	void YRange(HCDT a, bool add = false, mreal fact=0);
	inline void YRange(mreal v1,mreal v2)	{	if(v1!=v2)	{Min.y=v1;	Max.y=v2;	RecalcBorder();}	}
	/// Set values of mglGraph::Min.x and mglGraph::Max.x as minimal and maximal values of data a
	void ZRange(HCDT a, bool add = false, mreal fact=0);
	inline void ZRange(mreal v1,mreal v2)	{	if(v1!=v2)	{Min.z=v1;	Max.z=v2;	RecalcBorder();}	}
	/// Set ranges for automatic variables
	void SetAutoRanges(mreal x1, mreal x2, mreal y1=0, mreal y2=0, mreal z1=0, mreal z2=0, mreal c1=0, mreal c2=0);
	/// Set axis origin
	inline void SetOrigin(mreal x0, mreal y0, mreal z0=NAN, mreal c0=NAN)
	{	Org=mglPoint(x0,y0,z0,c0);	}
	/// Save ranges into internal variable and put parsed
	mreal SaveState(const char *opt);
	/// Load ranges from internal variable
	void LoadState();
	/// Increase ZMin
	mreal AdjustZMin()	{	ZMin /= MGL_EPSILON;	return Max.z - ZMin*(Max.z-Min.z);	}

	/// Safetly set the transformation formulas for coordinate.
	void SetFunc(const char *EqX, const char *EqY, const char *EqZ=0, const char *EqA=0);
	/// Set one of predefined transformation rule
	void SetCoor(int how);
	/// Safetly set the cutting off condition (formula).
	void CutOff(const char *EqCut);
	/// Set to draw Ternary axis (triangle like axis, grid and so on)
	void Ternary(int tern);

	/// Set cutting for points outside of bounding box
	inline void SetCut(bool val)	{	set(val, MGL_ENABLE_CUT);	}
	/// Set additional cutting box
	inline void SetCutBox(mreal x1, mreal y1, mreal z1, mreal x2, mreal y2, mreal z2)
	{	CutMin=mglPoint(x1,y1,z1);	CutMax=mglPoint(x2,y2,z2);	}
	inline void SetCutBox(mglPoint v1, mglPoint v2)	{	CutMin=v1;	CutMax=v2;	}

	/// Set the using of light on/off.
	virtual bool Light(bool enable)
	{	bool t=get(MGL_ENABLE_LIGHT);	set(enable,MGL_ENABLE_LIGHT);	return t;	}
	/// Set ambient light brightness
	virtual void SetAmbient(mreal bright=0.5);
	/// Use diffusive light (only for local light sources)
	inline void SetDifLight(bool dif)	{	set(dif,MGL_DIFFUSIVE);	}
	/// Set the transparency on/off.
	virtual bool Alpha(bool enable)
	{	bool t=get(MGL_ENABLE_ALPHA);	set(enable,MGL_ENABLE_ALPHA);	return t;	}
	/// Set default value of alpha-channel
	inline void SetAlphaDef(mreal val)	{	AlphaDef=val;	};
	/// Set default palette
	inline void SetPalette(const char *colors)
	{	Txt[0].Set(mgl_have_color(colors)?colors:MGL_DEF_PAL,-1);	}
	inline long GetNumPal(long id) const	{	return Txt[labs(id)/256].n;	}
	/// Set default color scheme
	inline void SetDefScheme(const char *colors)
	{	Txt[1].Set(mgl_have_color(colors)?colors:"BbcyrR");	}

	/// Set number of mesh lines
	inline void SetMeshNum(int val)	{	MeshNum=val;	};
	/// Set relative width of rectangles in Bars, Barh, BoxPlot
	inline void SetBarWidth(mreal val)	{	BarWidth=val;	};
	/// Set size of marks
	inline void SetMarkSize(mreal val)	{	MarkSize=0.02*val;	}
	/// Set size of arrows
	inline void SetArrowSize(mreal val)	{	ArrowSize=0.03*val;	}

	/// Set warning code ant fill Message
	void SetWarn(int code, const char *who);
	int inline GetWarn() const	{	return WarnCode;	}

	virtual void StartAutoGroup (const char *)=0;
	void StartGroup(const char *name, int id);
	virtual void EndGroup()=0;	//	{	LoadState();	}
	/// Highlight group
	inline void Highlight(int id)	{	HighId=id;	}

	/// Set FontSize by size in pt and picture DPI (default is 16 pt for dpi=72)
	virtual void SetFontSizePT(mreal pt, int dpi=72){	FontSize = pt*27.f/dpi;	}
	/// Set FontSize by size in centimeters and picture DPI (default is 0.56 cm = 16 pt)
	inline void SetFontSizeCM(mreal cm, int dpi=72)	{	SetFontSizePT(cm*28.45f,dpi);	};
	/// Set FontSize by size in inch and picture DPI (default is 0.22 in = 16 pt)
	inline void SetFontSizeIN(mreal in, int dpi=72)	{	SetFontSizePT(in*72.27f,dpi);	};
	/// Set font typeface. Note that each mglFont instance can be used with ONLY ONE mglGraph instance at a moment of time!
	void SetFont(mglFont *f);
	/// Get current typeface. Note that this variable can be deleted at next SetFont() call!
	inline mglFont *GetFont()	{	return fnt;	}
	/// Restore font
	inline void RestoreFont()	{	fnt->Restore();	}
	/// Load font from file
	inline void LoadFont (const char *name, const char *path=NULL)
	{	fnt->Load(name,path);	};
	/// Copy font from another mglGraph instance
	inline void CopyFont(mglBase *gr)	{	fnt->Copy(gr->GetFont());	}
	/// Set default font size
	inline void SetFontSize(mreal val)	{	FontSize=val>0 ? val:FontSize*val;	}
	inline mreal GetFontSize() const	{	return FontSize;	};
	inline mreal TextWidth(const wchar_t *text, const char *font, mreal size) const
	{	return (size<0?-size*FontSize:size)*font_factor*fnt->Width(text,(font&&*font)?font:FontDef)/8;	}
	inline mreal TextHeight(const char *font, mreal size) const
	{	return (size<0?-size*FontSize:size)*font_factor*fnt->Height(font?font:FontDef)/8; }
	inline mreal FontFactor() const		{	return font_factor;	}
	virtual mreal GetRatio() const;
	/// Set to use or not text rotation
	inline void SetRotatedText(bool val)	{	set(val,MGL_ENABLE_RTEXT);	}
	/// Set default font style and color
	inline void SetFontDef(const char *font)	{	strncpy(FontDef, font, 31);	}
	/// Set to use or not text rotation
	inline void SetTickRotate(bool val)	{	set(val,MGL_TICKS_ROTATE);	}
	/// Set to use or not text rotation
	inline void SetTickSkip(bool val)	{	set(val,MGL_TICKS_SKIP);	}

	/// Add string to legend
	void AddLegend(const char *text,const char *style);
	void AddLegend(const wchar_t *text,const char *style);
	/// Clear saved legend string
	inline void ClearLegend()	{	Leg.clear();	}

	/// Set plot quality
	virtual void SetQuality(int qual=MGL_DRAW_NORM)	{	Quality=qual;	}
	inline int GetQuality() const	{	return Quality;	}

	// ~~~~~~~~~~~~~~~~~~~~~~ Developer functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	/// Add point to the pntN and return its position
	long AddPnt(mglPoint p, mreal c=-1, mglPoint n=mglPoint(NAN), mreal a=-1, int scl=1);
	long CopyNtoC(long k, mreal c);
	long CopyProj(long from, mglPoint p, mglPoint n);
	virtual void Reserve(long n);		///< Allocate n-cells for pntC and return current position
	/// Set to reduce accuracy of points (to reduc size of output files)
	inline void SetReduceAcc(bool val)	{	set(val, MGL_REDUCEACC);	}

//	inline long GetPos()	{	return Pnt.size()-1;	}
	inline mglPoint GetPntP(long i) const
	{	const mglPnt &p=Pnt[i];	return mglPoint(p.x,p.y,p.z);	}
	inline float GetClrC(long i) const	{	return Pnt[i].c;	}
	inline const mglPnt &GetPnt(long i) const		{	return Pnt[i];		}
	inline long GetPntNum() const		{	return Pnt.size();	}
	inline mglPrim &GetPrm(long i)		{	return Prm[i];		}
	inline long GetPrmNum() const		{	return Prm.size();	}
	inline const mglText &GetPtx(long i) const		{	return Ptx[i];		}
	inline long GetPtxNum() const		{	return Ptx.size();	}
	inline const mglTexture &GetTxt(long i) const	{	return Txt[i];		}
	inline long GetTxtNum() const		{	return Txt.size();	}
	/// Scale coordinates and cut off some points
	virtual bool ScalePoint(mglPoint &p, mglPoint &n, bool use_nan=true) const;

	virtual mreal GetOrgX(char dir) const=0;	///< Get Org.x (parse NAN value)
	virtual mreal GetOrgY(char dir) const=0;	///< Get Org.y (parse NAN value)
	virtual mreal GetOrgZ(char dir) const=0;	///< Get Org.z (parse NAN value)

	/// Get color depending on single variable z, which should be scaled if scale=true
	inline mreal GetC(long s,mreal z,bool scale = true) const
	{	return s+(scale?GetA(z):(z>0?z/MGL_EPSILON:0));	}
	/// Get alpha value depending on single variable \a a
	mreal GetA(mreal a) const;
	/// Set pen/palette
	char SetPenPal(const char *stl, long *id=0);
	/// Add texture (like color scheme) and return the position of first color
	long AddTexture(const char *cols, int smooth=0);
//	inline mreal AddTexture(char col)	{	return AddTexture(mglColor(col));	};
	mreal AddTexture(mglColor col);
	inline void DefColor(mglColor col)	{	CDef = AddTexture(col);	}
	/// Set next color from palette
	mreal NextColor(long &id);

	virtual void mark_plot(long p, char type, mreal size=1)=0;
	virtual void arrow_plot(long p1, long p2, char st)=0;
	virtual void line_plot(long p1, long p2)=0;
	virtual void trig_plot(long p1, long p2, long p3)=0;
	virtual void quad_plot(long p1, long p2, long p3, long p4)=0;
	virtual void Glyph(mreal x, mreal y, mreal f, int style, long icode, mreal col)=0;
	virtual mreal text_plot(long p,const wchar_t *text,const char *fnt,mreal size=-1,mreal sh=0,mreal  col=-('k'),bool rot=true)=0;
	void vect_plot(long p1, long p2, mreal s=1);
	inline mreal mark_size()	{	return MarkSize*font_factor;	}
//	inline char last_color()	{	return last_style[1];	}
	inline const char *last_line()	{	return last_style;	}

protected:
	mglPoint FMin;		///< Actual lower edge after transformation formulas.
	mglPoint FMax;		///< Actual upper edge after transformation formulas.
	mglPoint Org;		///< Center of axis cross section.
	int WarnCode;		///< Warning code
	std::vector<mglPnt> Pnt;	///< Internal points
	std::vector<mglPrim> Prm;	///< Primitives (lines, triangles and so on) -- need for export
	std::vector<mglPrim> Sub;	///< InPlot regions {n1=x1,n2=x2,n3=y1,n4=y2,id}
	std::vector<mglText> Ptx;	///< Text labels for mglPrim
	std::vector<mglText> Leg;	///< Text labels for legend
	std::vector<mglTexture> Txt;///< Pointer to textures
#if MGL_HAVE_PTHREAD
	pthread_mutex_t mutexPnt, mutexTxt, mutexLeg;
#endif

	int TernAxis;		///< Flag that Ternary axis is used
	unsigned PDef;		///< Pen bit mask
	mreal pPos;			///< Current position in pen mask
	mreal PenWidth;		///< Pen width for further line plotting (must be >0 !!!)
//	long numT;			///< Number of textures
	mreal AmbBr;		///< Default ambient light brightness

	mglFont *fnt;		///< Class for printing vector text
	mreal FontSize;		///< The size of font for tick and axis labels
	char FontDef[32];	///< Font specification (see mglGraph::Puts). Default is Roman with align at center.
	int Quality;		///< Quality of plot (0x0-pure, 0x1-fast; 0x2-fine; 0x4 - low memory)

	mglFormula *fx;		///< Transformation formula for x direction.
	mglFormula *fy;		///< Transformation formula for y direction.
	mglFormula *fz;		///< Transformation formula for z direction.
	mglFormula *fa;		///< Transformation formula for coloring.
	mglFormula *fc;		///< Cutting off condition (formula).

	long CurrPal;		///< Current palette index
	mreal MarkSize;		///< The size of marks for 1D plots.
	mreal ArrowSize;	///< The size of arrows.
	char last_style[64];///< Last pen style
	mreal font_factor;	///< Font scaling factor

	virtual void LightScale()=0;			///< Scale positions of light sources

private:
	mglPoint MinS;		///< Saved lower edge of bounding box for graphics.
	mglPoint MaxS;		///< Saved upper edge of bounding box for graphics.
	mreal MSS, ASS, FSS, ADS, MNS, LSS;	///< Saved state
	long CSS;			///< Saved flags
	bool saved;			///< State is saved
	std::string leg_str;///< text to be save in legend

	mglPoint CutMin;	///< Lower edge of bounding box for cut off.
	mglPoint CutMax;	///< Upper edge of bounding box for cut off.

	void RecalcCRange();	///< Recalculate internal parameter for correct coloring.
	void RecalcBorder();	///< Recalculate internal parameter for correct transformation rules.
	void SetFBord(mreal x,mreal y,mreal z);	///< Set internal boundng box depending on transformation formula
	void ClearEq();			///< Clear the used variables for axis transformation
};
//-----------------------------------------------------------------------------
bool mgl_check_dim1(HMGL gr, HCDT x, HCDT y, HCDT z, HCDT r, const char *name, bool less=false);
bool mgl_check_dim2(HMGL gr, HCDT x, HCDT y, HCDT z, HCDT a, const char *name, bool less=false);
bool mgl_check_dim3(HMGL gr, bool both, HCDT x, HCDT y, HCDT z, HCDT a, HCDT b, const char *name);
bool mgl_check_vec3(HMGL gr, HCDT x, HCDT y, HCDT z, HCDT ax, HCDT ay, HCDT az, const char *name);
bool mgl_check_trig(HMGL gr, HCDT nums, HCDT x, HCDT y, HCDT z, HCDT a, const char *name, int d=3);
bool mgl_isboth(HCDT x, HCDT y, HCDT z, HCDT a);
//-----------------------------------------------------------------------------
#define _Da_(d)	(*((const mglDataA *)(d)))
#define _DA_(a)	((const mglDataA *)*(a))
#define _GR_	((mglBase *)(*gr))
//-----------------------------------------------------------------------------
//#define _D_(d)	*((mglData *)*(d))
#define _DM_(a)	((mglData *)*(a))
#define _DT_	((mglData *)*d)
//-----------------------------------------------------------------------------
#else
typedef void *HMGL;
typedef void *HMDT;
typedef void *HMEX;
typedef void *HMPR;
typedef const void *HCDT;
#endif
/*****************************************************************************/
#endif
