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
#include "Plane.h"

Plane::Plane(Vector a_loc, Vector a_normal, bool a_is_light, Texture a_texture) : loc(a_loc), normal(a_normal)
{ 
	texture = a_texture;
	m_is_light = a_is_light;
	d = DOT(loc, normal);
	
	rng.setSeed(time(NULL));
	if(normal.z == 0)
	{
// 		normal.CoutVector("normal");
		u = Vector(0,0,1);
	}
	else
	{
		double udx = 0;
		double udy = ((double)rng.getNext())/ISAAC_MAX;
		double udz = -normal.y*udy/normal.z;
		u = Vector(udx,udy,udz);
		u.Normalize();
// 		std::cout << udx << " " << udy << " " << udz << std::endl;
	}
	v = Cross(normal,u);
	v.Normalize();
// 	u.CoutVector("u");
// 	v.CoutVector("v");
};


Plane::~Plane()
{
// 	std::cout << "Plane deleted." << std::endl;
}


Vector Plane::Normal(Vector a_intersection)
{
	return normal;
}

double Plane::Intersect(Ray a_ray)
{


	Vector ray_origin = a_ray.GetOrigin();
	Vector ray_vector = a_ray.GetVector();

	double numerator = d - (DOT(ray_origin, normal));
	double denominator = DOT(ray_vector, normal);

	if(numerator == 0 && denominator == 0)
	{
		return -2;
	}
	else if(denominator == 0 && numerator != 0)
	{
		return -1;
	}
	else
	{
		double t = numerator/denominator;

		if(t > 0 )
			return t;
		else return -1;
	}
}

Vector Plane::RandomSurfacePoint(void )
{
	double s = (rng.getNext()/ISAAC_MAX-1/2)*1000;
	double t = (rng.getNext()/ISAAC_MAX-1/2)*1000;
	Vector du = u*s;
	Vector dv = v*t;
	Vector rand_point(loc+du+dv);

// 	rand_point.CoutVector("plane rand point");
	return rand_point;
}
