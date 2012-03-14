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
#ifndef SPHERE_H
#define SPHERE_H

/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/

// #define NDEBUG
#include "assert.h"
#include <ctime>

#include "Primitive.h"
#include "Vector.h"
#include "Ray.h"

class Sphere : public Primitive
{
public:
	Sphere();
	Sphere(Vector loc, double r, bool a_is_light, Texture text);

	double Intersect(Ray a_ray);

	Vector Normal(Vector a_intersection);
	Vector RandomSurfacePoint(void);
	
	~Sphere();

private:
	Vector loc;
	double r;
	
};

#endif
