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
#include "Intersection.h"

Intersection::Intersection()
{
}

Intersection::Intersection ( Primitive* a_oba, Primitive* a_obb, bool a_is_light, Texture a_texture )
{
	obj_a = a_oba;
	obj_b = a_obb;
	m_is_light = a_is_light;
	texture = a_texture;
}


Intersection::~Intersection()
{
	delete [] obj_a;
	delete [] obj_b;
}



double Intersection::Intersect ( Ray a_ray )
{
	double distance;

	if((distance = obj_a->Intersect(a_ray)) > 0)
	{
		Vector intersection = a_ray.GetOrigin() + a_ray.GetVector() * distance;
		Ray testray1(intersection, Vector(1,1,1));
		Ray testray2(intersection, Vector(-1,-1,-1));
		if(obj_b->Intersect(testray1) > 0 && obj_b->Intersect(testray2) > 0)
		{
			return distance;
		}
	}
	return -1;
}

Vector Intersection::Normal ( Vector a_intersection )
{
	double distance_a,distance_b;
	distance_a = obj_a->Intersect(Ray(Vector(0,0,0), a_intersection));	//ei o ohyvä
	distance_b = obj_b->Intersect(Ray(Vector(0,0,0), a_intersection));	//eikä tääkään
	if(distance_a >= distance_b)
	{
		return obj_a->Normal(a_intersection);
	}
	else
	{
		return obj_b->Normal(a_intersection);
	}
}


