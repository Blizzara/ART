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
#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(Vector a_location, double a_radius, bool a_is_light, Texture a_text)
{
	loc = a_location;
	r = a_radius;
	texture = a_text;
	m_is_light = a_is_light;
	
	rng.setSeed(time(NULL));
}

Sphere::~Sphere()
{
// 	std::cout << "Sphere deleted." << std::endl;
}

double Sphere::Intersect(Ray a_ray)
{
	double t1=0,t2=0;
	Vector ray_origin = a_ray.GetOrigin();
	Vector v = ray_origin - loc;
	Vector d = a_ray.GetVector();

// 	PrintVector(v);


	if(round(d.Length()) !=1)
	{
		std::cout << "Sphere::intersect: this should be 1 - d.Length " << d.Length() << " : " << round(d.Length()) << std::endl;
		std::cout << "a_ray vector: " << a_ray.GetVector() << " and a_origin: " << a_ray.GetOrigin() << std::endl;
		
		return false;
	}

// 	std::cout << d.Length() << std::endl;
	double dotvd = DOT(v,d);
	double D = pow(dotvd,2)-DOT(v,v)+(r*r);	// determinant 


	if(D < 0)
	{
// 		std::cout << "No answers, returning blue.. :( D was " << D << std::endl;
		return -1;
	}
	else if(D == 0)
	{
		t1 = -dotvd;

		std::cout << "Sphere: Found an answer, " << t1 << "!" << std::endl;

		return t1;
	}
	else
	{
		double sqrtd = sqrt(D);
		t1 = -dotvd-sqrtd;
		t2 = -dotvd+sqrtd;

		if(t1 > 0)
			return t1;
		else if (t2 > 0)
			return t2;
		else
			return -1;
	}
}

Vector Sphere::Normal(Vector a_intersection)
{
	Vector normal = a_intersection - loc;
// 	normal.CoutVector("Sphere normal before");
	normal.Normalize();
// 	std::cout << "Sphere intersect, loc, normal:" << std::endl;
// 	intersection.CoutVector("Sphere intersection");
// 	loc.CoutVector("Sphere location");
// 	normal.CoutVector("Sphere normal");
	return normal;
}

Vector Sphere::RandomSurfacePoint(void )
{
	Vector rand_point = Vector(rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2));	// ISAAC is faster!
	rand_point.Normalize();
	rand_point = rand_point*r;
	rand_point += loc;
	return rand_point;
}

