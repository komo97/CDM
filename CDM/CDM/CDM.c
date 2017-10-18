#include "CDM.h"
#include <stdlib.h>
#include <stdio.h>

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
	ctx->backBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |				
		GENERIC_WRITE,
		FILE_SHARE_READ |			 
		FILE_SHARE_WRITE,        
		NULL,						 
		CONSOLE_TEXTMODE_BUFFER,	
		NULL);
	ctx->mainBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |				
		GENERIC_WRITE,
		FILE_SHARE_READ |			
		FILE_SHARE_WRITE,        
		NULL,						 
		CONSOLE_TEXTMODE_BUFFER,	 
		NULL);
	ctx->mainBufferActive = TRUE;
	SetConsoleActiveScreenBuffer(ctx->backBuffer);
	HWND wnd = GetConsoleWindow();
	CDMCoord coord = { 
		(SHORT)width,
		(SHORT)height };
	SMALL_RECT wndw = { 
		0, 
		0,
		(SHORT)width - 1,
		(SHORT)height - 1};
	ctx->rect = wndw;
	SetConsoleScreenBufferSize(ctx->mainBuffer, coord);
	SetConsoleScreenBufferSize(ctx->backBuffer, coord);
	MoveWindow(wnd, -8, 0, 1, 1, FALSE);
	SetConsoleWindowInfo(ctx->mainBuffer, TRUE, &wndw);
	SetConsoleWindowInfo(ctx->backBuffer, TRUE, &wndw);
	ctx->contents.printBufferCont = calloc(width * height, sizeof(CHAR_INFO));
	ctx->contents.isAlphaTile = calloc(width * height, sizeof(CDMBool));
	ctx->contents.alreadyDrawn = calloc(width * height, sizeof(CDMBool));
	memset(ctx->contents.isAlphaTile, CDMFALSE, width * height);
	memset(ctx->contents.alreadyDrawn, CDMFALSE, width * height);
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(ctx->mainBuffer, &inf);
	GetConsoleScreenBufferInfoEx(ctx->mainBuffer, &ctx->inf);
	SetConsoleActiveScreenBuffer(ctx->mainBuffer);
	ctx->InputBuffer = GetStdHandle(STD_INPUT_HANDLE);
	return ctx;
}

void CDMChangeWindowSize(_INOUT_ CDMContext** ctx,
	const _IN_ short width,
	const _IN_ short height)
{
	CDMCoord coord = { width, height };
	(*ctx)->rect.Right = width;
	(*ctx)->rect.Bottom = height;
	HWND wnd = GetConsoleWindow();
	SetConsoleScreenBufferSize((*ctx)->mainBuffer, coord);
	SetConsoleScreenBufferSize((*ctx)->backBuffer, coord);
	MoveWindow(wnd, -8, 0, 1, 1, FALSE);
	SetConsoleWindowInfo((*ctx)->mainBuffer, TRUE, &(*ctx)->rect);
	SetConsoleWindowInfo((*ctx)->backBuffer, TRUE, &(*ctx)->rect);
}

void CDMToggleFullscreen(CDMContext** _INOUT_ ctx, const _IN_ CDMBool val)
{
	if (val)
	{
		SetConsoleDisplayMode((*ctx)->backBuffer, CONSOLE_FULLSCREEN_MODE, NULL);
		SetConsoleDisplayMode((*ctx)->mainBuffer, CONSOLE_FULLSCREEN_MODE, NULL);
	}
	else
	{
		SetConsoleDisplayMode((*ctx)->backBuffer, CONSOLE_WINDOWED_MODE, NULL);
		SetConsoleDisplayMode((*ctx)->mainBuffer, CONSOLE_WINDOWED_MODE, NULL);
	}
	CDMCoord coord = GetLargestConsoleWindowSize((*ctx)->mainBuffer);
	SetConsoleScreenBufferSize((*ctx)->mainBuffer, coord);
	SetConsoleScreenBufferSize((*ctx)->backBuffer, coord);
}

void CDMSetWindowTitle(const _IN_ char* title)
{
	SetConsoleTitle(title);
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
	SetCurrentConsoleFontEx((*ctx)->backBuffer, TRUE, &currFont);
}

