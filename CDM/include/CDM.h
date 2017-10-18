
/**
* @file CDM.h
* @about Description
* Console Draw Motor
* Library for creating 2D Games for the Windows CMD.
* For exclusive use with Windows. Not compatible for versions lower than Windows vista.
* This library only provides the C functions for drawing on the console, 
* and the structures for its usage.
*
* @about License
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
* @author José María Pérez Parrillat 2017
*/

#pragma once
#include <Windows.h>

#pragma region Defines

/**********************************************************************************************//**
 * \def	_IN_
 *
 * \brief	Describes a parameter that will only be used for data input and is required.
 **************************************************************************************************/

#define _IN_

/**********************************************************************************************//**
 * \def	_OUT_
 *
 * \brief	Describes a parameter that will only be used for data output and is required.
 **************************************************************************************************/
 
#define _OUT_

/**********************************************************************************************//**
 * \def	_INOUT_
 *
 * \brief	Describes a parameter that will be used for data input and output and is required.
 **************************************************************************************************/

#define _INOUT_

/**********************************************************************************************//**
 * \def	_INOPT_
 *
 * \brief	Describes a parameter that will only be used for data input and is not required.
 **************************************************************************************************/

#define _INOPT_

/**********************************************************************************************//**
 * \def	_OUTOPT_
 *
 * \brief	Describes a parameter that will only be used for data output and is not required.
 **************************************************************************************************/

#define _OUTOPT_

/**********************************************************************************************//**
 * \def	_INOUTOPT_
 *
 * \brief	Describes a parameter that will be used for data input and output and is not required.
 **************************************************************************************************/

#define _INOUTOPT_

/**********************************************************************************************//**
 * \def	CLEAR
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear 
 * 			defines a completely alpha color.
 **************************************************************************************************/

#define CLEAR				0

/**********************************************************************************************//**
 * \def	LETCOLOR1
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear 
 * 			defines the first color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR1			0x0000			//0000

/**********************************************************************************************//**
 * \def	LETCOLOR2
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the second color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR2			0x0001			//0001

/**********************************************************************************************//**
 * \def	LETCOLOR3
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the third color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR3			0x0002			//0010

/**********************************************************************************************//**
 * \def	LETCOLOR4
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fourth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR4			0x0003			//0011	

/**********************************************************************************************//**
 * \def	LETCOLOR5
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fifth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR5			0x0004			//0100

/**********************************************************************************************//**
 * \def	LETCOLOR6
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the sixth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR6			0x0005			//0101

/**********************************************************************************************//**
 * \def	LETCOLOR7
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the seventh color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR7			0x0006			//0110

/**********************************************************************************************//**
 * \def	LETCOLOR8
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the eighth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR8			0x0007			//0111

/**********************************************************************************************//**
 * \def	LETCOLOR9
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the ninth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR9			0x0008			//1000

/**********************************************************************************************//**
 * \def	LETCOLOR10
 *
 * \brief	 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear 
 * 			defines the tenth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR10			0x0009			//1001

/**********************************************************************************************//**
 * \def	LETCOLOR11
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the eleventh color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR11			0x000A			//1010

/**********************************************************************************************//**
 * \def	LETCOLOR12
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the twelfth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR12			0x000B			//1011

/**********************************************************************************************//**
 * \def	LETCOLOR13
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the thirtheenth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR13			0x000C			//1100

/**********************************************************************************************//**
 * \def	LETCOLOR14
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fourteenth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR14			0x000D			//1101

/**********************************************************************************************//**
 * \def	LETCOLOR15
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fifteenth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR15			0x000E			//1110

/**********************************************************************************************//**
 * \def	LETCOLOR16
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the sixteenth color of the scheme applied to the foreground.
 **************************************************************************************************/

#define LETCOLOR16			0x000F			//1111

/**********************************************************************************************//**
 * \def	BACKCOLOR1
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the first color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR1			0x0000

/**********************************************************************************************//**
 * \def	BACKCOLOR2
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the second color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR2			0x0010

/**********************************************************************************************//**
 * \def	BACKCOLOR3
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the third color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR3			0x0020

/**********************************************************************************************//**
 * \def	BACKCOLOR4
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fourth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR4			0x0030

/**********************************************************************************************//**
 * \def	BACKCOLOR5
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fifth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR5			0x0040

/**********************************************************************************************//**
 * \def	BACKCOLOR6
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the sixth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR6			0x0050

/**********************************************************************************************//**
 * \def	BACKCOLOR7
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the seventh color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR7			0x0060

/**********************************************************************************************//**
 * \def	BACKCOLOR8
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the eighth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR8			0x0070

/**********************************************************************************************//**
 * \def	BACKCOLOR9
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the ninth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR9			0x0080

/**********************************************************************************************//**
 * \def	BACKCOLOR10
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the tenth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR10			0x0090

/**********************************************************************************************//**
 * \def	BACKCOLOR11
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the eleventh color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR11			0x00A0

/**********************************************************************************************//**
 * \def	BACKCOLOR12
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the twelfth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR12			0x00B0

/**********************************************************************************************//**
 * \def	BACKCOLOR13
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the thirteenth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR13			0x00C0

/**********************************************************************************************//**
 * \def	BACKCOLOR14
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fourteenth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR14			0x00D0

/**********************************************************************************************//**
 * \def	BACKCOLOR15
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the fifteenth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR15			0x00E0

/**********************************************************************************************//**
 * \def	BACKCOLOR16
 *
 * \brief	This are color bytes. Use them for sprites along with the function SetPixel. Clear
 * 			defines the sixteenth color of the scheme applied to the background.
 **************************************************************************************************/

#define BACKCOLOR16			0x00F0

