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
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/

#include <ctime>

#ifndef ISAAC_MAX
#include "IsaacRand.hh"
#define ISAAC_MAX 4294967296
#endif

#include "Vector.h"
#include "Ray.h"

#include "Texture.h"


class Primitive{
public:

    virtual ~Primitive() =0;

	Texture GetTexture() {return texture;};
	
	virtual double Intersect(Ray a_ray) = 0;
	virtual Vector Normal(Vector a_intersection) = 0;
	virtual Vector RandomSurfacePoint() = 0;

	bool IsLight(void) { return m_is_light; };
	void IsLight(bool a) { m_is_light = a; };
    

protected:
    Primitive();
	Texture texture;
	bool m_is_light;
	IsaacRand rng;
};

#endif
