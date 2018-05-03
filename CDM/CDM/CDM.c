#include "CDM.h"
#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)
static CDMErrno	cdmErrno;

CDMContext* CDMCreateContext(const _IN_ short width, const _IN_ short height)
{
	CDMClearErrno();
	CDMContext* ctx = malloc(sizeof(CDMContext));
	if (!ctx)
	{
		CDMSetErrno(4);
		return NULL;
	}
	ctx->mainBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |				
		GENERIC_WRITE,
		FILE_SHARE_READ |			
		FILE_SHARE_WRITE,        
		NULL,						 
		CONSOLE_TEXTMODE_BUFFER,	 
		NULL);
	HWND wnd = GetConsoleWindow();
	ctx->contents.printBufferCont = NULL;
	ctx->contents.isAlphaTile = NULL;
	CDMChangeWindowSize(&ctx, width, height);
	CONSOLE_SCREEN_BUFFER_INFO inf;
	memset(&ctx->inf, 0, sizeof(CONSOLE_SCREEN_BUFFER_INFOEX));
	ctx->inf.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfo(ctx->mainBuffer, &inf);
	GetConsoleScreenBufferInfoEx(ctx->mainBuffer, &ctx->inf);
	SetConsoleActiveScreenBuffer(ctx->mainBuffer);
	ctx->inputBuffer = GetStdHandle(STD_INPUT_HANDLE);
	DWORD modes;
	GetConsoleMode(ctx->inputBuffer, &modes);
	SetConsoleMode(ctx->inputBuffer, (ENABLE_WINDOW_INPUT | modes) ^ (ENABLE_INSERT_MODE | ENABLE_QUICK_EDIT_MODE));
	SetConsoleMode(ctx->mainBuffer, DISABLE_NEWLINE_AUTO_RETURN | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	memset(ctx->events.inputPressed, CDMFalse, KeysEnd * sizeof(CDMBool));
	return ctx;
}

void CDMChangeWindowSize(_INOUT_ CDMContext** ctx,
	const _IN_ short width,
	const _IN_ short height)
{
	COORD screenCoords = { (SHORT)width, (SHORT)height };
	SMALL_RECT rect = { 0, 0, 10, 10 };
	CONSOLE_SCREEN_BUFFER_INFO infof; 
	SetConsoleWindowInfo((*ctx)->mainBuffer, TRUE, &rect);  
	COORD minConsoleSize = { (SHORT)GetSystemMetrics(SM_CXMIN), (SHORT)GetSystemMetrics(SM_CYMIN) };
	if (minConsoleSize.X > screenCoords.X)
		screenCoords.X = (*ctx)->rect.Right = minConsoleSize.X;
	if (minConsoleSize.Y > screenCoords.Y)
		screenCoords.Y = (*ctx)->rect.Bottom = minConsoleSize.Y; 
	SetConsoleScreenBufferSize((*ctx)->mainBuffer, screenCoords);
	GetConsoleScreenBufferInfo((*ctx)->mainBuffer, &infof);
	rect.Right = infof.dwMaximumWindowSize.X - 1;
	rect.Bottom = infof.dwMaximumWindowSize.Y - 1;
	SetConsoleWindowInfo((*ctx)->mainBuffer, TRUE, &rect);
	rect.Right = screenCoords.X;
	rect.Bottom = screenCoords.Y;
	(*ctx)->rect = rect;
	if ((*ctx)->contents.printBufferCont)
		free((*ctx)->contents.printBufferCont);
	if ((*ctx)->contents.isAlphaTile)
		free((*ctx)->contents.isAlphaTile);
	(*ctx)->contents.printBufferCont = calloc(rect.Right * rect.Bottom, sizeof(CHAR_INFO));
	(*ctx)->contents.isAlphaTile = calloc(rect.Right * rect.Bottom, sizeof(CDMBool));
	(*ctx)->lastFrameContents.printBufferCont = calloc(rect.Right * rect.Bottom, sizeof(CHAR_INFO));
	(*ctx)->lastFrameContents.isAlphaTile = calloc(rect.Right * rect.Bottom, sizeof(CDMBool));
	FlushConsoleInputBuffer((*ctx)->inputBuffer);
}