/**********************************************************************************************//**
 * \def	LBASEBLACK
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEBLACK			LETCOLOR1

/**********************************************************************************************//**
 * \def	LBASEBLUE
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEBLUE			LETCOLOR2

/**********************************************************************************************//**
 * \def	LBASEGREEN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEGREEN			LETCOLOR3

/**********************************************************************************************//**
 * \def	LBASECYAN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASECYAN			LETCOLOR4

/**********************************************************************************************//**
 * \def	LBASERED
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASERED			LETCOLOR5

/**********************************************************************************************//**
 * \def	LBASEMAGENTA
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEMAGENTA		LETCOLOR6

/**********************************************************************************************//**
 * \def	LBASEBROWN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEBROWN			LETCOLOR7

/**********************************************************************************************//**
 * \def	LBASEGREY
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEGREY			LETCOLOR8

/**********************************************************************************************//**
 * \def	LBASEDARKGREY
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEDARKGREY		LETCOLOR9

/**********************************************************************************************//**
 * \def	LBASELIGHTBLUE
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASELIGHTBLUE		LETCOLOR10

/**********************************************************************************************//**
 * \def	LBASELIGHTGREEN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASELIGHTGREEN		LETCOLOR11

/**********************************************************************************************//**
 * \def	LBASELIGHTCYAN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASELIGHTCYAN		LETCOLOR12

/**********************************************************************************************//**
 * \def	LBASELIGHTRED
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASELIGHTRED		LETCOLOR13

/**********************************************************************************************//**
 * \def	LBASELIGHTMAGENTA
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASELIGHTMAGENTA	LETCOLOR14

/**********************************************************************************************//**
 * \def	LBASEYELLOW
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define	LBASEYELLOW			LETCOLOR15

/**********************************************************************************************//**
 * \def	LBASEWHITE
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define LBASEWHITE			LETCOLOR16

/**********************************************************************************************//**
 * \def	BBASEBLACK
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEBLACK			BACKCOLOR1

/**********************************************************************************************//**
 * \def	BBASEBLUE
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEBLUE			BACKCOLOR2

/**********************************************************************************************//**
 * \def	BBASEGREEN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEGREEN			BACKCOLOR3

/**********************************************************************************************//**
 * \def	BBASECYAN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASECYAN			BACKCOLOR4

/**********************************************************************************************//**
 * \def	BBASERED
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASERED			BACKCOLOR5

/**********************************************************************************************//**
 * \def	BBASEMAGENTA
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEMAGENTA		BACKCOLOR6

/**********************************************************************************************//**
 * \def	BBASEBROWN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEBROWN			BACKCOLOR7

/**********************************************************************************************//**
 * \def	BBASEGREY
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEGREY			BACKCOLOR8

/**********************************************************************************************//**
 * \def	BBASEDARKGREY
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEDARKGREY		BACKCOLOR9

/**********************************************************************************************//**
 * \def	BBASELIGHTBLUE
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASELIGHTBLUE		BACKCOLOR10

/**********************************************************************************************//**
 * \def	BBASELIGHTGREEN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASELIGHTGREEN		BACKCOLOR11

/**********************************************************************************************//**
 * \def	BBASELIGHTCYAN
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASELIGHTCYAN		BACKCOLOR12

/**********************************************************************************************//**
 * \def	BBASELIGHTRED
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASELIGHTRED		BACKCOLOR13

/**********************************************************************************************//**
 * \def	BBASELIGHTMAGENTA
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASELIGHTMAGENTA	BACKCOLOR14

/**********************************************************************************************//**
 * \def	BBASEYELLOW
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define	BBASEYELLOW			BACKCOLOR15

/**********************************************************************************************//**
 * \def	BBASEWHITE
 *
 * \brief	Use this ones if you aren't using a new scheme.
 **************************************************************************************************/

#define BBASEWHITE			BACKCOLOR16

/**********************************************************************************************//**
 * \def	ALPHACOLOR
 *
 * \brief	This is used for choosing an alpha color in either of the .
 **************************************************************************************************/

#define ALPHACOLOR			100

/**********************************************************************************************//**
 * \def	CDMSET1
 *
 * \brief	Enumeration for quickly selecting data sets per pixel.
 **************************************************************************************************/

#define CDMSET1				0x0001

/**********************************************************************************************//**
 * \def	CDMSET2
 *
 * \brief	Enumeration for quickly selecting data sets per pixel.
 **************************************************************************************************/

#define CDMSET2				0x0002

/**********************************************************************************************//**
 * \def	CDMSET3
 *
 * \brief	Enumeration for quickly selecting data sets per pixel.
 **************************************************************************************************/

#define CDMSET3				0x0004

/**********************************************************************************************//**
 * \def	CDMSET4
 *
 * \brief	Enumeration for quickly selecting data sets per pixel.
 **************************************************************************************************/

#define CDMSET4				0x0008

/**********************************************************************************************//**
 * \def	CDMSETALPHA
 *
 * \brief	Sets an alpha color for the full pixel.
 **************************************************************************************************/

#define CDMSETALPHA			0x0010

/**********************************************************************************************//**
 * \def	CDMTRUE
 *
 * \brief	Boolean implementation.
 **************************************************************************************************/

#define CDMTRUE				1

/**********************************************************************************************//**
 * \def	CDMFALSE
 *
 * \brief	Boolean implementation.
 **************************************************************************************************/

#define CDMFALSE			0

#pragma region Inputs

#define CDMA		0
#define CDMB		1
#define CDMC		2
#define CDMD		3
#define CDME		4
#define CDMF		5
#define CDMG		6
#define CDMH		7
#define CDMI		8
#define CDMJ		9
#define CDMK		10
#define CDML		11
#define CDMM		12
#define CDMN		13
#define CDMO		14
#define CDMP		15
#define CDMQ		16
#define CDMR		17
#define CDMS		18
#define CDMT		19
#define CDMU		20
#define CDMV		21
#define CDMW		22
#define CDMX		23
#define CDMY		24
#define CDMZ		25
#define CDMLALT		26
#define CDMLSHIFT	27
#define CDMLCTRL	28
#define CDMRALT		29
#define CDMRSHIFT	30
#define CDMRCTRL	31
#define CDMESC		32
#define CDMRETURN	33
#define CDM1		34
#define CDM2		35
#define CDM3		36
#define CDM4		37
#define CDM5		38
#define CDM6		39
#define CDM7		40
#define CDM8		41
#define CDM9		42
#define CDM0		43
#define CDMCOMMA	47
#define CDMPERIOD	48
#define CDMBACKS	49
#define CDMLEFT		50
#define CDMRIGHT	51
#define CDMUP		52
#define CDMDOWN		53
#define CDMSPACE    54
#define CDMLMB		55
#define CDMRMB		56
#define CDMMMB		57
#pragma endregion !Inputs