void CDMSetCursorVisibility(_INOUT_ CDMContext** ctx,
	const _IN_ CDMBool status)
{
	CONSOLE_CURSOR_INFO inf;
	inf.bVisible = status;
	inf.dwSize = 1;
	SetConsoleCursorInfo((*ctx)->mainBuffer, &inf);
	SetConsoleCursorInfo((*ctx)->backBuffer, &inf);
}

void CDMActivateMouseInput(_INOUT_ CDMContext** ctx)
{
	SetConsoleMode((*ctx)->InputBuffer, ENABLE_MOUSE_INPUT);
	SetConsoleMode((*ctx)->backBuffer, ENABLE_MOUSE_INPUT);
	SetConsoleMode((*ctx)->mainBuffer, ENABLE_MOUSE_INPUT);
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
	memset(srfc->bufferContents.isAlphaTile, CDMFALSE, sizeX * sizeY);
	srfc->bufferContents.alreadyDrawn = NULL;
	for (i = sizeX * sizeY; i--;)
	{
		srfc->bufferContents.printBufferCont[i].Char.AsciiChar = '\0';
	}
	return srfc;
}

CDMSurface * CDMReadImg(const _IN_ char* fileName, _OUTOPT_ CDMColorScheme* scheme)
{
	CDMSurface* srfc;
	CDMCoord coord;
	FILE* f;
	char bytecheck = 0;
	f = fopen(fileName, "rb");
	fread(&bytecheck, 1, 1, f);
	if (bytecheck != 42)
	{
		CDMSetErrno(2);
		return NULL;
	}
	fread(&coord, sizeof(CDMCoord), 1, f);
	srfc = CDMCreateSurface(0, 0, coord.X, coord.Y);
	if (scheme != NULL)
		fread(scheme, sizeof(CDMColorScheme), 1, f);
	else fseek(f, sizeof(CDMColorScheme), SEEK_CUR);
	fread(&srfc->pallete, sizeof(CDMPalette), 1, f);
	fread(srfc->data, sizeof(CDMEnum), srfc->rect.Right * srfc->rect.Bottom, f);
	fclose(f);
	free(f);
	return srfc;
}

void CDMExportSrfcToImg(const _IN_ CDMContext* ctx,
	const _IN_ CDMSurface* srfc,
	const _IN_ char* fileName,
	const _IN_ size_t nameSize)
{
	FILE*	f;
	int		i;
	char*	name = calloc(1, nameSize + 4);
	char	val = 42;
	CDMColorScheme scheme;
	for (unsigned int i = 0; i < nameSize; ++i)
		name[i] = fileName[i];
	name[nameSize] = '.';
	name[nameSize + 1] = 'c';
	name[nameSize + 2] = 'd';
	name[nameSize + 3] = 'i';

	for (i = 0; i < 16; ++i)
		scheme.colors[i] = ctx->inf.ColorTable[i];
	f = fopen(name, "wb");
	fwrite(&val, 1, 1, f);
	fwrite(&srfc->rect, sizeof(CDMRect), 1, f);
	fwrite(&scheme, sizeof(CDMColorScheme), 1, f);
	fwrite(&srfc->pallete, sizeof(CDMPalette), 1, f);
	fwrite(srfc->data, sizeof(CDMEnum), srfc->rect.Right * srfc->rect.Bottom, f);
	fclose(f);
	free(f);
	free(name);
}

CDMText * CDMTextWrapper(_IN_ char * text, const _IN_ CDMEnum color, const _IN_ CDMEnum background)
{
	CDMText* txt = malloc(sizeof(CDMText));
	if(!txt)
	{
		CDMSetErrno(4);
		return NULL;
	}
	txt->data = text;
	txt->backColor = background;
	txt->frontColor = color;
	txt->bufferContents.printBufferCont = NULL;
	txt->bufferContents.printBufferCont = calloc(strlen(text), sizeof(CHAR_INFO));
	if (!txt->bufferContents.printBufferCont)
	{
		CDMSetErrno(4);
		return NULL;
	}
	txt->bufferContents.isAlphaTile = NULL;
	txt->bufferContents.alreadyDrawn = NULL;
	txt->rect.Bottom = 1;
	txt->rect.Left = 0;
	txt->rect.Right = (SHORT)strlen(text);
	txt->rect.Top = 0;
	return txt;
}

