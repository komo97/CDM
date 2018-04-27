
/**
* @file CDM.h
* @about Description
* Console Draw Motor
* Library for creating 2D Games for the Windows CMD.
* For exclusive use with Windows. Not compatible for versions lower than Windows vista.
* This library only provides the C functions for drawing on the console, 
* and the structures for its usage.
* For a Full hd device the maximum screen size is 237x124 using the terminal font and
* an 8x8 pixel per tile.
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

//#define PIXELBYPIXEL

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

typedef enum CDMLetterColor {
	CLEAR = -1,
	BLACK = 0,
	DARKBLUE = FOREGROUND_BLUE,
	DARKGREEN = FOREGROUND_GREEN,
	DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	DARKRED = FOREGROUND_RED,
	DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	GRAY = FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	LCOLOR1 = BLACK,
	LCOLOR2 = DARKBLUE,
	LCOLOR3 = DARKGREEN,
	LCOLOR4 = DARKCYAN,
	LCOLOR5 = DARKRED,
	LCOLOR6 = DARKMAGENTA,
	LCOLOR7 = DARKYELLOW,
	LCOLOR8 = DARKGRAY,
	LCOLOR9 = GRAY,
	LCOLOR10 = GREEN,
	LCOLOR11 = CYAN,
	LCOLOR12 = RED,
	LCOLOR13 = MAGENTA,
	LCOLOR14 = YELLOW,
	LCOLOR15 = WHITE,
} CDMLetterColor;

typedef enum CDMBackgroundColor {
	BCLEAR = -1,
	BBLACK = 0,
	BDARKBLUE = BACKGROUND_BLUE,
	BDARKGREEN = BACKGROUND_GREEN,
	BDARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
	BDARKRED = BACKGROUND_RED,
	BDARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
	BDARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
	BDARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BGRAY = BACKGROUND_INTENSITY,
	BBLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
	BGREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
	BCYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BRED = BACKGROUND_INTENSITY | BACKGROUND_RED,
	BMAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
	BYELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
	BWHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	BCOLOR1 =  BBLACK,
	BCOLOR2 =  BDARKBLUE,
	BCOLOR3 =  BDARKGREEN,
	BCOLOR4 =  BDARKCYAN,
	BCOLOR5 =  BDARKRED,
	BCOLOR6 =  BDARKMAGENTA,
	BCOLOR7 =  BDARKYELLOW,
	BCOLOR8 =  BDARKGRAY,
	BCOLOR9 =  BGRAY,
	BCOLOR10 = BGREEN,
	BCOLOR11 = BCYAN,
	BCOLOR12 = BRED,
	BCOLOR13 = BMAGENTA,
	BCOLOR14 = BYELLOW,
	BCOLOR15 = BWHITE,
} CDMBackgroundColor;

typedef enum CDMExtraOptions {
	reverseColors = COMMON_LVB_REVERSE_VIDEO,
	underscore = COMMON_LVB_UNDERSCORE,
	Alpha = 100,
}CDMExtraOptions;

typedef enum CDMColorSets
{
	Set1 = 0x0001,
	Set2 = 0x0002,
	Set3 = 0x0004,
	Set4 = 0x0008,
	SetAlpha = 0x0010,
}CDMColorSets;

typedef enum CDMBool
{
	CDMFalse = 0,
	CDMTrue = 1,
}CDMBool;

#pragma region Inputs

typedef enum CDMKey {
	mbleft = VK_LBUTTON,
	mbright = VK_RBUTTON,
	backspace = VK_BACK,
	tab = VK_TAB,
	clear = VK_CLEAR,
	returnK = VK_RETURN,
	shift = VK_SHIFT,
	ctrl = VK_CONTROL,
	alt = VK_MENU,
	pause = VK_PAUSE,
	caps = VK_CAPITAL,
	esc = VK_ESCAPE,
	space = VK_SPACE,
	pgup = VK_PRIOR,
	pgdown = VK_NEXT,
	end = VK_END,
	left = VK_LEFT,
	right = VK_RIGHT,
	up = VK_UP,
	down = VK_DOWN,
	print = VK_PRINT,
	insert = VK_INSERT,
	del = VK_DELETE,
	zero = 0x30,
	one = 0x31,
	two = 0x32,
	three = 0x33,
	four = 0x34,
	five = 0x35,
	six = 0x36,
	seven = 0x37,
	eight = 0x38,
	nine = 0x39,
	A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	add = 0x6B,
	separator,
	substract,
	decimal,
	divide,
	f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
	lshift = 0xA0,
	rshift,
	lctrl,
	rctrl,
	lalt,
	ralt,
	KeysEnd,
} CDMKey;
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
 * 			describes a parameter that requires to be filled with an enum.
 **************************************************************************************************/

