
/**
* File: CDM
* About: Description
* Console Draw Motor
* Library for creating 2D Games for the Windows CMD.
* For exclusive use with Windows. Not compatible for versions lower than Windows vista.
* This library only provides the C functions for drawing on the console, 
* and the structures for its usage.
*
* About: License
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not claim
* that you wrote the original software. If you use this software in a product,
* an acknowledgment in the product documentation would be appreciated but is
* not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*
* José María Pérez Parrillat 2017
*/

#pragma once
#include <Windows.h>

#pragma region Defines

//This are color bytes. Use them for sprites along with the function
//SetPixel.
#define CLEAR				0

//This values are for using a custom color scheme.
#define LETCOLOR1			0x0000			//0000
#define LETCOLOR2			0x0001			//0001
#define LETCOLOR3			0x0002			//0010
#define LETCOLOR4			0x0003			//0011	
#define LETCOLOR5			0x0004			//0100
#define LETCOLOR6			0x0005			//0101
#define LETCOLOR7			0x0006			//0110
#define LETCOLOR8			0x0007			//0111
#define LETCOLOR9			0x0008			//1000
#define LETCOLOR10			0x0009			//1001
#define LETCOLOR11			0x000A			//1010
#define LETCOLOR12			0x000B			//1011
#define LETCOLOR13			0x000C			//1100
#define LETCOLOR14			0x000D			//1101
#define LETCOLOR15			0x000E			//1110
#define LETCOLOR16			0x000F			//1111

#define BACKCOLOR1			0x0000
#define BACKCOLOR2			0x0010
#define BACKCOLOR3			0x0020
#define BACKCOLOR4			0x0030
#define BACKCOLOR5			0x0040
#define BACKCOLOR6			0x0050
#define BACKCOLOR7			0x0060
#define BACKCOLOR8			0x0070
#define BACKCOLOR9			0x0080
#define BACKCOLOR10			0x0090
#define BACKCOLOR11			0x00A0
#define BACKCOLOR12			0x00B0
#define BACKCOLOR13			0x00C0
#define BACKCOLOR14			0x00D0
#define BACKCOLOR15			0x00E0
#define BACKCOLOR16			0x00F0

//Use this ones if you aren't using a new scheme.
#define LBASEBLACK			LETCOLOR1
#define LBASEBLUE			LETCOLOR2
#define LBASEGREEN			LETCOLOR3
#define LBASECYAN			LETCOLOR4
#define LBASERED			LETCOLOR5
#define LBASEMAGENTA		LETCOLOR6
#define LBASEBROWN			LETCOLOR7
#define LBASEGREY			LETCOLOR8
#define LBASEDARKGREY		LETCOLOR9
#define LBASELIGHTBLUE		LETCOLOR10
#define LBASELIGHTGREEN		LETCOLOR11
#define LBASELIGHTCYAN		LETCOLOR12
#define LBASELIGHTRED		LETCOLOR13
#define LBASELIGHTMAGENTA	LETCOLOR14
#define	LBASEYELLOW			LETCOLOR15
#define LBASEWHITE			LETCOLOR16

#define BBASEBLACK			BACKCOLOR1
#define BBASEBLUE			BACKCOLOR2
#define BBASEGREEN			BACKCOLOR3
#define BBASECYAN			BACKCOLOR4
#define BBASERED			BACKCOLOR5
#define BBASEMAGENTA		BACKCOLOR6
#define BBASEBROWN			BACKCOLOR7
#define BBASEGREY			BACKCOLOR8
#define BBASEDARKGREY		BACKCOLOR9
#define BBASELIGHTBLUE		BACKCOLOR10
#define BBASELIGHTGREEN		BACKCOLOR11
#define BBASELIGHTCYAN		BACKCOLOR12
#define BBASELIGHTRED		BACKCOLOR13
#define BBASELIGHTMAGENTA	BACKCOLOR14
#define	BBASEYELLOW			BACKCOLOR15
#define BBASEWHITE			BACKCOLOR16