void CDMToggleFullscreen(CDMContext** _INOUT_ ctx, const _IN_ CDMBool val)
{
	if ((*ctx)->inf.bFullscreenSupported)
	{
		if (val)
		{
			SetConsoleDisplayMode((*ctx)->mainBuffer, CONSOLE_FULLSCREEN_MODE, NULL);
		}
		else
		{
			SetConsoleDisplayMode((*ctx)->mainBuffer, CONSOLE_WINDOWED_MODE, NULL);
		}
		CDMCoord coord = GetLargestConsoleWindowSize((*ctx)->mainBuffer);
		(*ctx)->rect.Top = 0;
		(*ctx)->rect.Left = 0;
		(*ctx)->rect.Right = coord.X;
		(*ctx)->rect.Bottom = coord.Y;
		free((*ctx)->contents.printBufferCont);
		free((*ctx)->contents.isAlphaTile);
		(*ctx)->contents.printBufferCont =
			calloc((*ctx)->rect.Right * (*ctx)->rect.Bottom, sizeof(CHAR_INFO));
		(*ctx)->contents.isAlphaTile =
			calloc((*ctx)->rect.Right * (*ctx)->rect.Bottom, sizeof(CDMBool));
		SetConsoleScreenBufferSize((*ctx)->mainBuffer, coord);
	}
}

void CDMSetWindowTitle(const _IN_ wchar_t* title)
{
	SetConsoleTitleW(title);
}

void CDMSetFontAndSize(_INOUT_ CDMContext** ctx,
	const _IN_ wchar_t* fontName,
	const _IN_ short width,
	const _IN_ short height)
{
	CONSOLE_FONT_INFOEX currFont;
	currFont.cbSize = sizeof currFont;
	currFont.nFont = 0;
	currFont.dwFontSize.X = width;
	currFont.dwFontSize.Y = height;
	currFont.FontFamily = FF_DONTCARE;
	currFont.FontWeight = FW_NORMAL;
	wcscpy_s(currFont.FaceName, 32, fontName);
	SetCurrentConsoleFontEx((*ctx)->mainBuffer, TRUE, &currFont);
}

void CDMSetCursorVisibility(_INOUT_ CDMContext** ctx,
	const _IN_ CDMBool status)
{
	CONSOLE_CURSOR_INFO inf;
	inf.bVisible = status;
	inf.dwSize = 1;
	SetConsoleCursorInfo((*ctx)->mainBuffer, &inf);
}

void CDMActivateMouseInput(_INOUT_ CDMContext** ctx)
{
	DWORD modes;
	GetConsoleMode((*ctx)->inputBuffer, &modes);
	SetConsoleMode((*ctx)->inputBuffer, (modes | ENABLE_MOUSE_INPUT));
}

CDMSurface* CDMCreateSurface(const _IN_ short posX,
	const _IN_ short posY,
	const _IN_ short sizeX,
	const _IN_ short sizeY)
{
	CDMSurface* srfc = malloc(sizeof(CDMSurface));
	if (!srfc)
	{
		CDMSetErrno(4);
		return NULL;
	}
	int i;
	srfc->rect = ((CDMRect) { posX, posY, sizeX, sizeY });
	srfc->data = calloc(sizeX*sizeY, sizeof(unsigned char));
	srfc->bufferContents.printBufferCont = calloc(sizeX * sizeY, sizeof(CHAR_INFO));
	srfc->bufferContents.isAlphaTile = calloc(sizeX * sizeY, sizeof(CDMBool));
	memset(srfc->bufferContents.isAlphaTile, CDMFalse, sizeX * sizeY);
	for (i = sizeX * sizeY; i--;)
	{
		srfc->bufferContents.printBufferCont[i].Char.AsciiChar = '\0';
	}
	return srfc;
}

CDMSurface * CDMReadImg(const _IN_ char* fileName, _OUTOPT_ CDMColorScheme* scheme)
{
	CDMSurface* srfc;
	CDMRect coord;
	FILE* f;
	char bytecheck = 0;
	f = fopen(fileName, "rb");
	fread(&bytecheck, 1, 1, f);
	if (bytecheck != 42)
	{
		CDMSetErrno(2);
		return NULL;
	}
	fread(&coord, sizeof(CDMRect), 1, f);
	srfc = CDMCreateSurface(coord.Left, coord.Top, coord.Right, coord.Bottom);
	if (scheme != NULL)
		fread(scheme, sizeof(CDMColorScheme), 1, f);
	else fseek(f, sizeof(CDMColorScheme), SEEK_CUR);
	fread(&srfc->pallete, sizeof(CDMPalette), 1, f);
	fread(srfc->data, sizeof(CDMEnum), srfc->rect.Right * srfc->rect.Bottom, f);
	fclose(f);
	return srfc;
}

