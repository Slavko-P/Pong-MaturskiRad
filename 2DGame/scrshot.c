#include "types.h"
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable:4996) //For disabling localtime security warning
#endif

void TakeScreenshot() {
	
	int w, h;
	char TimeString[24]; //space for "%dd-%mm-%YYYY_%HH.%MM.%SS\0" //24
	const Uint32 format = SDL_GetWindowPixelFormat(window);
	time_t current_time;
	struct tm *time_info;

	time(&current_time);
	time_info = localtime(&current_time); 

	strftime(TimeString, sizeof(TimeString), "%d-%m-%Y_%H.%M.%S", time_info); 
	SDL_GetRendererOutputSize(renderer, &w, &h);

	SDL_Surface* pScreenShot = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format);
	SDL_RenderReadPixels(renderer, NULL, format, pScreenShot->pixels, pScreenShot->pitch);
	
	int BufferSize = snprintf(NULL, 0, "%s%s", TimeString, ".bmp") + 1;
	char *NewString = (char *)malloc(BufferSize);
	snprintf(NewString, BufferSize, "%s%s", TimeString, ".bmp");

	SDL_SaveBMP(pScreenShot, NewString);
	
	free(NewString);
	SDL_FreeSurface(pScreenShot);
}