#pragma endregion !Defines

/**********************************************************************************************//**
 * \typedef	SMALL_RECT CDMRect
 *
 * \brief	Defines an alias representing the cdm rectangle, contains a left, right, top and
 * 			bottom properties.
 **************************************************************************************************/

typedef SMALL_RECT		CDMRect;

/**********************************************************************************************//**
 * \typedef	COORD CDMCoord
 *
 * \brief	Defines an alias representing the cdm coordinate, contains an X and a Y property.
 **************************************************************************************************/

typedef COORD			CDMCoord;

/**********************************************************************************************//**
 * \typedef	char CDMEnum
 *
 * \brief	Defines an alias representing the cdm enum, this type is completely symbolic and
 * 			describes a parameter that requires to be filled with a macro.
 **************************************************************************************************/

typedef char			CDMEnum;

/**********************************************************************************************//**
 * \typedef	unsigned char CDMBool
 *
 * \brief	Defines an alias representing the cdm bool, its a simple boolean implementation for C.
 **************************************************************************************************/

typedef unsigned char	CDMBool;

/**********************************************************************************************//**
 * \typedef	unsigned char CDMErrno
 *
 * \brief	Defines an alias representing the cdm errno, a simple type for checking errors inside
 * 			the API.
 **************************************************************************************************/

typedef unsigned char	CDMErrno;

/**********************************************************************************************//**
 * \struct	CDMTiles
 *
 * \brief	A structure that contains raw data for the console to process, most structures used in
 * 			CDM require this component.
 **************************************************************************************************/

typedef struct CDMTiles
{
	CHAR_INFO		*printBufferCont;
	CDMBool			*alreadyDrawn,
					*isAlphaTile;
}CDMTiles;

/**********************************************************************************************//**
 * \struct	CDMEvent
 *
 * \brief	A structure containing the events required to check input inside CDM.
 **************************************************************************************************/

typedef struct CDMEvent {
	INPUT_RECORD	inputs[51];
	__int32			inputNum;
	CDMBool			inputPressed[64];
}CDMEvent;

/**********************************************************************************************//**
 * \struct	CDMContext
 *
 * \brief	A context in which CDM will run.
 **************************************************************************************************/

typedef struct CDMContext
{
	HANDLE							mainBuffer,
									backBuffer,
									InputBuffer;
	CDMBool							mainBufferActive;
	CONSOLE_SCREEN_BUFFER_INFOEX	inf;
	CDMTiles						contents;
	CDMRect							rect;

}CDMContext;

/**********************************************************************************************//**
 * \struct	CDMPixelData
 *
 * \brief	The data of a single pixel.
 **************************************************************************************************/

typedef struct CDMPixelData
{
	unsigned char	character,
					frontColor,
					backColor;
}CDMPixelData;

/**********************************************************************************************//**
 * \struct	CDMPalette
 *
 * \brief	A palette for a CDMSurface. It contains the four types of pixel that the surface is able
 * 			to be used.
 **************************************************************************************************/

typedef struct CDMPalette
{
	CDMPixelData	p1,
					p2,
					p3,
					p4;
}CDMPalette;

/**********************************************************************************************//**
 * \struct	CDMSurface
 *
 * \brief	A representation of an image that is able to be interpreted by CDM.
 **************************************************************************************************/

typedef struct CDMSurface 
{
	CDMPalette			pallete;
	CDMRect				rect;
	CDMEnum				*data;
	CDMTiles			bufferContents;
}CDMSurface;

/**********************************************************************************************//**
 * \struct	CDMText
 *
 * \brief	A representation of a text object able to be interpreted by CDM.
 **************************************************************************************************/

typedef struct CDMText
{
	short		frontColor,
				backColor;
	char		*data;
	CDMRect		rect;
	CDMTiles	bufferContents;
}CDMText;

/**********************************************************************************************//**
 * \struct	CDMColorScheme
 *
 * \brief	This structure serves the purpose of a color palette. You can select which palette is
 * 			active and displaying at any time using CDMSetActiveScheme.
 * 			The default values for colors are this, in binary. 
 * 			0x00362b00		Black
 * 			0x00423607		Gray 
 * 			0x00756e58		Green 
 * 			0x00837b65		Yellow 
 * 			0x00969483		Blue 
 * 			0x00a1a193		Aqua 
 * 			0x00d5e8ee		White 
 * 			0x00e3f6fd		BrightWhite 
 * 			0x000089b5		BrightYellow 
 * 			0x00164bcb		Red 
 * 			0x002f32dc		LightRed 
 * 			0x008236d3		LightPurple 
 * 			0x00c4716c		Purple 
 * 			0x00d28b26		LightBlue 
 * 			0x0098a12a		LightAqua 
 * 			0x00009985		LightGreen
 **************************************************************************************************/

typedef struct CDMColorScheme 
{
	COLORREF colors[16];
}CDMColorScheme;

