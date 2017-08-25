#include "CDM.h"

CDMContext* CDMCreateContext(const int width, const int height)
{
	CDMContext* ctx = malloc(sizeof(CDMContext));
	ctx->backBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |				// read/write access
		GENERIC_WRITE,
		FILE_SHARE_READ |			// shared 
		FILE_SHARE_WRITE,        
		NULL,						// default security attributes 
		CONSOLE_TEXTMODE_BUFFER,	// must be TEXTMODE 
		NULL);
	ctx->mainBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |				// read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |			// shared 
		FILE_SHARE_WRITE,        
		NULL,						// default security attributes 
		CONSOLE_TEXTMODE_BUFFER,	// must be TEXTMODE 
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
		(SHORT)width,
		(SHORT)height };
	MoveWindow(wnd, -8, 0, width - 1, height - 1, FALSE);
	char*	mod = calloc(100, sizeof(char)),
			*num = calloc(5, sizeof(char));
	ctx->contents.printBufferCont = calloc(width * height, sizeof(CHAR_INFO));
	mod[0] = '\0';
	strcat_s(mod, 100, "MODE CON: COLS=\0");
	_itoa_s(width, num, 5, 10);
	strcat_s(mod, 100, num);
	free(num);
	strcat_s(mod, 100, " LINES=\0");
	_itoa_s(height, num, 5, 10);
	strcat_s(mod, 100, num);
	free(num);
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(ctx->mainBuffer, &inf);
	SetConsoleScreenBufferSize(ctx->backBuffer, coord);
	system(mod);
	SetConsoleActiveScreenBuffer(ctx->mainBuffer);
	SetConsoleScreenBufferSize(ctx->mainBuffer, coord);
	system(mod);
	SetConsoleWindowInfo(ctx->mainBuffer, TRUE, &wndw);
	wndw = ((SMALL_RECT){
		0,
		0,
		(SHORT)width,
		(SHORT)height });
	SetConsoleWindowInfo(ctx->backBuffer, TRUE, &wndw);
	GetConsoleScreenBufferInfoEx(ctx->mainBuffer, &ctx->inf);
	return ctx;
}

CDMSurface * CMDCreateSurface(const SHORT posX, const SHORT posY, const SHORT sizeX, const SHORT sizeY)
{
	CDMSurface* srfc = malloc(sizeof(CDMSurface));
	int i;
	srfc->rect = ((CDMRect) { posX, posY, sizeX, sizeY });
	srfc->data = calloc(sizeX*sizeY, sizeof(unsigned char));
	srfc->bufferContents.printBufferCont = calloc(sizeX * sizeY, sizeof(CHAR_INFO));
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
}

void CDMFreeText(CDMText ** txt)
{
	free((*txt)->data);
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
			case 0:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->characters.p1;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->frontColors.p1 | (*surface)->backgroundColors.p1;
				break;
			case 1:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->characters.p2;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->frontColors.p2 | (*surface)->backgroundColors.p2;
				break;
			case 2:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->characters.p3;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->frontColors.p3 | (*surface)->backgroundColors.p3;
				break;
			case 3:
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Char.AsciiChar =
					(*surface)->characters.p4;
				(*surface)->bufferContents.printBufferCont[j + (i*(*surface)->rect.Right)].Attributes =
					(*surface)->frontColors.p4 | (*surface)->backgroundColors.p4;
				break;
			}
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

CDMText * CDMTextWrapper(char * text, const short color, const short background)
{
	CDMText* txt = malloc(sizeof(CDMText));
	txt->data = text;
	txt->backColor = background;
	txt->frontColor = color;
	return txt;
}

void CDMSetForegroundColor(CDMSurface ** surface, const char c1, const char c2, const char c3, const char c4)
{
	(*surface)->frontColors.p1 = c1;
	(*surface)->frontColors.p2 = c2;
	(*surface)->frontColors.p3 = c3;
	(*surface)->frontColors.p4 = c4;
}

void CDMSetBackgroundColor(CDMSurface ** surface, const char c1, const char c2, const char c3, const char c4)
{
	(*surface)->backgroundColors.p1 = c1;
	(*surface)->backgroundColors.p2 = c2;
	(*surface)->backgroundColors.p3 = c3;
	(*surface)->backgroundColors.p4 = c4;
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
	SHORT i, j; 
	for (i = surface->rect.Left;
		i < surface->rect.Right && i < (*ctx)->rect.Right; ++i)
	{
		for (j = surface->rect.Top;
			j < surface->rect.Right && i < (*ctx)->rect.Right; ++i)
		{
			(*ctx)->contents.printBufferCont[j + (i*(*ctx)->rect.Right)] =
				surface->bufferContents.printBufferCont[j + (i*(surface)->rect.Right)];
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
	SHORT i, j;
	for (i = txt->rect.Left;
		i < txt->rect.Right && i < (*ctx)->rect.Right; ++i)
	{
		for (j = txt->rect.Top;
			j < txt->rect.Right && i < (*ctx)->rect.Right; ++i)
		{
			(*ctx)->contents.printBufferCont[j + (i*(*ctx)->rect.Right)] =
				txt->bufferContents.printBufferCont[j + (i*(txt)->rect.Right)];
		}
	}
}

void CDMSetColorRGB(CDMColorScheme* data, int position, int r, int g, int b)
{
	data->colors[position % 16] = RGB(r % 256, g % 256, b % 256);
}

void CDMSetColorBin(CDMColorScheme* data, int position, const DWORD color)
{
	data->colors[position % 16] = color;
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

int CDMGetR(CDMColorScheme* data, const int position)
{
	return GetRValue(data->colors[position % 16]);
}

int CDMGetG(CDMColorScheme* data, const int position)
{
	return GetGValue(data->colors[position % 16]);
}

int CDMGetB(CDMColorScheme* data, const int position)
{
	return GetBValue(data->colors[position % 16]);
}

void SetActiveScheme(CDMColorScheme data, CDMContext** ctx)
{
	int i;
	for (i = 16; i--;)
		(*ctx)->inf.ColorTable[i] = data.colors[i];
	SetConsoleScreenBufferInfoEx((*ctx)->mainBuffer, &(*ctx)->inf);
	SetConsoleScreenBufferInfoEx((*ctx)->backBuffer, &(*ctx)->inf);
}