int CDMSwapBuffer(_IN_ CDMContext* const ctx)
{
	SetConsoleActiveScreenBuffer(ctx->mainBufferActive ? ctx->backBuffer : ctx->mainBuffer);
	return ctx->mainBufferActive ^= 1;
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
	CloseHandle((*ctx)->backBuffer);
	CloseHandle((*ctx)->mainBuffer);
	free((*ctx));
	*ctx = NULL;
}

void CDMPrepareSurface(_INOUT_ CDMSurface** surface)
{
	SHORT i, j;
	for (i = (*surface)->rect.Bottom; i--;)
	{
		for (j = (*surface)->rect.Right; j--;)
		{
			switch((*surface)->data[j + (i*(*surface)->rect.Right)])
			{
			case CDMSET1:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->pallete.p1.character;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->pallete.p1.frontColor | (*surface)->pallete.p1.backColor;
				goto NotAlpha;
			case CDMSET2:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->pallete.p2.character;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->pallete.p2.frontColor | (*surface)->pallete.p2.backColor;
				goto NotAlpha;
			case CDMSET3:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->pallete.p3.character;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->pallete.p3.frontColor | (*surface)->pallete.p3.backColor;
				goto NotAlpha;
			case CDMSET4:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->pallete.p4.character;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->pallete.p4.frontColor | (*surface)->pallete.p4.backColor;
				goto NotAlpha;
			case CDMSETALPHA:
				(*surface)->bufferContents.isAlphaTile[j + (i*(*surface)->rect.Right)] = CDMTRUE;
				break;
			}
			NotAlpha:
				(*surface)->bufferContents.isAlphaTile[j + (i*(*surface)->rect.Right)] = CDMFALSE;
		}

	}
}

void CDMPrepareText(_INOUT_ CDMText** txt)
{
	SHORT i, j;
	for (i = (*txt)->rect.Bottom; i--;)
	{
		for (j = (*txt)->rect.Right; j--;)
		{
				(*txt)->bufferContents.printBufferCont[j + (i*(*txt)->rect.Right)].Char.AsciiChar =
					(*txt)->data[j + (i*(*txt)->rect.Right)];
				(*txt)->bufferContents.printBufferCont[j + (i*(*txt)->rect.Right)].Attributes =
					(*txt)->frontColor | (*txt)->backColor;
		}
	}
}

CDMText * CDMTextWrapper_s(_IN_ char * text, const _IN_ size_t textSize, const _IN_ CDMEnum color, const _IN_ CDMEnum background)
{
	CDMText* txt = malloc(sizeof(CDMText));
	if(!txt)
	{
		CDMSetErrno(4);
		return NULL;
	}
	txt->data = text;
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
	txt->bufferContents.alreadyDrawn = NULL;
	txt->rect.Bottom = 1;
	txt->rect.Left = 0;
	txt->rect.Right = (SHORT)textSize;
	txt->rect.Top = 0;
	return txt;
}

void CDMChangeText(CDMText ** txt, const _IN_ char * text)
{
	size_t strSize = strlen(text);
	char* dataCpy = (char*)realloc((*txt)->data, strSize);
	if (!dataCpy)
	{
		CDMSetErrno(4);
		return;
	}
	(*txt)->data = dataCpy;
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
	const _IN_ CDMEnum c1,
	const _IN_ CDMEnum c2,
	const _IN_ CDMEnum c3,
	const _IN_ CDMEnum c4)
{
	(*surface)->pallete.p1.frontColor = c1;
	(*surface)->pallete.p2.frontColor = c2;
	(*surface)->pallete.p3.frontColor = c3;
	(*surface)->pallete.p4.frontColor = c4;
}