void CDMExportSrfcToImg(const _IN_ CDMContext* ctx,
	const _IN_ CDMSurface* srfc,
	const _IN_ char* fileName,
	const _IN_ size_t nameSize)
{
	FILE*	f;
	int		i;
	char*	name = calloc(1, nameSize + 5);
	char	val = 42;
	CDMColorScheme scheme;
	for (unsigned int i = 0; i < nameSize; ++i)
		name[i] = fileName[i];
	name[nameSize] = '.';
	name[nameSize + 1] = 'c';
	name[nameSize + 2] = 'd';
	name[nameSize + 3] = 'i';
	name[nameSize + 4] = '\0';
	GetConsoleScreenBufferInfoEx(ctx->mainBuffer, &ctx->inf);
	for (i = 0; i < 16; ++i)
		scheme.colors[i] = ctx->inf.ColorTable[i];
	f = fopen(name, "wb");
	fwrite(&val, 1, 1, f);
	fwrite(&srfc->rect, sizeof(CDMRect), 1, f);
	fwrite(&scheme, sizeof(CDMColorScheme), 1, f);
	fwrite(&srfc->pallete, sizeof(CDMPalette), 1, f);
	fwrite(srfc->data, sizeof(CDMEnum), srfc->rect.Right * srfc->rect.Bottom, f);
	fclose(f);
	free(name);
}

CDMText * CDMTextWrapper(_IN_ char * text, const _IN_ CDMLetterColor color, const _IN_ CDMBackgroundColor background)
{
	CDMText* txt = malloc(sizeof(CDMText));
	if (!txt)
	{
		CDMSetErrno(4);
		return NULL;
	}
	txt->rect.Bottom = 1;
	txt->rect.Left = 0;
	txt->rect.Right = (SHORT)strlen(text);
	txt->rect.Top = 0;
	(txt)->data = malloc(txt->rect.Right + 1);
	strcpy((txt)->data, text);
	txt->backColor = background;
	txt->frontColor = color;
	txt->bufferContents.printBufferCont = NULL;
	txt->bufferContents.printBufferCont = calloc(strlen(text), sizeof(CHAR_INFO));
	int i;
	for (i = txt->rect.Right; i--;)
	{
		txt->bufferContents.printBufferCont[i].Char.AsciiChar = '\0';
	}
	if (!txt->bufferContents.printBufferCont)
	{
		CDMSetErrno(4);
		return NULL;
	}
	txt->bufferContents.isAlphaTile = NULL;
	return txt;
}

void CDMFreeSurface(_INOUT_ CDMSurface** srfc)
{
	free((*srfc)->data);
	free((*srfc)->bufferContents.printBufferCont);
	free((*srfc)->bufferContents.isAlphaTile);
	free((*srfc));
	*srfc = NULL;
}

void CDMFreeText(_INOUT_ CDMText** txt)
{
	free((*txt)->data);
	free((*txt)->bufferContents.printBufferCont);
	free((*txt));
	*txt = NULL;
}

void CDMFreeContext(_INOUT_ CDMContext** ctx)
{
	CloseHandle((*ctx)->mainBuffer);
	free((*ctx)->contents.printBufferCont);
	free((*ctx)->contents.isAlphaTile);
	free((*ctx)->lastFrameContents.isAlphaTile);
	free((*ctx)->lastFrameContents.printBufferCont);
	free((*ctx));
	*ctx = NULL;
}

