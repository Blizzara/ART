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
#ifndef RAY_H
#define RAY_H

/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/

#include "Vector.h"

class Ray{
	
public:
    Ray();

	Ray(Vector orig, Vector vect) : vector(vect), origin(orig) {};

    ~Ray();

	Vector GetOrigin() { return origin; };
	Vector GetVector() { return vector; };


	Ray operator* (float param);

private:
	Vector vector;
	Vector origin;

};

#endif