void CDMSetBackgroundColor(_INOUT_ CDMSurface** surface,
	const _IN_ CDMEnum c1,
	const _IN_ CDMEnum c2,
	const _IN_ CDMEnum c3,
	const _IN_ CDMEnum c4)
{
	(*surface)->pallete.p1.backColor = c1;
	(*surface)->pallete.p2.backColor = c2;
	(*surface)->pallete.p3.backColor = c3;
	(*surface)->pallete.p4.backColor = c4;
}

void CDMSetCharacters(_INOUT_ CDMSurface** surface,
	const _IN_ CDMEnum c1,
	const _IN_ CDMEnum c2,
	const _IN_ CDMEnum c3,
	const _IN_ CDMEnum c4)
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
	SMALL_RECT	rect = surface->rect;
	WriteConsoleOutput(
		(*ctx)->mainBufferActive ? (*ctx)->backBuffer : (*ctx)->mainBuffer,
		surface->bufferContents.printBufferCont,
		pos, size, &rect);
}

void CDMAddSurfaceToContext(_INOUT_ CDMContext** ctx, _IN_ CDMSurface* surface)
{
	SHORT	i, 
			j,
			si,
			sj,
			ctxAccessor,
			srfcAccessor; 
	CDMBool pixelEqual;
	for (i = surface->rect.Left, si = 0;
		si < surface->rect.Right && i < (*ctx)->rect.Right; ++i, ++si)
	{
		for (j = surface->rect.Top, sj = 0;
			sj < surface->rect.Bottom && i < (*ctx)->rect.Bottom; ++i, ++sj)
		{
			ctxAccessor = j + (i * (*ctx)->rect.Right);
			srfcAccessor = sj + (si * surface->rect.Right);
			pixelEqual = CDMCompareCHARINFO(surface->bufferContents.printBufferCont[srfcAccessor],
				(*ctx)->contents.printBufferCont[ctxAccessor]);
			if (! pixelEqual &&
				!surface->bufferContents.isAlphaTile[srfcAccessor])
			{
				(*ctx)->contents.printBufferCont[ctxAccessor] =
					surface->bufferContents.printBufferCont[srfcAccessor];
				(*ctx)->contents.alreadyDrawn[ctxAccessor] = CDMFALSE;
			}
			else if(pixelEqual)
				(*ctx)->contents.alreadyDrawn[ctxAccessor] = CDMTRUE;
		}
	}
}

void CDMDrawText(_INOUT_ CDMContext ** ctx, _IN_ CDMText * txt)
{
	CDMCoord	pos = { txt->rect.Left,txt->rect.Top },
				size = { txt->rect.Right, txt->rect.Bottom };
	SMALL_RECT	rect = txt->rect;
	WriteConsoleOutput(
		(*ctx)->mainBufferActive ? (*ctx)->backBuffer : (*ctx)->mainBuffer,
		txt->bufferContents.printBufferCont,
		pos, size, &rect);
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
			sj < txt->rect.Bottom && i < (*ctx)->rect.Bottom; ++i, ++sj)
		{
			ctxAccessor = j + (i * (*ctx)->rect.Right);
			srfcAccessor = sj + (si * txt->rect.Right);
			if (!CDMCompareCHARINFO(txt->bufferContents.printBufferCont[srfcAccessor],
				(*ctx)->contents.printBufferCont[ctxAccessor]))
			{
				(*ctx)->contents.printBufferCont[ctxAccessor] =
					txt->bufferContents.printBufferCont[srfcAccessor];
			}

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
	SHORT	i, 
			j;
	for (i = (*ctx)->rect.Right; i--;)
	{
		for (j = (*ctx)->rect.Bottom; j--;)
		{
			if (!(*ctx)->contents.alreadyDrawn)
			{
				(*ctx)->contents.printBufferCont[j + (i * (*ctx)->rect.Right)].Attributes = 0;
				(*ctx)->contents.printBufferCont[j + (i * (*ctx)->rect.Right)].Char.AsciiChar = 0;
			}
		}
	}
}

