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
#ifndef PLANE_H
#define PLANE_H

/**
	@author Arttu Voutilainen <blizzara@zbxt.net>
*/

#include "Vector.h"
#include "Primitive.h"
#include "Ray.h"

class Plane : public Primitive {
public:
    Plane();
    Plane(Vector a_loc, Vector a_normal, bool a_is_light, Texture a_texture);

    ~Plane();

	double Intersect(Ray a_ray);

	Vector Normal(Vector a_intersection);
	Vector RandomSurfacePoint(void);

private:

	Vector loc;
	Vector normal;
	double d;
	Vector u;
	Vector v;

};

#endif