void CDMPrepareSurface(_INOUT_ CDMSurface** surface)
{
	SHORT i, j;
	int accessor;
	for (i = (*surface)->rect.Bottom; i--;)
	{
		for (j = (*surface)->rect.Right; j--;)
		{
			accessor = j + (i*(*surface)->rect.Right);
			switch((*surface)->data[accessor])
			{
			case Set1:
				(*surface)->bufferContents.printBufferCont[accessor].Char.AsciiChar =
					(*surface)->pallete.p1.character;
				(*surface)->bufferContents.printBufferCont[accessor].Attributes =
					(*surface)->pallete.p1.frontColor | (*surface)->pallete.p1.backColor;
				goto NotAlpha;
			case Set2:
				(*surface)->bufferContents.printBufferCont[accessor].Char.AsciiChar =
					(*surface)->pallete.p2.character;
				(*surface)->bufferContents.printBufferCont[accessor].Attributes =
					(*surface)->pallete.p2.frontColor | (*surface)->pallete.p2.backColor;
				goto NotAlpha;
			case Set3:
				(*surface)->bufferContents.printBufferCont[accessor].Char.AsciiChar =
					(*surface)->pallete.p3.character;
				(*surface)->bufferContents.printBufferCont[accessor].Attributes =
					(*surface)->pallete.p3.frontColor | (*surface)->pallete.p3.backColor;
				goto NotAlpha;
			case Set4:
				(*surface)->bufferContents.printBufferCont[accessor].Char.AsciiChar =
					(*surface)->pallete.p4.character;
				(*surface)->bufferContents.printBufferCont[accessor].Attributes =
					(*surface)->pallete.p4.frontColor | (*surface)->pallete.p4.backColor;
				goto NotAlpha;
			case SetAlpha:
				(*surface)->bufferContents.isAlphaTile[accessor] = CDMTrue;
				break;
			}
			NotAlpha:
				(*surface)->bufferContents.isAlphaTile[accessor] = CDMFalse;
		}

	}
}

void CDMPrepareText(_INOUT_ CDMText** txt)
{
	SHORT i, j, k = 0;
	int accessor; 
	for (i = (*txt)->rect.Bottom; i--;)
	{
		for (j = (*txt)->rect.Right; j--;)
		{
			accessor = j + (i*(*txt)->rect.Right);
			(*txt)->bufferContents.printBufferCont[accessor].Char.AsciiChar =
				(*txt)->data[accessor];
			(*txt)->bufferContents.printBufferCont[accessor].Attributes =
				(*txt)->frontColor | (*txt)->backColor;
		}
	}
}

CDMText * CDMTextWrapper_s(_IN_ char * text, const _IN_ size_t textSize,
	const _IN_ CDMLetterColor color, const _IN_ CDMBackgroundColor background)
{
	CDMText* txt = malloc(sizeof(CDMText));
	if (!txt)
	{
		CDMSetErrno(4);
		return NULL;
	}
	(txt)->data = malloc(textSize + 1);
	strcpy((txt)->data, text);
	txt->backColor = background;
	txt->frontColor = color;
	txt->bufferContents.printBufferCont = NULL;
	txt->bufferContents.printBufferCont = calloc(textSize, sizeof(CHAR_INFO));
	if (!txt->bufferContents.printBufferCont)
	{
		CDMSetErrno(4);
		return NULL;
	}
	txt->bufferContents.isAlphaTile = NULL;
	txt->rect.Bottom = 1;
	txt->rect.Left = 0;
	txt->rect.Right = (SHORT)textSize;
	txt->rect.Top = 0;
	int i;
	for (i = txt->rect.Right; i--;)
	{
		txt->bufferContents.printBufferCont[i].Char.AsciiChar = '\0';
	}
	return txt;
}

void CDMChangeText(CDMText ** txt, const _IN_ char * text)
{
	size_t strSize = strlen(text);
	free((*txt)->data);
	(*txt)->data = malloc(strSize + 1);
	strcpy((*txt)->data, text);
	(*txt)->rect.Right = (SHORT)strSize;
	CHAR_INFO* cinf = (CHAR_INFO*)realloc((*txt)->bufferContents.printBufferCont,
		sizeof(CHAR_INFO)* strSize);
	if (!cinf)
	{
		CDMSetErrno(4);
		return;
	}
	(*txt)->bufferContents.printBufferCont = cinf;
}

void CDMSetForegroundColor(_INOUT_ CDMSurface** surface,
	const _IN_ CDMLetterColor c1,
	const _IN_ CDMLetterColor c2,
	const _IN_ CDMLetterColor c3,
	const _IN_ CDMLetterColor c4)
{
	(*surface)->pallete.p1.frontColor = c1;
	(*surface)->pallete.p2.frontColor = c2;
	(*surface)->pallete.p3.frontColor = c3;
	(*surface)->pallete.p4.frontColor = c4;
}

