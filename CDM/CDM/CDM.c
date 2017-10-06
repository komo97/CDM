#include "CDM.h"

CDMContext* CDMCreateContext(const short width, const short height)
{
	CDMContext* ctx = malloc(sizeof(CDMContext));
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
	COORD coord = { 
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

void CDMChangeWindowSize(CDMContext ** ctx, const short width, const short height)
{
	COORD coord = { width, height };
	(*ctx)->rect.Right = width;
	(*ctx)->rect.Bottom = height;
	HWND wnd = GetConsoleWindow();
	SetConsoleScreenBufferSize((*ctx)->mainBuffer, coord);
	SetConsoleScreenBufferSize((*ctx)->backBuffer, coord);
	MoveWindow(wnd, -8, 0, 1, 1, FALSE);
	SetConsoleWindowInfo((*ctx)->mainBuffer, TRUE, &(*ctx)->rect);
	SetConsoleWindowInfo((*ctx)->backBuffer, TRUE, &(*ctx)->rect);
}

void CDMSetWindowTitle(const char * title)
{
	SetConsoleTitle(title);
}

void CDMSetFontAndSize(CDMContext ** ctx, const wchar_t * fontName, const short width, const short height)
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

void CDMSetCursorVisibility(CDMContext ** ctx, const CDMBool status)
{
	CONSOLE_CURSOR_INFO inf;
	inf.bVisible = status;
	inf.dwSize = 1;
	SetConsoleCursorInfo((*ctx)->mainBuffer, &inf);
	SetConsoleCursorInfo((*ctx)->backBuffer, &inf);
}

void CDMActivateMouseInput(CDMContext ** ctx)
{
	SetConsoleMode((*ctx)->InputBuffer, ENABLE_MOUSE_INPUT);
	SetConsoleMode((*ctx)->backBuffer, ENABLE_MOUSE_INPUT);
	SetConsoleMode((*ctx)->mainBuffer, ENABLE_MOUSE_INPUT);
}

CDMSurface* CMDCreateSurface(const short posX, 
	const short posY, 
	const short sizeX, 
	const short sizeY)
{
	CDMSurface* srfc = malloc(sizeof(CDMSurface));
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

int CDMSwapBuffer(CDMContext * const ctx)
{
	SetConsoleActiveScreenBuffer(ctx->mainBufferActive ? ctx->backBuffer : ctx->mainBuffer);
	return ctx->mainBufferActive ^= 1;
}

void CDMFreeSurface(CDMSurface ** srfc)
{
	free((*srfc)->data);
	free((*srfc));
	free((*srfc)->bufferContents.printBufferCont);
	free((*srfc)->bufferContents.isAlphaTile);
}

void CDMFreeText(CDMText ** txt)
{
	free((*txt)->data);
	free((*txt)->bufferContents.printBufferCont);
	free((*txt));
}

void CDMFreeContext(CDMContext ** ctx)
{
	CloseHandle((*ctx)->backBuffer);
	CloseHandle((*ctx)->mainBuffer);
	free((*ctx));
}

void CDMPrepareSurface(CDMSurface ** surface)
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

void CDMPrepareText(CDMText ** txt)
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

CDMText * CDMTextWrapper(char * text, 
	const size_t textSize, 
	const CDMEnum color, 
	const CDMEnum background)
{
	CDMText* txt = malloc(sizeof(CDMText));
	txt->data = text;
	txt->backColor = background;
	txt->frontColor = color;
	txt->bufferContents.printBufferCont = calloc(textSize, sizeof(CHAR_INFO));
	txt->bufferContents.isAlphaTile = NULL;
	txt->bufferContents.alreadyDrawn = NULL;
	return txt;
}

void CDMSetForegroundColor(CDMSurface ** surface, 
	const CDMEnum c1, 
	const CDMEnum c2, 
	const CDMEnum c3, 
	const CDMEnum c4)
{
	(*surface)->pallete.p1.frontColor = c1;
	(*surface)->pallete.p2.frontColor = c2;
	(*surface)->pallete.p3.frontColor = c3;
	(*surface)->pallete.p4.frontColor = c4;
}

void CDMSetBackgroundColor(CDMSurface ** surface,
	const CDMEnum c1, 
	const CDMEnum c2, 
	const CDMEnum c3, 
	const CDMEnum c4)
{
	(*surface)->pallete.p1.backColor = c1;
	(*surface)->pallete.p2.backColor = c2;
	(*surface)->pallete.p3.backColor = c3;
	(*surface)->pallete.p4.backColor = c4;
}

void CDMSetCharacters(CDMSurface ** surface, 
	const CDMEnum c1, 
	const CDMEnum c2, 
	const CDMEnum c3, 
	const CDMEnum c4)
{
	(*surface)->pallete.p1.character = c1;
	(*surface)->pallete.p2.character = c2;
	(*surface)->pallete.p3.character = c3;
	(*surface)->pallete.p4.character = c4;
}

void CDMDrawSurface(CDMContext ** ctx, CDMSurface * surface)
{
	COORD		pos = { surface->rect.Left,surface->rect.Top },
				size = { surface->rect.Right, surface->rect.Bottom };
	SMALL_RECT	rect = surface->rect;
	WriteConsoleOutput(
		(*ctx)->mainBufferActive ? (*ctx)->backBuffer : (*ctx)->mainBuffer,
		surface->bufferContents.printBufferCont,
		pos, size, &rect);
}

void CDMAddSurfaceToContext(CDMContext ** ctx, CDMSurface * surface)
{
	SHORT i, j, si, sj, ctxAccessor, srfcAccessor; 
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

void CDMDrawText(CDMContext ** ctx, CDMText * txt)
{
	COORD		pos = { txt->rect.Left,txt->rect.Top },
		size = { txt->rect.Right, txt->rect.Bottom };
	SMALL_RECT	rect = txt->rect;
	WriteConsoleOutput(
		(*ctx)->mainBufferActive ? (*ctx)->backBuffer : (*ctx)->mainBuffer,
		txt->bufferContents.printBufferCont,
		pos, size, &rect);
}

void CDMAddTextToContext(CDMContext ** ctx, CDMText * txt)
{
	SHORT i, j, si, sj, ctxAccessor, srfcAccessor;
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
				(*ctx)->contents.alreadyDrawn[ctxAccessor] = CDMFALSE;
			}
			else
				(*ctx)->contents.alreadyDrawn[ctxAccessor] = CDMTRUE;
		}
	}
}

void CDMSetColorRGB(CDMColorScheme* data, short position, short r, short g, short b)
{
	data->colors[position % 16] = RGB(r % 256, g % 256, b % 256);
}

void CDMSetColorBin(CDMColorScheme* data, short position, const DWORD color)
{
	data->colors[position % 16] = color;
}

void CDMClearScreen(CDMContext ** ctx)
{
	SHORT i, j;
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

void CDMDraw(CDMContext * ctx)
{
	COORD	size = { (ctx)->rect.Right,(ctx)->rect.Bottom },
		top = { (ctx)->rect.Left, (ctx)->rect.Top };
	CDMRect r;
	WriteConsoleOutput(
		(ctx)->mainBufferActive ? (ctx)->backBuffer : (ctx)->mainBuffer,
		(ctx)->contents.printBufferCont,
		size, top, &r);
}

int CDMGetR(CDMColorScheme* data, const short position)
{
	return GetRValue(data->colors[position % 16]);
}

int CDMGetG(CDMColorScheme* data, const short position)
{
	return GetGValue(data->colors[position % 16]);
}

int CDMGetB(CDMColorScheme* data, const short position)
{
	return GetBValue(data->colors[position % 16]);
}

void CDMSetActiveScheme(CDMColorScheme data, CDMContext** ctx)
{
	int i;
	for (i = 16; i--;)
		(*ctx)->inf.ColorTable[i] = data.colors[i];
	SetConsoleScreenBufferInfoEx((*ctx)->mainBuffer, &(*ctx)->inf);
	SetConsoleScreenBufferInfoEx((*ctx)->backBuffer, &(*ctx)->inf);
}

void CDMSetPixel(CDMSurface ** surface, short x, short y, CDMEnum pixelSet)
{
	(*surface)->data[y * (x * (*surface)->rect.Right)] = pixelSet;
}

CDMBool CDMCompareCHARINFO(CHAR_INFO rhs, CHAR_INFO lhs)
{
	return rhs.Attributes == lhs.Attributes &&
		rhs.Char.AsciiChar == lhs.Char.AsciiChar ? CDMTRUE : CDMFALSE;
}

void CDMPollEvents(CDMContext* ctx, CDMEvent * event)
{
	GetNumberOfConsoleInputEvents(ctx->InputBuffer, &event->inputNum);
	ReadConsoleInput(ctx->InputBuffer, event->inputs, 51, &event->inputNum);
}

CDMBool CDMGetKeyPressed(CDMEvent * event, const CDMEnum key)
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

CDMBool CDMGetKeyDown(CDMEvent * event, const CDMEnum key)
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

CDMBool CDMGetKeyUp(CDMEvent * event, const CDMEnum key)
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

CDMCoord CDMGetMousePos(CDMEvent * event)
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
	COORD ret = { 0,0 };
	return ret;
}

void CDMKeepScreenSize(CDMContext ** ctx, CDMEvent* event)
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


