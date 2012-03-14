/***************************************************************************
 *   Copyright (C) 2008 by Arttu Voutilainen   *
 *   blizzara@blizzard   *
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
#include "SDLEngine.h"

SDLEngine::SDLEngine(int width, int height)
{

	Status(SDLENGINE_WORKS);

	std::cout <<"Initializing SDL..." << std::endl;
	/* Initializes Audio and the CDROM, add SDL_INIT_VIDEO for Video */
	if(SDL_Init(SDL_INIT_VIDEO)< 0) {
		std::cout <<"Could not initialize SDL:" << SDL_GetError() << std::endl;
		Status(SDLENGINE_FAIL);
		SDL_Quit();
		return;
	}

	std::cout << "Initializing video..." << std::endl;

	screen = SDL_SetVideoMode(width, height, DEFAULT_BPP, DEFAULT_FLAGS);
	if(!screen)
	{
		std::cout << "Could not initialize video: " << SDL_GetError() << std::endl;
		Status(SDLENGINE_FAIL);
		SDL_Quit();
	}
	scWidth = width;
	scHeight = height;
}


SDLEngine::~SDLEngine()
{
	std::cout << "Closing SDL..." << std::endl;
	SDL_Quit();
}

void SDLEngine::DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  Slock();

  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }

  Sulock();
}

int SDLEngine::SetPixel(int x, int y, int r, int g, int b)
{
	if(r > 255 || g > 255 || b > 255)
	{
		std::cout << "SDLEngine::SetPixel: Some argument was too big!" << std::endl;
		std::cout << "R, G, B: " << r << " " << g << " " << b << std::endl;
	}
	DrawPixel(screen, x, y, r, g, b);
	return true;
}

int SDLEngine::UpdateSc()
{
	return SDL_Flip(screen);
}

void SDLEngine::Slock()
{
  if ( SDL_MUSTLOCK(screen) )
  {
    if ( SDL_LockSurface(screen) < 0 )
    {
      return;
    }
  }
}

void SDLEngine::Sulock()
{
  if ( SDL_MUSTLOCK(screen) )
  {
    SDL_UnlockSurface(screen);
  }
}


int SDLEngine::Wait()
{
	std::cout << "SDL Waiting for quit..." << std::endl;
	while(!WaitGetEscape());
	return true;

}

bool SDLEngine::WaitGetEscape()
{
	SDL_WaitEvent(&event);
	if (
	    ( event.type == SDL_QUIT ) ||
	    (( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ))
	   )
	{ 
		return true;
	}
	else
	{
		return false;
	}
}
bool SDLEngine::PollGetEscape()
{
	SDL_PollEvent(&event);
	if (
	    ( event.type == SDL_QUIT ) ||
	    (( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_ESCAPE ))
	   )
	{ 
		return true;
	}
	else
	{
		return false;
	}
}

bool SDLEngine::WaitGetRefresh()
{
	SDL_WaitEvent(&event);
	if (
	    ( event.type == SDL_QUIT ) ||
	    (( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_r ))
	   )
	{ 
		return true;
	}
	else
	{
		return false;
	}
}

bool SDLEngine::PollGetRefresh()
{
	SDL_PollEvent(&event);
	if (
	    ( event.type == SDL_QUIT ) ||
	    (( event.type == SDL_KEYDOWN ) && ( event.key.keysym.sym == SDLK_r ))
	   )
	{ 
		return true;
	}
	else
	{
		return false;
	}
}
