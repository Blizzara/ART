/*
    Copyright (c) <year> <copyright holders>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "Box.h"

// Box::Box()
// {
// 
// }

Box::Box(Vector a_point1, Vector a_point2, bool a_is_light, Texture text)
{
	m_is_light = a_is_light;
	texture = text;
	bounds[0] = Vector(std::min(a_point1.x,a_point2.x), std::min(a_point1.y,a_point2.y), std::min(a_point1.z,a_point2.z));
	bounds[1] = Vector(std::max(a_point1.x,a_point2.x), std::max(a_point1.y,a_point2.y), std::max(a_point1.z,a_point2.z));
// 	bounds[0].CoutVector("min corner");
// 	bounds[1].CoutVector("max corner");
	
	dx = bounds[1].x-bounds[0].x;
	dy = bounds[1].y-bounds[0].y;
	dz = bounds[1].z-bounds[0].z;
// 	Vector corners[8];
// 	corners[0] = a_point1;
// 	corners[1] = a_point1+Vector(dx,0,0);
// 	corners[2] = a_point1+Vector(0,0,dz);
// 	corners[3] = a_point1+Vector(dx,0,dz);
// 	corners[4] = a_point1+Vector(0,dy,0);	
// 	corners[5] = a_point1+Vector(dx,dy,0);	
// 	corners[6] = a_point1+Vector(0,dy,dz);
// 	corners[7] = a_point1+Vector(dx,dy,dz);		// = a_point2
// 	
// 	triangle[0][0] = Triangle(corners[0],corners[1],corners[2]);	// bottom
// 	triangle[0][1] = Triangle(corners[3],corners[1],corners[2]);	// dy = 0
// 
// 	triangle[1][0] = Triangle(corners[4],corners[5],corners[6]);	// top 
// 	triangle[1][1] = Triangle(corners[7],corners[5],corners[6]);	// +dy
// 	
// 	triangle[2][0] = Triangle(corners[2],corners[3],corners[6]);	// back	
// 	triangle[2][1] = Triangle(corners[7],corners[3],corners[6]);	// +dz
// 	
// 	triangle[3][0] = Triangle(corners[0],corners[1],corners[4]);	// front
// 	triangle[3][1] = Triangle(corners[5],corners[1],corners[4]);	// dz=0
// 	
// 	triangle[4][0] = Triangle(corners[0],corners[2],corners[4]);	// left
// 	triangle[4][1] = Triangle(corners[6],corners[2],corners[4]);	// dx=0
// 	
// 	triangle[5][0] = Triangle(corners[1],corners[3],corners[5]);	// right
// 	triangle[5][1] = Triangle(corners[7],corners[3],corners[5]);	// +dx

	rng.setSeed(time(NULL));
	
	
// 	for (int i = 0; i < 6; i++)
// 	{	
// 		triangle[i][0].Cout("0");
// 		triangle[i][1].Cout("1");
// 	}
}


Vector Box::Normal(Vector a_intersection)
{
	// stupid and must be slow, as this is doing the intersections test again..
// 	Ray testray(Vector(0,0,0),a_intersection);
// 	a_intersection.CoutVector("intersection");
	if(fabs(a_intersection.x - bounds[0].x) < EPSILON)
		return Vector(-1, 0, 0);
	else if(fabs(a_intersection.x - bounds[1].x) < EPSILON)
		return Vector( 1, 0, 0);
	else if(fabs(a_intersection.y - bounds[0].y) < EPSILON)
		return Vector( 0,-1, 0);
	else if(fabs(a_intersection.y - bounds[1].y) < EPSILON)
		return Vector( 0, 1, 0);
	else if(fabs(a_intersection.z - bounds[0].z) < EPSILON)
		return Vector( 0, 0,-1);
	else if(fabs(a_intersection.z - bounds[1].z) < EPSILON)
		return Vector( 0, 0, 1);

// 	for (int i = 0; i < 6; i++)	// try all 6 sides
// 	{
// 		if (triangle[i][0].Inside(a_intersection)) return triangle[i][0].Normal();	//side consists of two polygons
// 		if (triangle[i][1].Inside(a_intersection)) return triangle[i][1].Normal();
// 	}
	std::cout << "Dying! Intersection: " << a_intersection << std::endl;

	return Vector(0,0,0);
}

double Box::Intersect(Ray a_ray)
{
// 	std::cout << "Testing for box ------------------------------------------------------------" << std::endl;
	double tnear = 1/(-0.0), tfar = 1/0.0;
	Vector ray_dir = a_ray.GetVector();
	Vector ray_origin = a_ray.GetOrigin();

	double t1, t2, ddir;
	ddir = 1.0/ray_dir.x;
	if(ddir >= 0)
	{
		t1 = (bounds[0].x-ray_origin.x)*ddir;
		t2 = (bounds[1].x-ray_origin.x)*ddir;
	}
	else
	{
		t2 = (bounds[0].x-ray_origin.x)*ddir;
		t1 = (bounds[1].x-ray_origin.x)*ddir;
	}
	tnear = t1;
	tfar = t2;
// 	std::cout << tnear << " x " << tfar << std::endl;
// 	std::cout << t1 << " x " << t2 << std::endl;
	if(tfar < 0 || tnear > tfar)	// box behind ray or box missed
	{
// 		std::cout << "got miss! x " << tnear << tfar << std::endl;
		return -1;
	}
	
	ddir = 1.0/ray_dir.y;
	if(ddir >= 0)
	{
		t1 = (bounds[0].y-ray_origin.y)*ddir;
		t2 = (bounds[1].y-ray_origin.y)*ddir;
	}
	else
	{
		t2 = (bounds[0].y-ray_origin.y)*ddir;
		t1 = (bounds[1].y-ray_origin.y)*ddir;
	}
	if (t1 > tnear)
	{
		tnear = t1;
	}
	if (t2 < tfar)
	{
		tfar = t2;
	}
// 	std::cout << tnear << " y " << tfar << std::endl;
// 	std::cout << t1 << " y " << t2 << std::endl;
	if(tfar < 0 || tnear > tfar)	// box behind ray or box missed
	{
// 		std::cout << "got miss y ! " << tnear << tfar << std::endl;
		return -1;
	}
	ddir = 1.0/ray_dir.z;
	if(ddir >= 0)
	{
		t1 = (bounds[0].z-ray_origin.z)*ddir;
		t2 = (bounds[1].z-ray_origin.z)*ddir;
	}
	else
	{
		t2 = (bounds[0].z-ray_origin.z)*ddir;
		t1 = (bounds[1].z-ray_origin.z)*ddir;
	}
	
	if (t1 > tnear)
		tnear = t1;
	if (t2 < tfar)
		tfar = t2;
// 	std::cout << tnear << " z " << tfar << std::endl;
// 	std::cout << t1 << " z " << t2 << std::endl;
	if(tfar < 0 || tnear > tfar)	// box behind ray or box missed
	{
// 		std::cout << "got miss! z " << tnear << tfar << std::endl;
		return -1;
	}
// 	std::cout << tnear << " " << tfar << std::endl;
	return tnear;		// returns the smalles positive distance
}

// double Box::Intersect(Ray a_ray)
// {
// 	// 	std::cout << "Testing for box ------------------------------------------------------------" << std::endl;
// 	double distance = -1, temp = 0;
// 	for (int i = 0; i < 6; i++)	// try all 6 sides
// 	{
// 		temp = triangle[i][0].Intersect(a_ray);
// 		// 		std::cout << i << "0 " << temp << std::endl;
// 		if (temp > 0 && (temp < distance || distance < 0))
// 		{
// 			distance = temp;	//side consists of two polygons
// 		}
// 		temp = triangle[i][1].Intersect(a_ray);
// 		// 		std::cout << i << "1 " << temp << std::endl;
// 		if (temp > 0 && (temp < distance  || distance < 0))
// 		{
// 			distance = temp;
// 		}
// 	}
// 	// 	if(distance > 0) std::cout << "Box got hit!" << std::endl;
// 	// 	std::cout << distance << " " << temp << std::endl;
// 	return distance;		// returns the smalles positive distance
// }

Vector Box::RandomSurfacePoint(void ) // Should work, to be tested some day
{
	int side = rng.getNext()%6;
	double u = rng.getNext()/ISAAC_MAX;
	double v = rng.getNext()/ISAAC_MAX;
	switch (side)
	{
		case 0:
			return bounds[0] + Vector(u*dx,v*dy,0);
		case 1:
			return bounds[0] + Vector(u*dx,v*dy,dz);
		case 2:
			return bounds[0] + Vector(0,u*dy,v*dz);
		case 3:
			return bounds[0] + Vector(dx,u*dy,v*dz);
		case 4:
			return bounds[0] + Vector(v*dx,0,u*dz);
		case 5:
			return bounds[0] + Vector(v*dx,dy,u*dz);
	}
// 	return triangle[side][which].RandomSurfacePoint();
}


Box::~Box()
{
}