void CDMFillScreen(_INOUT_ CDMContext ** ctx,
	const _IN_ char character,
	const _IN_ CDMEnum frontColor,
	const _IN_ CDMEnum backColor)
{
	SHORT	i,
			j;
	for (i = (*ctx)->rect.Right; i--;)
	{
		for (j = (*ctx)->rect.Bottom; j--;)
		{
			(*ctx)->contents.printBufferCont[j + (i * (*ctx)->rect.Right)].Attributes = 
				frontColor | backColor;
			(*ctx)->contents.printBufferCont[j + (i * (*ctx)->rect.Right)].Char.AsciiChar = character;
		}
	}
}

void CDMPoke(_INOUT_ CDMContext ** ctx,
	const _IN_ CDMCoord coord,
	const _IN_ char character,
	const _IN_ CDMEnum frontColor,
	const _IN_ CDMEnum backColor)
{
	SHORT accesor = coord.Y + (coord.X * (*ctx)->rect.Right);
	(*ctx)->contents.printBufferCont[accesor].Attributes =
		frontColor | backColor;
	(*ctx)->contents.printBufferCont[accesor].Char.AsciiChar = character;
}

void CDMDraw(_IN_ CDMContext* ctx)
{
	CDMCoord	size = { (ctx)->rect.Right,(ctx)->rect.Bottom },
				top = { (ctx)->rect.Left, (ctx)->rect.Top };
	CDMRect		r;
	WriteConsoleOutput(
		(ctx)->mainBufferActive ? (ctx)->backBuffer : (ctx)->mainBuffer,
		(ctx)->contents.printBufferCont,
		size, top, &r);
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
	for (i = 16; i--;)
		(*ctx)->inf.ColorTable[i] = data.colors[i];
	SetConsoleScreenBufferInfoEx((*ctx)->mainBuffer, &(*ctx)->inf);
	SetConsoleScreenBufferInfoEx((*ctx)->backBuffer, &(*ctx)->inf);
}

void CDMSetPixel(_INOUT_ CDMSurface** surface,
	_IN_ short x,
	_IN_ short y,
	_IN_ CDMEnum pixelSet)
{
	(*surface)->data[y * (x * (*surface)->rect.Right)] = pixelSet;
}

CDMBool CDMCompareCHARINFO(_IN_ CHAR_INFO rhs, _IN_ CHAR_INFO lhs)
{
	return rhs.Attributes == lhs.Attributes &&
		rhs.Char.AsciiChar == lhs.Char.AsciiChar ? CDMTRUE : CDMFALSE;
}

void CDMPollEvents(_IN_ CDMContext* ctx, _INOUT_ CDMEvent* event)
{
	GetNumberOfConsoleInputEvents(ctx->InputBuffer, &event->inputNum);
	ReadConsoleInput(ctx->InputBuffer, event->inputs, 51, &event->inputNum);
}

