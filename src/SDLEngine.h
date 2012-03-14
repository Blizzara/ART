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
#ifndef SDLENGINE_H
#define SDLENGINE_H



/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/

#include "SDL.h"
#include <iostream>

#define DEFAULT_FLAGS SDL_HWSURFACE|SDL_DOUBLEBUF
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_BPP 0

enum SDLEStatus { SDLENGINE_WORKS, SDLENGINE_FAIL };

class SDLEngine{
public:
    SDLEngine(int width, int height);
    ~SDLEngine();

	int GetWidth() { return scWidth; };
	int GetHeight() { return scHeight; };

	int SetPixel(int x, int y, int r, int g, int b);

	int UpdateSc();

	int Wait();

	bool PollGetEscape();
	bool WaitGetEscape();

	bool PollGetRefresh();
	bool WaitGetRefresh();

	SDLEStatus Status() { return status; };

private:

	void Status(SDLEStatus a_s) { status = a_s; };
	void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
	void Slock();
	void Sulock();

	SDL_Surface *screen;
	SDL_Event event;

	int scWidth;
	int scHeight;

	SDLEStatus status;
};

#endif