void CDMSetBackgroundColor(_INOUT_ CDMSurface** surface,
	const _IN_ CDMBackgroundColor c1,
	const _IN_ CDMBackgroundColor c2,
	const _IN_ CDMBackgroundColor c3,
	const _IN_ CDMBackgroundColor c4)
{
	(*surface)->pallete.p1.backColor = c1;
	(*surface)->pallete.p2.backColor = c2;
	(*surface)->pallete.p3.backColor = c3;
	(*surface)->pallete.p4.backColor = c4;
}

void CDMSetCharacters(_INOUT_ CDMSurface** surface,
	const _IN_ unsigned char c1,
	const _IN_ unsigned char c2,
	const _IN_ unsigned char c3,
	const _IN_ unsigned char c4)
{
	(*surface)->pallete.p1.character = c1;
	(*surface)->pallete.p2.character = c2;
	(*surface)->pallete.p3.character = c3;
	(*surface)->pallete.p4.character = c4;
}

void CDMDrawSurface(_INOUT_ CDMContext ** ctx, _IN_ CDMSurface * surface)
{
	CDMCoord	pos = { surface->rect.Left,surface->rect.Top },
				size = { surface->rect.Right, surface->rect.Bottom };
	SMALL_RECT	rect = { pos.X, pos.Y, (*ctx)->rect.Right, (*ctx)->rect.Bottom };
	WriteConsoleOutputA(
		(*ctx)->mainBuffer,
		surface->bufferContents.printBufferCont,
		size, pos, &rect);
}

void CDMAddSurfaceToContext(_INOUT_ CDMContext** ctx, _IN_ CDMSurface* surface)
{
	SHORT	i, 
			j,
			si,
			sj,
			ctxAccessor,
			srfcAccessor; 
	for (i = surface->rect.Left, si = 0;
		si < surface->rect.Right && i < (*ctx)->rect.Right; ++i, ++si)
	{
		for (j = surface->rect.Top, sj = 0;
			sj < surface->rect.Bottom && j < (*ctx)->rect.Bottom; ++j, ++sj)
		{
			ctxAccessor = i + (j * (*ctx)->rect.Right);
			srfcAccessor = si + (sj * surface->rect.Right);
			(*ctx)->contents.printBufferCont[ctxAccessor] =
				surface->bufferContents.printBufferCont[srfcAccessor];
		}
	}
}

void CDMDrawText(_INOUT_ CDMContext ** ctx, _IN_ CDMText * txt)
{
	CDMCoord	pos = { txt->rect.Left,txt->rect.Top },
				size = { txt->rect.Right, txt->rect.Bottom };
	SMALL_RECT	rect = { pos.X, pos.Y, (*ctx)->rect.Right, (*ctx)->rect.Bottom };
	WriteConsoleOutputA(
		(*ctx)->mainBuffer,
		txt->bufferContents.printBufferCont,
		size, pos, &rect);
}

void CDMAddTextToContext(_INOUT_ CDMContext** ctx, _IN_ CDMText* txt)
{
	SHORT	i, 
			j, 
			si, 
			sj, 
			ctxAccessor, 
			srfcAccessor;
	for (i = txt->rect.Left, si = 0;
		si < txt->rect.Right && i < (*ctx)->rect.Right; ++i, ++si)
	{
		for (j = txt->rect.Top, sj = 0;
			sj < txt->rect.Bottom && j < (*ctx)->rect.Bottom; ++j, ++sj)
		{
			ctxAccessor = i + (j * (*ctx)->rect.Right);
			srfcAccessor = si + (sj * txt->rect.Right);
			(*ctx)->contents.printBufferCont[ctxAccessor] =
				txt->bufferContents.printBufferCont[srfcAccessor];

		}
	}
}

void CDMSetColorRGB(_INOUT_ CDMColorScheme* data,
	_IN_ short position,
	_IN_ short r,
	_IN_ short g,
	_IN_ short b)
{
	data->colors[position % 16] = RGB(r % 256, g % 256, b % 256);
}

void CDMSetColorBin(_INOUT_ CDMColorScheme* data,
	_IN_ short position,
	const _IN_ DWORD color)
{
	data->colors[position % 16] = color;
}

void CDMClearScreen(_INOUT_ CDMContext ** ctx)
{
	memset((*ctx)->contents.printBufferCont, 0, sizeof(CHAR_INFO) * (*ctx)->rect.Right * (*ctx)->rect.Bottom);
}