CDMBool CDMGetKeyPressed(_IN_ CDMEvent* event, const _IN_ CDMEnum key)
{
	int i, keyVal;
	switch (key)
	{
	case CDMA:
		keyVal = 0x41;
		break;
	case CDMB:
		keyVal = 0x42;
		break;
	case CDMC:
		keyVal = 0x43;
		break;
	case CDMD:
		keyVal = 0x44;
		break;
	case CDME:
		keyVal = 0x45;
		break;
	case CDMF:
		keyVal = 0x46;
		break;
	case CDMG:
		keyVal = 0x47;
		break;
	case CDMH:
		keyVal = 0x48;
		break;
	case CDMI:
		keyVal = 0x49;
		break;
	case CDMJ:
		keyVal = 0x4A;
		break;
	case CDMK:
		keyVal = 0x4B;
		break;
	case CDML:
		keyVal = 0x4C;
		break;
	case CDMM:
		keyVal = 0x4D;
		break;
	case CDMN:
		keyVal = 0x4E;
		break;
	case CDMO:
		keyVal = 0x4F;
		break;
	case CDMP:
		keyVal = 0x50;
		break;
	case CDMQ:
		keyVal = 0x51;
		break;
	case CDMR:
		keyVal = 0x52;
		break;
	case CDMS:
		keyVal = 0x53;
		break;
	case CDMT:
		keyVal = 0x54;
		break;
	case CDMU:
		keyVal = 0x55;
		break;
	case CDMV:
		keyVal = 0x56;
		break;
	case CDMW:
		keyVal = 0x57;
		break;
	case CDMX:
		keyVal = 0x58;
		break;
	case CDMY:
		keyVal = 0x59;
		break;
	case CDMZ:
		keyVal = 0x5A;
		break;
	case CDMLALT:
		keyVal = VK_LMENU;
		break;
	case CDMLSHIFT:
		keyVal = VK_LSHIFT;
		break;
	case CDMLCTRL:
		keyVal = VK_LCONTROL;
		break;
	case CDMRALT:
		keyVal = VK_RMENU;
		break;
	case CDMRSHIFT:
		keyVal = VK_RSHIFT;
		break;
	case CDMRCTRL:
		keyVal = VK_RCONTROL;
		break;
	case CDMESC:
		keyVal = VK_ESCAPE;
		break;
	case CDMRETURN:
		keyVal = VK_RETURN;
		break;
	case CDM1:
		keyVal = 0x31;
		break;
	case CDM2:
		keyVal = 0x32;
		break;
	case CDM3:
		keyVal = 0x33;
		break;
	case CDM4:
		keyVal = 0x34;
		break;
	case CDM5:
		keyVal = 0x35;
		break;
	case CDM6:
		keyVal = 0x36;
		break;
	case CDM7:
		keyVal = 0x37;
		break;
	case CDM8:
		keyVal = 0x38;
		break;
	case CDM9:
		keyVal = 0x39;
		break;
	case CDM0:
		keyVal = 0x30;
		break;
	case CDMCOMMA:
		keyVal = VK_OEM_COMMA;
		break;
	case CDMPERIOD:
		keyVal = VK_OEM_PERIOD;
		break;
	case CDMBACKS:
		keyVal = VK_BACK;
		break;
	case CDMLEFT:
		keyVal = VK_LEFT;
		break;
	case CDMRIGHT:
		keyVal = VK_RIGHT;
		break;
	case CDMUP:
		keyVal = VK_UP;
		break;
	case CDMDOWN:
		keyVal = VK_DOWN;
		break;
	case CDMSPACE:
		keyVal = VK_SPACE;
		break;
	case CDMRMB:
		keyVal = 0x0002;
		break;
	case CDMLMB:
		keyVal = 0x0001;
		break;
	case CDMMMB:
		keyVal = 0x0004;
		break;
	}
	for (i = 0; i < event->inputNum; ++i)
	{
		switch (event->inputs[i].EventType)
		{
		case KEY_EVENT:
			if (event->inputs[i].Event.KeyEvent.wVirtualKeyCode == keyVal &&
				event->inputs[i].Event.KeyEvent.bKeyDown)
				return event->inputPressed[key] = CDMTRUE;
			break;
		case MOUSE_EVENT:
			if (event->inputs[i].Event.MouseEvent.dwButtonState & keyVal)
				return event->inputPressed[key] = CDMTRUE;
			break;
		}
	}
	return event->inputPressed[key] = CDMFALSE;
}