#ifdef __cplusplus
/** \brief	. */
extern "C" {
#endif

	/**********************************************************************************************//**
	 * \fn	CDMContext* CDMCreateContext(const _IN_ short width, const _IN_ short height);
	 *
	 * \brief	The setup function of CDM. Must be called before anything else. CDM requires a
	 * 			context to work, most of the functions here require a context to be used. \warning
	 * 			This might not be thread safe.
	 *
	 * \param [in]	width 	The expected width in CDM pixels.
	 * \param [in]	height	The expected height in CDM pixels.
	 *
	 * \return	Null if it fails, else a pointer to a CDMContext.
	 **************************************************************************************************/

	CDMContext*	CDMCreateContext(const _IN_ short width, const _IN_ short height);

	/**********************************************************************************************//**
	 * \fn	void CDMChangeWindowSize(_INOUT_ CDMContext** ctx, const _IN_ short width, const _IN_ short height);
	 *
	 * \brief	Changes the window size of a context. May be called at any time, however it will
	 * 			clear the screen once its done.
	 *
	 * \param [in,out]	ctx   	The context, must not be null.
	 * \param [in]	  	width 	The expected width in CDM pixels.
	 * \param [in]	  	height	The expected height in CDM pixels.
	 **************************************************************************************************/

	void		CDMChangeWindowSize(_INOUT_ CDMContext** ctx,
							const _IN_ short width,
							const _IN_ short height);

	/**********************************************************************************************//**
	 * \fn	void CDMToggleFullscreen(CDMContext** _INOUT_ ctx, const _IN_ CDMBool val);
	 *
	 * \brief	Toggles fullscreen mode.
	 *
	 * \param [in,out]	ctx	If non-null, the context.
	 * \param [in]	  	val	Boolean value for the toggle.
	 **************************************************************************************************/

	void		CDMToggleFullscreen(CDMContext** _INOUT_ ctx, const _IN_ CDMBool val);

	/**********************************************************************************************//**
	 * \fn	void CDMSetWindowTitle(const _IN_ char* title);
	 *
	 * \brief	Sets the title of the console. Just a wrapper for a WINAPI functionality.
	 *
	 * \param [in]	title	The title of the console.
	 **************************************************************************************************/

	void		CDMSetWindowTitle(const _IN_ char* title);

	/**********************************************************************************************//**
	 * \fn	void CDMSetFontAndSize(_INOUT_ CDMContext** ctx, const _IN_ wchar_t* fontName, const _IN_ short width, const _IN_ short height);
	 *
	 * \brief	Sets the font and font size of the console. The recommended font name is L"Terminal"
	 * 			for its unique characteristic of allowing square pixels, however most fonts can be
	 * 			used. It's important to include L at the start of your string, since this function
	 * 			requires a wchar_t* instead of a regular char.
	 *
	 * \param [in,out]	ctx			The context, must not be null.
	 * \param [in]	  	fontName	Name of the font.
	 * \param [in]	  	width   	The width in regular pixels of the font.
	 * \param [in]	  	height  	The height in regular pixels of the font.
	 **************************************************************************************************/

	void		CDMSetFontAndSize(_INOUT_ CDMContext** ctx,
							const _IN_ wchar_t* fontName,
							const _IN_ short width,
							const _IN_ short height);

	/**********************************************************************************************//**
	 * \fn	void CDMSetCursorVisibility(_INOUT_ CDMContext** ctx, const _IN_ CDMBool status);
	 *
	 * \brief	Sets the visibility of the console's cursor.
	 *
	 * \param [in,out]	ctx   	If non-null, the context.
	 * \param 		  	status	Boolean value to set the status of the cursor.
	 **************************************************************************************************/

	void		CDMSetCursorVisibility(_INOUT_ CDMContext** ctx,
							const _IN_ CDMBool status);

	/**********************************************************************************************//**
	 * \fn	void CDMActivateMouseInput(_INOUT_ CDMContext** ctx);
	 *
	 * \brief	Activates mouse input recognition for the console.
	 *
	 * \param [in,out]	ctx	The context, must not be null.
	 **************************************************************************************************/

	void		CDMActivateMouseInput(_INOUT_ CDMContext** ctx);

	/**********************************************************************************************//**
	 * \fn	CDMSurface* CDMCreateSurface(const _IN_ short posX, const _IN_ short posY, const _IN_ short sizeX, const _IN_ short sizeY);
	 *
	 * \brief	Creates a surface. A surface is the base representation of an image in CDM Most every
	 * 			object used in CDM will most likely be a surface.
	 *
	 * \param [in]	posX 	The position x coordinate of the surface, using screen coordinates.
	 * \param [in]	posY 	The position y coordinate of the surface, using screen coordinates.
	 * \param [in]	sizeX	The width of the surface.
	 * \param [in]	sizeY	The height of the surface.
	 *
	 * \return	Null if it fails, else a pointer to a CDMSurface.
	 **************************************************************************************************/

	CDMSurface*	CDMCreateSurface(const _IN_ short posX,
							const _IN_ short posY,
							const _IN_ short sizeX,
							const _IN_ short sizeY);

	/**********************************************************************************************//**
	 * \fn	CDMSurface* CDMReadImg(const _IN_ char* fileName, _OUTOPT_ CDMColorScheme* scheme);
	 *
	 * \brief	Reads a .cdi image file into a CDMSurface. The file must be generated exactly the
	 * 			same as CDMExportSrfcToImg, for it to work using this function. The usage of the
	 * 			structure may be imperative.
	 *
	 * \param [in]		  	fileName	Filename of the file.
	 * \param [in,out,opt]	scheme  	[in,out,opt] If non-null, the scheme that will obtain the
	 * 									real scheme used in the image.
	 *
	 * \return	Null if it fails, else a pointer to a CDMSurface.
	 **************************************************************************************************/

	CDMSurface*	CDMReadImg(const _IN_ char* fileName, _OUTOPT_ CDMColorScheme* scheme);

	/**********************************************************************************************//**
	 * \fn	void CDMExportSrfcToImg(const _IN_ CDMContext* ctx, const _IN_ CDMSurface* srfc, const _IN_ char* fileName, const _IN_ size_t nameSize);
	 *
	 * \brief	Cdm export srfc to image
	 *
	 * \param [in]	ctx			The current context, must not be null.
	 * \param [in]	srfc		The surface intended to export, must not be null.
	 * \param [in]	fileName	Filename of the file.
	 * \param [in]	nameSize	Size of the name.
	 **************************************************************************************************/

	void		CDMExportSrfcToImg(const _IN_ CDMContext* ctx,
							const _IN_ CDMSurface* srfc,
							const _IN_ char* fileName,
							const _IN_ size_t nameSize);

	/**********************************************************************************************//**
	 * \fn	CDMText* CDMTextWrapper(_IN_ char * text, const _IN_ CDMEnum color, const _IN_ CDMEnum background);
	 *
	 * \brief	Since CDM basically highjacks the console, functions like printf are unabled to be
	 * 			used. No output will be shown using them, instead you must use the text as an object,
	 * 			this means you have much more control of the position and design of your text, at the
	 * 			expense of making a little bit harder to use. Moreover, repeated uses of the same
	 * 			text box will not require you to create a new object or call anything else other than
	 * 			adding this object to the context, or drawing it directly. All text begins in the ( 0
	 * 			, 0 ) coordinate.
	 *
	 * \param [in,out]	text	  	The text string, must not be null, must be zero terminated.
	 * \param [in]	  	color	  	The color of the text.
	 * \param [in]	  	background	The background color of the text.
	 *
	 * \return	Null if it fails, else a pointer to a CDMText.
	 **************************************************************************************************/

	CDMText*	CDMTextWrapper(_IN_ char * text,
		const _IN_ CDMEnum color,
		const _IN_ CDMEnum background);

	/**********************************************************************************************//**
	 * \fn	CDMText* CDMTextWrapper_s(_IN_ char * text, const _IN_ size_t textSize, const _IN_ CDMEnum color, const _IN_ CDMEnum background);
	 *
	 * \brief	Since CDM basically highjacks the console, functions like printf are unabled to be
	 * 			used. No output will be shown using them, instead you must use the text as an object,
	 * 			this means you have much more control of the position and design of your text, at the
	 * 			expense of making a little bit harder to use. Moreover, repeated uses of the same
	 * 			text box will not require you to create a new object or call anything else other than
	 * 			adding this object to the context, or drawing it directly. All text begins in the ( 0
	 * 			, 0 ) coordinate.
	 *
	 * \param [in,out]	text	  	The text string, must not be null.
	 * \param [in]	  	textSize  	Size of the text.
	 * \param [in]	  	color	  	The color of the text.
	 * \param [in]	  	background	The background color of the text.
	 *
	 * \return	Null if it fails, else a pointer to a CDMText.
	 **************************************************************************************************/

	CDMText*	CDMTextWrapper_s(_IN_ char * text,
							const _IN_ size_t textSize,
							const _IN_ CDMEnum color,
							const _IN_ CDMEnum background);

	/**********************************************************************************************//**
	 * \fn	void CDMChangeText(CDMText** txt, const _IN_ char * text);
	 *
	 * \brief	Changes the text content of a CDMText.
	 *
	 * \param [in,out]	txt 	The text object, must not be null.
	 * \param [in]	  	text	The text, null terminated.
	 **************************************************************************************************/

	void		CDMChangeText(CDMText** txt, const _IN_ char * text);

	/**********************************************************************************************//**
	 * \fn	void CDMSetForegroundColor(_INOUT_ CDMSurface** surface, const _IN_ CDMEnum c1, const _IN_ CDMEnum c2, const _IN_ CDMEnum c3, const _IN_ CDMEnum c4);
	 *
	 * \brief	A CDMSurface may only have 4 color sets at a time. Including background, foreground
	 * 			and character. Each combination of 3 of those elements makes a set. This function
	 * 			sets directly the four foreground colors that the Surface will use from the color
	 * 			palette.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 * \param [in]	  	c1	   	The first CDMEnum using color macros.
	 * \param [in]	  	c2	   	The second CDMEnum using color macros.
	 * \param [in]	  	c3	   	The third CDMEnum using color macros.
	 * \param [in]	  	c4	   	The fourth CDMEnum using color macros.
	 **************************************************************************************************/

	void		CDMSetForegroundColor(_INOUT_ CDMSurface** surface,
							const _IN_ CDMEnum c1,
							const _IN_ CDMEnum c2,
							const _IN_ CDMEnum c3,
							const _IN_ CDMEnum c4);

	/**********************************************************************************************//**
	 * \fn	void CDMSetBackgroundColor(_INOUT_ CDMSurface** surface, const _IN_ CDMEnum c1, const _IN_ CDMEnum c2, const _IN_ CDMEnum c3, const _IN_ CDMEnum c4);
	 *
	 * \brief	A CDMSurface may only have 4 color sets at a time. Including background, foreground
	 * 			and character. Each combination of 3 of those elements makes a set. This function
	 * 			sets directly the four background colors that the Surface will use from the color
	 * 			palette.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 * \param [in]	  	c1	   	The first CDMEnum using color macros.
	 * \param [in]	  	c2	   	The second CDMEnum using color macros.
	 * \param [in]	  	c3	   	The third CDMEnum using color macros.
	 * \param [in]	  	c4	   	The fourth CDMEnum using color macros.
	 **************************************************************************************************/

	void		CDMSetBackgroundColor(_INOUT_ CDMSurface** surface,
							const _IN_ CDMEnum c1,
							const _IN_ CDMEnum c2,
							const _IN_ CDMEnum c3,
							const _IN_ CDMEnum c4);

	/**********************************************************************************************//**
	 * \fn	void CDMSetCharacters(_INOUT_ CDMSurface** surface, const _IN_ CDMEnum c1, const _IN_ CDMEnum c2, const _IN_ CDMEnum c3, const _IN_ CDMEnum c4);
	 *
	 * \brief	A CDMSurface may only have 4 color sets at a time. Including background, foreground
	 * 			and character. Each combination of 3 of those elements makes a set. This function
	 * 			sets directly the four characters that the Surface will use.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 * \param [in]	  	c1	   	The first CDMEnum using color macros.
	 * \param [in]	  	c2	   	The second CDMEnum using color macros.
	 * \param [in]	  	c3	   	The third CDMEnum using color macros.
	 * \param [in]	  	c4	   	The fourth CDMEnum using color macros.
	 **************************************************************************************************/

	void		CDMSetCharacters(_INOUT_ CDMSurface** surface,
							const _IN_ CDMEnum c1,
							const _IN_ CDMEnum c2,
							const _IN_ CDMEnum c3,
							const _IN_ CDMEnum c4);

	/**********************************************************************************************//**
	 * \fn	int CDMSwapBuffer(_IN_ CDMContext* const ctx);
	 *
	 * \brief	CDM runs in a two buffers rendering architecture. Swapping the buffers will be
	 * 			necessary for CDM to draw properly. Calling this function easies things a lot.
	 *
	 * \param [in,out]	ctx	context, must not be null.
	 *
	 * \return	The index of the new current buffer.
	 **************************************************************************************************/

	int			CDMSwapBuffer(_IN_ CDMContext* const ctx);

	/**********************************************************************************************//**
	 * \fn	void CDMFreeSurface(_INOUT_ CDMSurface** surface);
	 *
	 * \brief	Simple dynamic memory allocation free method.
	 *
	 * \param [in,out]	surface	The surface, must not be null. Upon finishing this function makes
	 * 							this parameter's value null.
	 **************************************************************************************************/

	void		CDMFreeSurface(_INOUT_ CDMSurface** surface);

	/**********************************************************************************************//**
	 * \fn	void CDMFreeText(_INOUT_ CDMText** txt);
	 *
	 * \brief	Simple dynamic memory allocation free method.
	 *
	 * \param [in,out]	txt	The text, must not be null. Upon finishing, this function makes this
	 * 						parameter's value null.
	 **************************************************************************************************/

	void		CDMFreeText(_INOUT_ CDMText** txt);

	/**********************************************************************************************//**
	 * \fn	void CDMFreeContext(_INOUT_ CDMContext** ctx);
	 *
	 * \brief	Simple dynamic memory allocation free method.
	 *
	 * \param [in,out]	ctx	The context, must not be null. Upon finishing, this function makes this
	 * 						parameter's value null.
	 **************************************************************************************************/

	void		CDMFreeContext(_INOUT_ CDMContext** ctx);

	/**********************************************************************************************//**
	 * \fn	void CDMPrepareSurface(_INOUT_ CDMSurface** surface);
	 *
	 * \brief	This should only be called each time the surface's contents were modified before
	 * 			calling a draw or add function. Internally this function converts the image's values
	 * 			to raw data that the console understands.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 **************************************************************************************************/

	void		CDMPrepareSurface(_INOUT_ CDMSurface** surface);

	/**********************************************************************************************//**
	 * \fn	void CDMPrepareText(_INOUT_ CDMText** txt);
	 *
	 * \brief	This should only be called each time the text's contents were modified before calling
	 * 			a draw or add function. Internally this function converts the text's values to raw
	 * 			data that the console understands.
	 *
	 * \param [in,out]	txt	The text, must not be null.
	 **************************************************************************************************/

	void		CDMPrepareText(_INOUT_ CDMText** txt);

	/**********************************************************************************************//**
	 * \fn	void CDMDrawSurface(_INOUT_ CDMContext ** ctx, _IN_ CDMSurface * surface);
	 *
	 * \brief	Draws directly a surface in the context, instead of batching it with other draws. I
	 * 			highly recommend using the batch function (Add, then CDMDraw) over this one, to make
	 * 			the program run faster.
	 *
	 * \param [in,out]	ctx	   	The context in which the surface will be painted, must not be null.
	 * \param [in,out]	surface	The surface to be printed, must not be null.
	 **************************************************************************************************/

	void		CDMDrawSurface(_INOUT_ CDMContext ** ctx, _IN_ CDMSurface * surface);

	/**********************************************************************************************//**
	 * \fn	void CDMAddSurfaceToContext(_INOUT_ CDMContext** ctx, _IN_ CDMSurface* surface);
	 *
	 * \brief	Adds a surface to the context, and thus batching its draw with every other added
	 * 			object, the batch will be completely flushed once CDMDraw is called.
	 *
	 * \param [in,out]	ctx	   	The context in which the surface will be painted, must not be null.
	 * \param [in,out]	surface	The surface to be printed, must not be null.
	 **************************************************************************************************/

	void		CDMAddSurfaceToContext(_INOUT_ CDMContext** ctx, _IN_ CDMSurface* surface);

	/**********************************************************************************************//**
	 * \fn	void CDMDrawText(_INOUT_ CDMContext ** ctx, _IN_ CDMText * txt);
	 *
	 * \brief	Draws directly a text in the context, instead of batching it with other draws. I
	 * 			highly recommend using the batch function (Add, then CDMDraw) over this one, to make
	 * 			the program run faster.
	 *
	 * \param [in,out]	ctx	The context in which the text will be painted, must not be null.
	 * \param [in,out]	txt	The text that will be printed, must not be null.
	 **************************************************************************************************/

	void		CDMDrawText(_INOUT_ CDMContext ** ctx, _IN_ CDMText * txt);

	/**********************************************************************************************//**
	 * \fn	void CDMAddTextToContext(_INOUT_ CDMContext** ctx, _IN_ CDMText* txt);
	 *
	 * \brief	Adds a text to the context, and thus batching its draw with every other added object,
	 * 			the batch will be completely flushed once CDMDraw is called.
	 *
	 * \param [in,out]	ctx	The context in which the text will be painted, must not be null.
	 * \param [in,out]	txt	The text that will be printed, must not be null.
	 **************************************************************************************************/

	void		CDMAddTextToContext(_INOUT_ CDMContext** ctx, _IN_ CDMText* txt);

	/**********************************************************************************************//**
	 * \fn	void CDMSetColorRGB(_INOUT_ CDMColorScheme* data, _IN_ short position, _IN_ short r, _IN_ short g, _IN_ short b);
	 *
	 * \brief	Sets an RGB color inside a ColorScheme. Every color goes from 0 to 255, however every
	 * 			value passes through a modulo operation to assure no weird behaviour will happen.
	 *
	 * \param [in,out]	data		The color scheme, must not be null.
	 * \param [in]	  	position	The position of the color inside the ColorScheme.
	 * \param [in]	  	r			Red value.
	 * \param [in]	  	g			Green value.
	 * \param [in]	  	b			Blue value.
	 **************************************************************************************************/

	void		CDMSetColorRGB(_INOUT_ CDMColorScheme* data,
							_IN_ short position,
							_IN_ short r, 
							_IN_ short g, 
							_IN_ short b);

	/**********************************************************************************************//**
	 * \fn	void CDMSetColorBin(_INOUT_ CDMColorScheme* data, _IN_ short position, const _IN_ DWORD color);
	 *
	 * \brief	Sets an RGB color inside a ColorScheme. This function accepts an already converted to
	 * 			binary RGB color. You may use Windows.h macro RGB(r,g,b) to get the data.
	 *
	 * \param [in,out]	data		The color scheme, must not be null.
	 * \param [in]	  	position	The position of the color inside the ColorScheme.
	 * \param [in]	  	color   	The binary RGB color.
	 **************************************************************************************************/

	void		CDMSetColorBin(_INOUT_ CDMColorScheme* data,
							_IN_ short position,
							const _IN_ DWORD color);

	/**********************************************************************************************//**
	 * \fn	void CDMClearScreen(_INOUT_ CDMContext ** ctx);
	 *
	 * \brief	Clears the current buffer of undrawn data. It does not make the whole screen black.
	 * 			For that you may use CDMFillScreen.This function is implemented like this to reduce
	 * 			overhead on the program by reducing assignations and comparissons.
	 *
	 * \param [in,out]	ctx	The context, must not be null.
	 **************************************************************************************************/

	void		CDMClearScreen(_INOUT_ CDMContext ** ctx);

	/**********************************************************************************************//**
	 * \fn	void CDMFillScreen(_INOUT_ CDMContext ** ctx, const _IN_ char character, const _IN_ CDMEnum frontColor, const _IN_ CDMEnum backColor);
	 *
	 * \brief	Fills the context with a single color. Ignores drawn flags completely.
	 *
	 * \param [in,out]	ctx		  	The context, must not be null.
	 * \param [in]	  	character 	The character to be printed.
	 * \param [in]	  	frontColor	The front color.
	 * \param [in]	  	backColor 	The background color.
	 **************************************************************************************************/

	void		CDMFillScreen(_INOUT_ CDMContext ** ctx,
							const _IN_ char character,
							const _IN_ CDMEnum frontColor,
							const _IN_ CDMEnum backColor);

	/**********************************************************************************************//**
	 * \fn	void CDMPoke(_INOUT_ CDMContext ** ctx, const _IN_ CDMCoord coord, const _IN_ char character, const _IN_ CDMEnum frontColor, const _IN_ CDMEnum backColor);
	 *
	 * \brief	Pokes a pixel in the screen to a certain color. Ignores drawn flags.
	 *
	 * \param [in,out]	ctx		  	The context, must not be null.
	 * \param [in]	  	coord	  	The coordinate of the pixel.
	 * \param [in]	  	character 	The character to be printed.
	 * \param [in]	  	frontColor	The front color.
	 * \param [in]	  	backColor 	The background color.
	 **************************************************************************************************/

	void		CDMPoke(_INOUT_ CDMContext ** ctx,
							const _IN_ CDMCoord coord,
							const _IN_ char character,
							const _IN_ CDMEnum frontColor,
							const _IN_ CDMEnum backColor);

	/**********************************************************************************************//**
	 * \fn	void CDMDraw(_IN_ CDMContext* ctx);
	 *
	 * \brief	Draws the whole screen. Does a batch draw if things have been added to the context.
	 *
	 * \param [in]	The context, must not be null.
	 **************************************************************************************************/

	void		CDMDraw(_IN_ CDMContext* ctx);

	/**********************************************************************************************//**
	 * \fn	int CDMGetR(_IN_ CDMColorScheme* data, const _IN_ short position);
	 *
	 * \brief	Gets the red color of a certain color inside a ColorScheme.
	 *
	 * \param [in]		data		The color scheme to check from.
	 * \param [in]	  	position	The position of the color wanted.
	 *
	 * \return	The color's value in decimal.
	 **************************************************************************************************/

	int			CDMGetR(_IN_ CDMColorScheme* data, const _IN_ short position);

	/**********************************************************************************************//**
	 * \fn	int CDMGetG(_IN_ CDMColorScheme* data, const _IN_ short position);
	 *
	 * \brief	Gets the green color of a certain color inside a ColorScheme.
	 *
	 * \param [in]		data		The color scheme to check from.
	 * \param [in]	  	position	The position of the color wanted.
	 *
	 * \return	The color's value in decimal.
	 **************************************************************************************************/

	int			CDMGetG(_IN_ CDMColorScheme* data, const _IN_ short position);

	/**********************************************************************************************//**
	 * \fn	int CDMGetB(_IN_ CDMColorScheme* data, const _IN_ short position);
	 *
	 * \brief	Gets the blue color of a certain color inside a ColorScheme.
	 *
	 * \param [in]		data		The color scheme to check from.
	 * \param [in]	  	position	The position of the color wanted.
	 *
	 * \return	The color's value in decimal.
	 **************************************************************************************************/

	int			CDMGetB(_IN_ CDMColorScheme* data, const _IN_ short position);

	/**********************************************************************************************//**
	 * \fn	void CDMSetActiveScheme(_IN_ CDMColorScheme data, _INOUT_ CDMContext** ctx);
	 *
	 * \brief	Sets a color scheme inside a context, and thus changing every display color of it.
	 * 			This instruction does not require you to draw again for results to be shown, as such
	 * 			its extremely fast.
	 *
	 * \param [in]	  	data	The color scheme to be set.
	 * \param [in,out]	ctx 	The context to modify, must not be null.
	 **************************************************************************************************/

	void		CDMSetActiveScheme(_IN_ CDMColorScheme data, _INOUT_ CDMContext** ctx);

	/**********************************************************************************************//**
	 * \fn	void CDMSetPixel(_INOUT_ CDMSurface** surface, _IN_ short x, _IN_ short y, _IN_ CDMEnum pixelSet);
	 *
	 * \brief	Sets a pixel inside a surface. You must select from one of the five possible colors
	 * 			inside the surface.
	 *
	 * \param [in,out]	surface 	The surface to be modified, must not be null.
	 * \param [in]	  	x			The x coordinate of the pixel.
	 * \param [in]	  	y			The y coordinate of the pixel.
	 * \param [in]	  	pixelSet	The enumeration value of the data.
	 **************************************************************************************************/

	void		CDMSetPixel(_INOUT_ CDMSurface** surface,
							_IN_ short x,
							_IN_ short y,
							_IN_ CDMEnum pixelSet);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMCompareCHARINFO(_IN_ CHAR_INFO rhs, _IN_ CHAR_INFO lhs);
	 *
	 * \brief	Compares two CHAR_INFO structures, it's mainly used inside the API for certain 
	 * 			operations. May not prove useful to the graphics programmer. 
	 *
	 * \param [in]	rhs	The right hand side.
	 * \param [in]	lhs	The left hand side.
	 *
	 * \return	CDMTRUE if both structures are the same, else CDMFALSE.
	 **************************************************************************************************/

	CDMBool		CDMCompareCHARINFO(_IN_ CHAR_INFO rhs, _IN_ CHAR_INFO lhs);

	/**********************************************************************************************//**
	 * \fn	void CDMPollEvents(_IN_ CDMContext* ctx, _INOUT_ CDMEvent* event);
	 *
	 * \brief	Polls the console events, this function must be used in order to get key and mouse
	 * 			presses, as such it must be called at the beggining of every frame and before every
	 * 			function that requires a CDMEvent.
	 *
	 * \param [in,out]	ctx  	The context, must not be null.
	 * \param [in,out]	event	An event structure, must not be null.
	 **************************************************************************************************/

	void		CDMPollEvents(_IN_ CDMContext* ctx, _INOUT_ CDMEvent* event);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMGetKeyPressed(_IN_ CDMEvent* event, const _IN_ CDMEnum key);
	 *
	 * \brief	Checks if the key selected in the parameter was pressed.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 * \param [in]	  	key  	The key to be checked.
	 *
	 * \return	Returns CDMTRUE if the key is pressed, regardless of how many frames it has been
	 * 			pressed, CDMFALSE if the key is not pressed.
	 **************************************************************************************************/

	CDMBool		CDMGetKeyPressed(_IN_ CDMEvent* event, const _IN_ CDMEnum key);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMGetKeyDown(_IN_ CDMEvent* event, const _IN_ CDMEnum key);
	 *
	 * \brief	Checks if the key selected in the parameter was pressed this frame.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 * \param 		  	key  	The key to be checked.
	 *
	 * \return	Returns CDMTRUE if the key is pressed, but only if it was pressed in this frame,
	 * 			CDMFALSE if the key is not pressed.
	 **************************************************************************************************/

	CDMBool		CDMGetKeyDown(_IN_ CDMEvent* event, const _IN_ CDMEnum key);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMGetKeyUp(_IN_ CDMEvent* event, const _IN_ CDMEnum key);
	 *
	 * \brief	Checks if the key selected in the parameter stopped being pressed this frame.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 * \param 		  	key  	The key to be checked.
	 *
	 * \return	Returns CDMTRUE if the key is not pressed, but only if it was pressed in the last
	 * 			frame, CDMFALSE if the key is pressed.
	 **************************************************************************************************/

	CDMBool		CDMGetKeyUp(_IN_ CDMEvent* event, const _IN_ CDMEnum key);

	/**********************************************************************************************//**
	 * \fn	CDMCoord CDMGetMousePos(_IN_ CDMEvent* event);
	 *
	 * \brief	Gets the mouse position inside the console window.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 *
	 * \return	A CDMCoord containing the coordinates of the mouse inside the screen.
	 **************************************************************************************************/

	CDMCoord	CDMGetMousePos(_IN_ CDMEvent* event);

	/**********************************************************************************************//**
	 * \fn	void CDMKeepScreenSize(_INOUT_ CDMContext** ctx, _IN_ CDMEvent* event);
	 *
	 * \brief	Keeps the screen size of the program. Might be useful if you want to limit screen
	 * 			resizing.
	 *
	 * \param [in,out]	ctx  	The context, must not be null.
	 * \param [in,out]	event	An event structure to check for resize events, must not be null.
	 **************************************************************************************************/

	void		CDMKeepScreenSize(_INOUT_ CDMContext** ctx, _IN_ CDMEvent* event);

	/**********************************************************************************************//**
	 * \fn	void CDMSetErrno(const _IN_ CDMErrno code);
	 *
	 * \brief	Sets an specific errno to a value.
	 *
	 * \param	code	The code to be set.
	 **************************************************************************************************/

	void		CDMSetErrno(const _IN_ CDMErrno code);

	/**********************************************************************************************//**
	 * \fn	CDMErrno CDMGetErrno();
	 *
	 * \brief	Gets the value of errno and sets it to zero.
	 *
	 * \return	The value of errno.
	 **************************************************************************************************/

	CDMErrno	CDMGetErrno();

	/**********************************************************************************************//**
	 * \fn	char* CDMGetErrorMessage();
	 *
	 * \brief	Translates an error code to an error message, for a brief description.
	 *
	 * \return	Will always return a string of characters.
	 **************************************************************************************************/

	char*		CDMGetErrorMessage();

	/**********************************************************************************************//**
	 * \fn	void CDMClearErrno();
	 *
	 * \brief	Sets errno back to 0.
	 **************************************************************************************************/

	void		CDMClearErrno();

#ifdef __cplusplus
}
#endif