void CDMFillScreen(_INOUT_ CDMContext ** ctx,
	const _IN_ char character,
	const _IN_ CDMLetterColor frontColor,
	const _IN_ CDMBackgroundColor backColor)
{
	SHORT	i,
			j;
	for (i = (*ctx)->rect.Right; i--;)
	{
		for (j = (*ctx)->rect.Bottom; j--;)
		{
			(*ctx)->contents.printBufferCont[i + (j * (*ctx)->rect.Right)].Attributes = 
				frontColor | backColor;
			(*ctx)->contents.printBufferCont[i + (j * (*ctx)->rect.Right)].Char.AsciiChar = character;
		}
	}
}

void CDMPoke(_INOUT_ CDMContext ** ctx,
	const _IN_ CDMCoord coord,
	const _IN_ char character,
	const _IN_ CDMLetterColor frontColor,
	const _IN_ CDMBackgroundColor backColor)
{
	if (coord.X < 0 || coord.X >= (*ctx)->rect.Right || coord.Y < 0 || coord.Y >= (*ctx)->rect.Bottom)
		return;
	int accesor = coord.X + (coord.Y * (*ctx)->rect.Right);
	(*ctx)->contents.printBufferCont[accesor].Attributes =
		frontColor | backColor;
	(*ctx)->contents.printBufferCont[accesor].Char.AsciiChar = character;
}

void CDMDraw(_IN_ CDMContext** ctx)
{
#ifndef PIXELBYPIXEL


	CDMCoord	pos = { 0,0 },
		size = { (*ctx)->rect.Right, (*ctx)->rect.Bottom };
	SMALL_RECT	rect = { pos.X, pos.Y, (*ctx)->rect.Right, (*ctx)->rect.Bottom };
	WriteConsoleOutputA(
		(*ctx)->mainBuffer,
		(*ctx)->contents.printBufferCont,
		size, pos, &rect);
#else
	int i, j, accessor;
	DWORD extract;
	COORD pos;
	for (i = 0; i < (*ctx)->rect.Bottom; ++i)
	{
		for (j = 0; j < (*ctx)->rect.Right; ++j)
		{
			pos.X = j;
			pos.Y = i;
			accessor = j + (i * (*ctx)->rect.Right);
			if (!CDMCompareCHARINFO((*ctx)->contents.printBufferCont[accessor], (*ctx)->lastFrameContents.printBufferCont[accessor]))
			{
				SetConsoleCursorPosition((*ctx)->mainBuffer, pos);
				SetConsoleTextAttribute((*ctx)->mainBuffer, (*ctx)->contents.printBufferCont[accessor].Attributes);
				WriteConsoleA((*ctx)->mainBuffer, &(*ctx)->contents.printBufferCont[accessor].Char.AsciiChar, 1, &extract, NULL);
			}
		}
	}
	memcpy((*ctx)->lastFrameContents.printBufferCont, (*ctx)->contents.printBufferCont, sizeof(CHAR_INFO) * (*ctx)->rect.Right * (*ctx)->rect.Bottom);
	pos.X = pos.Y = 0;
	SetConsoleCursorPosition((*ctx)->mainBuffer, pos);
#endif // !PIXELBYPIXEL
}

int CDMGetR(_IN_ CDMColorScheme* data, const _IN_ short position)
{
	return GetRValue(data->colors[position % 16]);
}

int CDMGetG(_IN_ CDMColorScheme* data, const _IN_ short position)
{
	return GetGValue(data->colors[position % 16]);
}

int CDMGetB(_IN_ CDMColorScheme* data, const _IN_ short position)
{
	return GetBValue(data->colors[position % 16]);
}

void CDMSetActiveScheme(_IN_ CDMColorScheme data, _INOUT_ CDMContext** ctx)
{
	int i;
	GetConsoleScreenBufferInfoEx((*ctx)->mainBuffer, &(*ctx)->inf);
	for (i = 16; i--;)
		(*ctx)->inf.ColorTable[i] = data.colors[i];
	SetConsoleScreenBufferInfoEx((*ctx)->mainBuffer, &(*ctx)->inf);
}

void CDMSetPixel(_INOUT_ CDMSurface** surface,
	_IN_ short x,
	_IN_ short y,
	_IN_ CDMColorSets pixelSet)
{
	(*surface)->data[x + (y * (*surface)->rect.Right)] = pixelSet;
}