CDMBool CDMGetKeyDown(_IN_ CDMEvent* event, const _IN_ CDMEnum key)
{
	int i, keyVal;
	switch (key)
	{
	case CDMA:
		keyVal = 0x41;
		break;
	case CDMB:
		keyVal = 0x42;
		break;
	case CDMC:
		keyVal = 0x43;
		break;
	case CDMD:
		keyVal = 0x44;
		break;
	case CDME:
		keyVal = 0x45;
		break;
	case CDMF:
		keyVal = 0x46;
		break;
	case CDMG:
		keyVal = 0x47;
		break;
	case CDMH:
		keyVal = 0x48;
		break;
	case CDMI:
		keyVal = 0x49;
		break;
	case CDMJ:
		keyVal = 0x4A;
		break;
	case CDMK:
		keyVal = 0x4B;
		break;
	case CDML:
		keyVal = 0x4C;
		break;
	case CDMM:
		keyVal = 0x4D;
		break;
	case CDMN:
		keyVal = 0x4E;
		break;
	case CDMO:
		keyVal = 0x4F;
		break;
	case CDMP:
		keyVal = 0x50;
		break;
	case CDMQ:
		keyVal = 0x51;
		break;
	case CDMR:
		keyVal = 0x52;
		break;
	case CDMS:
		keyVal = 0x53;
		break;
	case CDMT:
		keyVal = 0x54;
		break;
	case CDMU:
		keyVal = 0x55;
		break;
	case CDMV:
		keyVal = 0x56;
		break;
	case CDMW:
		keyVal = 0x57;
		break;
	case CDMX:
		keyVal = 0x58;
		break;
	case CDMY:
		keyVal = 0x59;
		break;
	case CDMZ:
		keyVal = 0x5A;
		break;
	case CDMLALT:
		keyVal = VK_LMENU;
		break;
	case CDMLSHIFT:
		keyVal = VK_LSHIFT;
		break;
	case CDMLCTRL:
		keyVal = VK_LCONTROL;
		break;
	case CDMRALT:
		keyVal = VK_RMENU;
		break;
	case CDMRSHIFT:
		keyVal = VK_RSHIFT;
		break;
	case CDMRCTRL:
		keyVal = VK_RCONTROL;
		break;
	case CDMESC:
		keyVal = VK_ESCAPE;
		break;
	case CDMRETURN:
		keyVal = VK_RETURN;
		break;
	case CDM1:
		keyVal = 0x31;
		break;
	case CDM2:
		keyVal = 0x32;
		break;
	case CDM3:
		keyVal = 0x33;
		break;
	case CDM4:
		keyVal = 0x34;
		break;
	case CDM5:
		keyVal = 0x35;
		break;
	case CDM6:
		keyVal = 0x36;
		break;
	case CDM7:
		keyVal = 0x37;
		break;
	case CDM8:
		keyVal = 0x38;
		break;
	case CDM9:
		keyVal = 0x39;
		break;
	case CDM0:
		keyVal = 0x30;
		break;
	case CDMCOMMA:
		keyVal = VK_OEM_COMMA;
		break;
	case CDMPERIOD:
		keyVal = VK_OEM_PERIOD;
		break;
	case CDMBACKS:
		keyVal = VK_BACK;
		break;
	case CDMLEFT:
		keyVal = VK_LEFT;
		break;
	case CDMRIGHT:
		keyVal = VK_RIGHT;
		break;
	case CDMUP:
		keyVal = VK_UP;
		break;
	case CDMDOWN:
		keyVal = VK_DOWN;
		break;
	case CDMSPACE:
		keyVal = VK_SPACE;
		break;
	case CDMRMB:
		keyVal = 0x0002;
		break;
	case CDMLMB:
		keyVal = 0x0001;
		break;
	case CDMMMB:
		keyVal = 0x0004;
		break;
	}
	for (i = 0; i < event->inputNum; ++i)
	{
		switch (event->inputs[i].EventType)
		{
		case KEY_EVENT:
			if (event->inputs[i].Event.KeyEvent.wVirtualKeyCode == keyVal &&
				event->inputs[i].Event.KeyEvent.bKeyDown && 
				!event->inputPressed[i])
				return event->inputPressed[key] = CDMTRUE;
			break;
		case MOUSE_EVENT:
			if (event->inputs[i].Event.MouseEvent.dwButtonState & keyVal &&
				!event->inputPressed[i])
				return event->inputPressed[key] = CDMTRUE;
			break;
		}
	}
	return event->inputPressed[key] = CDMFALSE;
}