typedef char			CDMEnum;

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
	CDMBool			*isAlphaTile;
}CDMTiles;

/**********************************************************************************************//**
 * \struct	CDMEvent
 *
 * \brief	A structure containing the events required to check input inside CDM.
 **************************************************************************************************/

typedef struct CDMEvent {
	INPUT_RECORD	inputs[64];
	__int32			inputNum;
	CDMBool			inputPressed[KeysEnd];
}CDMEvent;

/**********************************************************************************************//**
 * \struct	CDMContext
 *
 * \brief	A context in which CDM will run.
 **************************************************************************************************/

typedef struct CDMContext
{
	HANDLE							mainBuffer,
									inputBuffer;
	CONSOLE_SCREEN_BUFFER_INFOEX	inf;
	CDMTiles						contents,
									lastFrameContents;
	CDMRect							rect;
	CDMEvent						events;
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
	 * 			context to work, most of the functions here require a context to be used. 
	 *			Status: Working.
	 * \warning This might not be thread safe.
	 * 			 
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
	 *			Status: Might not be working completely.
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
	 *			Status: May be working on older platforms.
	 *
	 * \param [in,out]	ctx	If non-null, the context.
	 * \param [in]	  	val	Boolean value for the toggle.
	 **************************************************************************************************/

	void		CDMToggleFullscreen(CDMContext** _INOUT_ ctx, const _IN_ CDMBool val);

	/**********************************************************************************************//**
	 * \fn	void CDMSetWindowTitle(const _IN_ char* title);
	 *
	 * \brief	Sets the title of the console. Just a wrapper for a WINAPI functionality.
	 *			Status: Working.
	 *
	 * \param [in]	title	The title of the console.
	 **************************************************************************************************/

	void		CDMSetWindowTitle(const _IN_ wchar_t* title);

	/**********************************************************************************************//**
	 * \fn	void CDMSetFontAndSize(_INOUT_ CDMContext** ctx, const _IN_ wchar_t* fontName, const _IN_ short width, const _IN_ short height);
	 *
	 * \brief	Sets the font and font size of the console. The recommended font name is L"Terminal"
	 * 			for its unique characteristic of allowing square pixels, however most fonts can be
	 * 			used. It's important to include L at the start of your string, since this function
	 * 			requires a wchar_t* instead of a regular char.
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
	 *
	 * \param [in,out]	ctx	The context, must not be null.
	 **************************************************************************************************/

	void		CDMActivateMouseInput(_INOUT_ CDMContext** ctx);

	/**********************************************************************************************//**
	 * \fn	CDMSurface* CDMCreateSurface(const _IN_ short posX, const _IN_ short posY, const _IN_ short sizeX, const _IN_ short sizeY);
	 *
	 * \brief	Creates a surface. A surface is the base representation of an image in CDM Most every
	 * 			object used in CDM will most likely be a surface.
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
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
	 * \brief	Since CDM basically highjacks the console, functions like printf are not enabled. 
	 *			No output will be shown using them, instead you must use the text as an object,
	 * 			this means you have much more control of the position and design of your text, at the
	 * 			expense of making a little bit harder to use. Moreover, repeated uses of the same
	 * 			text box will not require you to create a new object or call anything else other than
	 * 			adding this object to the context, or drawing it directly. All text begins in the ( 0
	 * 			, 0 ) coordinate.
	 *			Status: Working.
	 *
	 * \param [in,out]	text	  	The text string, must not be null, must be zero terminated.
	 * \param [in]	  	color	  	The color of the text.
	 * \param [in]	  	background	The background color of the text.
	 *
	 * \return	Null if it fails, else a pointer to a CDMText.
	 **************************************************************************************************/

	CDMText*	CDMTextWrapper(_IN_ char * text,
		const _IN_ CDMLetterColor color,
		const _IN_ CDMBackgroundColor background);

	/**********************************************************************************************//**
	 * \fn	CDMText* CDMTextWrapper_s(_IN_ char * text, const _IN_ size_t textSize, const _IN_ CDMEnum color, const _IN_ CDMEnum background);
	 *
	 * \brief	Since CDM basically highjacks the console, functions like printf are disabled. 
	 *			No output will be shown using them, instead you must use the text as an object,
	 * 			this means you have much more control of the position and design of your text, at the
	 * 			expense of making a little bit harder to use. Moreover, repeated uses of the same
	 * 			text box will not require you to create a new object or call anything else other than
	 * 			adding this object to the context, or drawing it directly. All text begins in the ( 0
	 * 			, 0 ) coordinate.
	 *			Status: Working.
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
							const _IN_ CDMLetterColor color,
							const _IN_ CDMBackgroundColor background);

	/**********************************************************************************************//**
	 * \fn	void CDMChangeText(CDMText** txt, const _IN_ char * text);
	 *
	 * \brief	Changes the text content of a CDMText.
	 *			Status: Working.
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
	 *			Status: Working.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 * \param [in]	  	c1	   	The first CDMEnum using color macros.
	 * \param [in]	  	c2	   	The second CDMEnum using color macros.
	 * \param [in]	  	c3	   	The third CDMEnum using color macros.
	 * \param [in]	  	c4	   	The fourth CDMEnum using color macros.
	 **************************************************************************************************/

	void		CDMSetForegroundColor(_INOUT_ CDMSurface** surface,
							const _IN_ CDMLetterColor c1,
							const _IN_ CDMLetterColor c2,
							const _IN_ CDMLetterColor c3,
							const _IN_ CDMLetterColor c4);

	/**********************************************************************************************//**
	 * \fn	void CDMSetBackgroundColor(_INOUT_ CDMSurface** surface, const _IN_ CDMEnum c1, const _IN_ CDMEnum c2, const _IN_ CDMEnum c3, const _IN_ CDMEnum c4);
	 *
	 * \brief	A CDMSurface may only have 4 color sets at a time. Including background, foreground
	 * 			and character. Each combination of 3 of those elements makes a set. This function
	 * 			sets directly the four background colors that the Surface will use from the color
	 * 			palette.
	 *			Status: Working.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 * \param [in]	  	c1	   	The first CDMEnum using color macros.
	 * \param [in]	  	c2	   	The second CDMEnum using color macros.
	 * \param [in]	  	c3	   	The third CDMEnum using color macros.
	 * \param [in]	  	c4	   	The fourth CDMEnum using color macros.
	 **************************************************************************************************/

	void		CDMSetBackgroundColor(_INOUT_ CDMSurface** surface,
							const _IN_ CDMBackgroundColor c1,
							const _IN_ CDMBackgroundColor c2,
							const _IN_ CDMBackgroundColor c3,
							const _IN_ CDMBackgroundColor c4);

	/**********************************************************************************************//**
	 * \fn	void CDMSetCharacters(_INOUT_ CDMSurface** surface, const _IN_ CDMEnum c1, const _IN_ CDMEnum c2, const _IN_ CDMEnum c3, const _IN_ CDMEnum c4);
	 *
	 * \brief	A CDMSurface may only have 4 color sets at a time. Including background, foreground
	 * 			and character. Each combination of 3 of those elements makes a set. This function
	 * 			sets directly the four characters that the Surface will use.
	 *			Status: Working.
	 *
	 * \param [in,out]	surface	The surface, must not be null.
	 * \param [in]	  	c1	   	The first character to be used.
	 * \param [in]	  	c2	   	The second character to be used.
	 * \param [in]	  	c3	   	The third character to be used.
	 * \param [in]	  	c4	   	The fourth character to be used.
	 **************************************************************************************************/

	void		CDMSetCharacters(_INOUT_ CDMSurface** surface,
							const _IN_ unsigned char c1,
							const _IN_ unsigned char c2,
							const _IN_ unsigned char c3,
							const _IN_ unsigned char c4);

	/**********************************************************************************************//**
	 * \fn	void CDMFreeSurface(_INOUT_ CDMSurface** surface);
	 *
	 * \brief	Simple dynamic memory allocation free method.
	 *			Status: Working.
	 *
	 * \param [in,out]	surface	The surface, must not be null. Upon finishing this function makes
	 * 							this parameter's value null.
	 **************************************************************************************************/

	void		CDMFreeSurface(_INOUT_ CDMSurface** surface);

	/**********************************************************************************************//**
	 * \fn	void CDMFreeText(_INOUT_ CDMText** txt);
	 *
	 * \brief	Simple dynamic memory allocation free method.
	 *			Status: Working.
	 *
	 * \param [in,out]	txt	The text, must not be null. Upon finishing, this function makes this
	 * 						parameter's value null.
	 **************************************************************************************************/

	void		CDMFreeText(_INOUT_ CDMText** txt);

	/**********************************************************************************************//**
	 * \fn	void CDMFreeContext(_INOUT_ CDMContext** ctx);
	 *
	 * \brief	Simple dynamic memory allocation free method.
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Partiallly works.
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
	 *			Status: Working.
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
	 *			Status: Partially Works.
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
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
	 *
	 * \param [in,out]	ctx	The context, must not be null.
	 **************************************************************************************************/

	void		CDMClearScreen(_INOUT_ CDMContext ** ctx);

	/**********************************************************************************************//**
	 * \fn	void CDMFillScreen(_INOUT_ CDMContext ** ctx, const _IN_ char character, const _IN_ CDMEnum frontColor, const _IN_ CDMEnum backColor);
	 *
	 * \brief	Fills the context with a single color. Ignores drawn flags completely.
	 *			Status: Working.
	 *
	 * \param [in,out]	ctx		  	The context, must not be null.
	 * \param [in]	  	character 	The character to be printed.
	 * \param [in]	  	frontColor	The front color.
	 * \param [in]	  	backColor 	The background color.
	 **************************************************************************************************/

	void		CDMFillScreen(_INOUT_ CDMContext ** ctx,
							const _IN_ char character,
							const _IN_ CDMLetterColor frontColor,
							const _IN_ CDMBackgroundColor backColor);

	/**********************************************************************************************//**
	 * \fn	void CDMPoke(_INOUT_ CDMContext ** ctx, const _IN_ CDMCoord coord, const _IN_ char character, const _IN_ CDMEnum frontColor, const _IN_ CDMEnum backColor);
	 *
	 * \brief	Pokes a pixel in the screen to a certain color. Ignores drawn flags.
	 *			Status: Working.
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
							const _IN_ CDMLetterColor frontColor,
							const _IN_ CDMBackgroundColor backColor);

	/**********************************************************************************************//**
	 * \fn	void CDMDraw(_IN_ CDMContext* ctx);
	 *
	 * \brief	Draws the whole screen. Does a batch draw if things have been added to the context.
	 *			Status: Working.
	 *
	 * \param [in]	The context, must not be null.
	 **************************************************************************************************/

	void		CDMDraw(_IN_ CDMContext** ctx);

	/**********************************************************************************************//**
	 * \fn	int CDMGetR(_IN_ CDMColorScheme* data, const _IN_ short position);
	 *
	 * \brief	Gets the red color of a certain color inside a ColorScheme.
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
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
	 *			Status: Working.
	 *
	 * \param [in,out]	surface 	The surface to be modified, must not be null.
	 * \param [in]	  	x			The x coordinate of the pixel.
	 * \param [in]	  	y			The y coordinate of the pixel.
	 * \param [in]	  	pixelSet	The enumeration value of the data.
	 **************************************************************************************************/

	void		CDMSetPixel(_INOUT_ CDMSurface** surface,
							_IN_ short x,
							_IN_ short y,
							_IN_ CDMColorSets pixelSet);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMCompareCHARINFO(_IN_ CHAR_INFO rhs, _IN_ CHAR_INFO lhs);
	 *
	 * \brief	Compares two CHAR_INFO structures, it's mainly used inside the API for certain 
	 * 			operations. May not prove useful to the graphics programmer. 
	 *			Status: Working.
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
	 *			Status: Working.
	 *
	 * \param [in,out]	ctx  	The context, must not be null.
	 * \param [in,out]	event	An event structure, must not be null.
	 **************************************************************************************************/

	void		CDMPollEvents(_IN_ CDMContext* ctx, _INOUT_ CDMEvent* event);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMGetKeyPressed(_IN_ CDMEvent* event, const _IN_ CDMEnum key);
	 *
	 * \brief	Checks if the key selected in the parameter was pressed. This is the only function
	 *			that checks for mouse input too.
	 *			Status: Working.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 * \param [in]	  	key  	The key to be checked.
	 *
	 * \return	Returns CDMTRUE if the key is pressed, regardless of how many frames it has been
	 * 			pressed, CDMFALSE if the key is not pressed.
	 **************************************************************************************************/

	CDMBool		CDMGetKeyPressed(_IN_ CDMEvent* event, const _IN_ CDMKey key);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMGetKeyDown(_IN_ CDMEvent* event, const _IN_ CDMEnum key);
	 *
	 * \brief	Checks if the key selected in the parameter was pressed this frame.
	 *			Status: Working.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 * \param 		  	key  	The key to be checked.
	 *
	 * \return	Returns CDMTRUE if the key is pressed, but only if it was pressed in this frame,
	 * 			CDMFALSE if the key is not pressed.
	 **************************************************************************************************/

	CDMBool		CDMGetKeyDown(_IN_ CDMEvent* event, const _IN_ CDMKey key);

	/**********************************************************************************************//**
	 * \fn	CDMBool CDMGetKeyUp(_IN_ CDMEvent* event, const _IN_ CDMEnum key);
	 *
	 * \brief	Checks if the key selected in the parameter stopped being pressed this frame.
	 *			Status: Working.
	 *
	 * \param [in,out]	event	An event structure, must not be null.
	 * \param 		  	key  	The key to be checked.
	 *
	 * \return	Returns CDMTRUE if the key is not pressed, but only if it was pressed in the last
	 * 			frame, CDMFALSE if the key is pressed.
	 **************************************************************************************************/

	CDMBool		CDMGetKeyUp(_IN_ CDMEvent* event, const _IN_ CDMKey key);

	/**********************************************************************************************//**
	 * \fn	CDMCoord CDMGetMousePos(_IN_ CDMEvent* event);
	 *
	 * \brief	Gets the mouse position inside the console window.
	 *			Status: Working.
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
	 *			Status: Working.
	 *
	 * \param [in,out]	ctx  	The context, must not be null.
	 * \param [in,out]	event	An event structure to check for resize events, must not be null.
	 **************************************************************************************************/

	void		CDMKeepScreenSize(_INOUT_ CDMContext** ctx, _IN_ CDMEvent* event);

	/**********************************************************************************************//**
	 * \fn	void CDMSetErrno(const _IN_ CDMErrno code);
	 *
	 * \brief	Sets an specific errno to a value.
	 *			Status: Working.
	 *
	 * \param	code	The code to be set.
	 **************************************************************************************************/

	void		CDMSetErrno(const _IN_ CDMErrno code);

	/**********************************************************************************************//**
	 * \fn	CDMErrno CDMGetErrno();
	 *
	 * \brief	Gets the value of errno and sets it to zero.
	 *			Status: Working.
	 *
	 * \return	The value of errno.
	 **************************************************************************************************/

	CDMErrno	CDMGetErrno();

	/**********************************************************************************************//**
	 * \fn	char* CDMGetErrorMessage();
	 *
	 * \brief	Translates an error code to an error message, for a brief description.
	 *			Status: Working.
	 *
	 * \return	Will always return a string of characters.
	 **************************************************************************************************/

	char*		CDMGetErrorMessage();

	/**********************************************************************************************//**
	 * \fn	void CDMClearErrno();
	 *			Status: Working.
	 *
	 * \brief	Sets errno back to 0.
	 **************************************************************************************************/

	void		CDMClearErrno();

#ifdef __cplusplus
}
#endif