//This is used for choosing an alpha.
#define ALPHACOLOR			100

#pragma endregion !Defines

typedef SMALL_RECT CDMRect;

typedef struct CDMTiles
{
	CHAR_INFO		*printBufferCont;
}CDMTiles;

typedef struct CDMContext
{
	HANDLE WINAPI					mainBuffer,
									backBuffer;
	BOOL							mainBufferActive;
	CONSOLE_SCREEN_BUFFER_INFOEX	inf;
	CDMTiles						contents;
	CDMRect							rect;
}CDMContext;

typedef struct CDMPalette
{
	char	p1,
			p2,
			p3,
			p4;
}CDMPalette;

typedef struct CDMSurface 
{
	CDMPalette			characters,
						frontColors,
						backgroundColors;
	CDMRect				rect;
	unsigned char		*data;
	CDMTiles			bufferContents;
}CDMSurface;

typedef struct CDMText
{
	short		frontColor,
				backColor;
	char		*data;
	CDMRect		rect;
	CDMTiles	bufferContents;
}CDMText;

/*
*	This structure serves the purpose of a color palette. 
*	You can select which palette is active and displaying at any time 
*	using 
*	Default values for colors.
*	{ 0x00362b00,		//Black 
*	0x00423607,		//Gray
*	0x00756e58,		//Green
*	0x00837b65,		//Yellow
*	0x00969483,		//Blue
*	0x00a1a193,		//Aqua
*	0x00d5e8ee,		//White
*	0x00e3f6fd,		//BrightWhite
*	0x000089b5,		//BrightYellow
*	0x00164bcb,		//Red
*	0x002f32dc,		//LightRed
*	0x008236d3,		//LightPurple
*	0x00c4716c,		//Purple
*	0x00d28b26,		//LightBlue
*	0x0098a12a,		//LightAqua
*	0x00009985 };	//LightGreen
*/
typedef struct CDMColorScheme 
{
	COLORREF colors[16];
}CDMColorScheme;

#ifdef __cplusplus
extern "C" {
#endif
 CDMContext*	CDMCreateContext(const int width, const int height);
 CDMSurface*	CMDCreateSurface(const SHORT posX,
							const SHORT posY,
							const SHORT sizeX,
							const SHORT sizeY);
 CDMText*		CDMTextWrapper(char * text,
							const short color,
							const short background);
 void			CDMSetForegroundColor(CDMSurface** surface,
							const char c1,
							const char c2,
							const char c3,
							const char c4);
 void			CDMSetBackgroundColor(CDMSurface** surface,
							const char c1,
							const char c2,
							const char c3,
							const char c4);
 int			CDMSwapBuffer(CDMContext* const ctx);
 void			CDMFreeSurface(CDMSurface** surface);
 void			CDMFreeText(CDMText** txt);
 void			CDMFreeContext(CDMContext** ctx);
 void			CDMPrepareSurface(CDMSurface** surface);
 void			CDMPrepareText(CDMText** txt);
 void			CDMDrawSurface(CDMContext ** ctx, CDMSurface * surface);
 void			CDMAddSurfaceToContext(CDMContext** ctx, CDMSurface* surface);
 void			CDMDrawText(CDMContext ** ctx, CDMText * txt);
 void			CDMAddTextToContext(CDMContext** ctx, CDMText* txt);
 void			CDMSetColorRGB(CDMColorScheme* data, int position, int r, int g, int b);
 void			CDMSetColorBin(CDMColorScheme* data, int position, const DWORD color);
 void			CDMDraw(CDMContext* ctx);
 int			CDMGetR(CDMColorScheme* data, const int position);
 int			CDMGetG(CDMColorScheme* data, const int position);
 int			CDMGetB(CDMColorScheme* data, const int position);
 void			SetActiveScheme(CDMColorScheme data, CDMContext** ctx);
#ifdef __cplusplus
}
#endif