CDMBool CDMGetKeyUp(_IN_ CDMEvent* event, const _IN_ CDMEnum key)
{
	int i, keyVal;
	switch (key)
	{
	case CDMA:
		keyVal = 0x41;
		break;
	case CDMB:
		keyVal = 0x42;
		break;
	case CDMC:
		keyVal = 0x43;
		break;
	case CDMD:
		keyVal = 0x44;
		break;
	case CDME:
		keyVal = 0x45;
		break;
	case CDMF:
		keyVal = 0x46;
		break;
	case CDMG:
		keyVal = 0x47;
		break;
	case CDMH:
		keyVal = 0x48;
		break;
	case CDMI:
		keyVal = 0x49;
		break;
	case CDMJ:
		keyVal = 0x4A;
		break;
	case CDMK:
		keyVal = 0x4B;
		break;
	case CDML:
		keyVal = 0x4C;
		break;
	case CDMM:
		keyVal = 0x4D;
		break;
	case CDMN:
		keyVal = 0x4E;
		break;
	case CDMO:
		keyVal = 0x4F;
		break;
	case CDMP:
		keyVal = 0x50;
		break;
	case CDMQ:
		keyVal = 0x51;
		break;
	case CDMR:
		keyVal = 0x52;
		break;
	case CDMS:
		keyVal = 0x53;
		break;
	case CDMT:
		keyVal = 0x54;
		break;
	case CDMU:
		keyVal = 0x55;
		break;
	case CDMV:
		keyVal = 0x56;
		break;
	case CDMW:
		keyVal = 0x57;
		break;
	case CDMX:
		keyVal = 0x58;
		break;
	case CDMY:
		keyVal = 0x59;
		break;
	case CDMZ:
		keyVal = 0x5A;
		break;
	case CDMLALT:
		keyVal = VK_LMENU;
		break;
	case CDMLSHIFT:
		keyVal = VK_LSHIFT;
		break;
	case CDMLCTRL:
		keyVal = VK_LCONTROL;
		break;
	case CDMRALT:
		keyVal = VK_RMENU;
		break;
	case CDMRSHIFT:
		keyVal = VK_RSHIFT;
		break;
	case CDMRCTRL:
		keyVal = VK_RCONTROL;
		break;
	case CDMESC:
		keyVal = VK_ESCAPE;
		break;
	case CDMRETURN:
		keyVal = VK_RETURN;
		break;
	case CDM1:
		keyVal = 0x31;
		break;
	case CDM2:
		keyVal = 0x32;
		break;
	case CDM3:
		keyVal = 0x33;
		break;
	case CDM4:
		keyVal = 0x34;
		break;
	case CDM5:
		keyVal = 0x35;
		break;
	case CDM6:
		keyVal = 0x36;
		break;
	case CDM7:
		keyVal = 0x37;
		break;
	case CDM8:
		keyVal = 0x38;
		break;
	case CDM9:
		keyVal = 0x39;
		break;
	case CDM0:
		keyVal = 0x30;
		break;
	case CDMCOMMA:
		keyVal = VK_OEM_COMMA;
		break;
	case CDMPERIOD:
		keyVal = VK_OEM_PERIOD;
		break;
	case CDMBACKS:
		keyVal = VK_BACK;
		break;
	case CDMLEFT:
		keyVal = VK_LEFT;
		break;
	case CDMRIGHT:
		keyVal = VK_RIGHT;
		break;
	case CDMUP:
		keyVal = VK_UP;
		break;
	case CDMDOWN:
		keyVal = VK_DOWN;
		break;
	case CDMSPACE:
		keyVal = VK_SPACE;
		break;
	case CDMRMB:
		keyVal = 0x0002;
		break;
	case CDMLMB:
		keyVal = 0x0001;
		break;
	case CDMMMB:
		keyVal = 0x0004;
		break;
	}
	for (i = 0; i < event->inputNum; ++i)
	{
		switch (event->inputs[i].EventType)
		{
		case KEY_EVENT:
			if (event->inputs[i].Event.KeyEvent.wVirtualKeyCode == keyVal &&
				!event->inputs[i].Event.KeyEvent.bKeyDown &&
				event->inputPressed[key])
			{
				event->inputPressed[key] = CDMFALSE;
				return CDMTRUE;
			}
			break;
		}
	}
	return event->inputPressed[key] = CDMFALSE;
}

CDMCoord CDMGetMousePos(_IN_ CDMEvent* event)
{
	int i;
	for (i = 0; i < event->inputNum; ++i)
	{
		switch (event->inputs[i].EventType)
		{
		case MOUSE_EVENT:
			return event->inputs[i].Event.MouseEvent.dwMousePosition;
			break;
		}
	}
	CDMCoord ret = { 0,0 };
	return ret;
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
			break;
		}
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