CDMBool CDMCompareCHARINFO(_IN_ CHAR_INFO rhs, _IN_ CHAR_INFO lhs)
{
	return rhs.Attributes == lhs.Attributes &&
		rhs.Char.AsciiChar == lhs.Char.AsciiChar ? CDMTrue : CDMFalse;
}

void CDMPollEvents(_IN_ CDMContext* ctx, _INOUT_ CDMEvent* event)
{
	GetNumberOfConsoleInputEvents(ctx->inputBuffer, &event->inputNum);
	if(event->inputNum)
		ReadConsoleInput(ctx->inputBuffer, event->inputs, 51, &event->inputNum);
}

CDMBool CDMGetKeyPressed(_IN_ CDMEvent* event, const _IN_ CDMKey key)
{
	int i;
	for (i = 0; i < event->inputNum; ++i)
	{
		if ((event->inputs[i].EventType == KEY_EVENT &&
			event->inputs[i].Event.KeyEvent.wVirtualKeyCode == key &&
			event->inputs[i].Event.KeyEvent.bKeyDown) || 
			(event->inputs[i].EventType == MOUSE_EVENT && 
			((key == mbright && 
			event->inputs[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) ||
			(key == mbleft && 
			event->inputs[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED))))
		{
			event->inputPressed[key] = CDMTrue;
			return CDMTrue;
		}
	}
	event->inputPressed[key] = CDMFalse;
	return CDMFalse;
}

CDMBool CDMGetKeyDown(_IN_ CDMEvent* event, const _IN_ CDMKey key)
{
	int i;
	for (i = 0; i < event->inputNum; ++i)
	{
		if (event->inputs[i].EventType == KEY_EVENT &&
			event->inputs[i].Event.KeyEvent.wVirtualKeyCode == key &&
			event->inputs[i].Event.KeyEvent.bKeyDown &&
			!event->inputPressed[key])
		{
			event->inputPressed[key] = CDMTrue;
			return CDMTrue;
		}
		else if (event->inputs[i].EventType == KEY_EVENT &&
			event->inputs[i].Event.KeyEvent.wVirtualKeyCode == key &&
			!event->inputs[i].Event.KeyEvent.bKeyDown &&
			event->inputPressed[key])
		{
			event->inputPressed[key] = CDMFalse;
			return CDMFalse;
		}
	}
	return CDMFalse;
}

CDMBool CDMGetKeyUp(_IN_ CDMEvent* event, const _IN_ CDMKey key)
{
	int i;
	for (i = 0; i < event->inputNum; ++i)
	{
		if (event->inputs[i].EventType == KEY_EVENT &&
			event->inputs[i].Event.KeyEvent.wVirtualKeyCode == key &&
			!event->inputs[i].Event.KeyEvent.bKeyDown)
		{
			event->inputPressed[key] = CDMFalse;
			return CDMTrue;
		}
		if (event->inputs[i].EventType == KEY_EVENT &&
			event->inputs[i].Event.KeyEvent.wVirtualKeyCode == key &&
			event->inputs[i].Event.KeyEvent.bKeyDown)
		{
			event->inputPressed[key] = CDMTrue;
			return CDMFalse;
		}
	}
	return CDMFalse;
}

CDMCoord CDMGetMousePos(_IN_ CDMEvent * event)
{
	COORD pos = { -1,-1 };
	int i;
	for (i = 0; i < event->inputNum; ++i)
	{
		if (event->inputs[i].EventType == MOUSE_EVENT)
		{
			pos = event->inputs[i].Event.MouseEvent.dwMousePosition;
			break;
		}
	}
	return pos;
}

void CDMKeepScreenSize(_INOUT_ CDMContext** ctx, _IN_ CDMEvent* event)
{
	int i;
	for (i = 0; i < event->inputNum; ++i)
	{
		switch (event->inputs[i].EventType)
		{
		case WINDOW_BUFFER_SIZE_EVENT:
			CDMChangeWindowSize(ctx, (*ctx)->rect.Right, (*ctx)->rect.Bottom);
			return;
		}
	}
}

void CDMPrintf(_INOUT_ CDMContext** ctx, const _IN_ int startingLetter, _IN_ CDMRect initialPos,
	const _IN_ CDMLetterColor frontColor,
	const _IN_ CDMBackgroundColor backColor, const _IN_ char* txt, ...)
{
	va_list args;
	va_start(args, txt);
	char token;
	int argInt, i, iposX = initialPos.Left;
	unsigned int arguint;
	float argFloat;
	char trans[32], argChar;
	char* argString;
	CDMCoord inPos = { initialPos.Left, initialPos.Right };
	for (i = 0; i <= startingLetter && *txt != '\0'; ++i)
		++txt;
	while (*txt != '\0')
	{
		switch (*txt)
		{
		case '%':
			token = *(++txt);
			switch (token)
			{
			case '%':
				CDMPoke(ctx, inPos, '%', frontColor, backColor);
				++inPos.X;
				break;
			case 'U':
			case 'u':
				arguint = va_arg(args, unsigned int);
				sprintf(trans, "%u", arguint);
				for (i = 0; trans[i] != '\0'; ++i)
				{
					CDMPoke(ctx, inPos, trans[i], frontColor, backColor);
					if (inPos.X + 1 >= initialPos.Right)
					{
						++inPos.Y;
						inPos.X = iposX;
					}
					else
						++inPos.X;
				}
				break;
			case 'O':
			case 'o':
				argInt = va_arg(args, int);
				sprintf(trans, "%o", argInt);
				for (i = 0; trans[i] != '\0'; ++i)
				{
					CDMPoke(ctx, inPos, trans[i], frontColor, backColor);
					if (inPos.X + 1 >= initialPos.Right)
					{
						++inPos.Y;
						inPos.X = iposX;
					}
					else
						++inPos.X;
				}
				break;
			case 'C':
			case 'c':
				argChar = va_arg(args, char);
				CDMPoke(ctx, inPos, argChar, frontColor, backColor);
				++inPos.X;
				break;
			case 'D':
			case 'I':
			case 'd':
			case 'i':
				argInt = va_arg(args, int);
				sprintf(trans, "%d", argInt);
				for (i = 0; trans[i] != '\0'; ++i)
				{
					CDMPoke(ctx, inPos, trans[i], frontColor, backColor);
					if (inPos.X + 1 >= initialPos.Right)
					{
						++inPos.Y;
						inPos.X = iposX;
					}
					else
						++inPos.X;
				}
				break;
			case 'G':
			case 'F':
			case 'g':
			case 'f':
				argFloat = va_arg(args, float);
				sprintf(trans, "%g", argFloat);
				for (i = 0; trans[i] != '\0'; ++i)
				{
					CDMPoke(ctx, inPos, trans[i], frontColor, backColor);
					if (inPos.X + 1 >= initialPos.Right)
					{
						++inPos.Y;
						inPos.X = iposX;
					}
					else
						++inPos.X;
				}
				break;
			case 's':
			case 'S':
				argString = va_arg(args, char*);
				while(*argString != '\0')
				{
					CDMPoke(ctx, inPos, *argString, frontColor, backColor);
					if (inPos.X + 1 >= initialPos.Right)
					{
						++inPos.Y;
						inPos.X = iposX;
					}
					else
						++inPos.X;
					++argString;
				}
				break;
			case 'X':
			case 'x':
				argInt = va_arg(args, int);
				sprintf(trans, "%x", argInt);
				for (i = 0; trans[i] != '\0'; ++i)
				{
					CDMPoke(ctx, inPos, trans[i], frontColor, backColor);
					if (inPos.X + 1 >= initialPos.Right)
					{
						++inPos.Y;
						inPos.X = iposX;
					}
					else
						++inPos.X;
				}
				break;
			}
			break;
		case '\n':
			++inPos.Y;
			if (inPos.Y >= initialPos.Bottom)
				inPos.Y = initialPos.Top;
			inPos.X = iposX;
			break;
		default:
			CDMPoke(ctx, inPos, *txt, frontColor, backColor);
			++inPos.X;
			break;
		}
		++txt;
	}
}

void CDMSetErrno(const _IN_ CDMErrno code)
{
	cdmErrno = code;
}

CDMErrno CDMGetErrno()
{
	CDMErrno cpy = cdmErrno;
	cdmErrno = 0;
	return cpy;
}

char * CDMGetErrorMessage()
{
	switch(cdmErrno)
	{
	case 0:
		return "No Error.\0";
	case 1:
		return "Failed to load image.\0";
	case 2:
		return "File is not a CDM compatible image.\0";
	case 4:
		return "Memory was unable to be allocated.\0";
	default:
		return "Unknown error.\0";
	}
}

void CDMClearErrno()
{
	cdmErrno = 0;
}


