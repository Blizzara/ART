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

#include "Triangle.h"

Triangle::Triangle()
{

}


Triangle::Triangle(Vector a_p1, Vector a_p2, Vector a_p3, bool a_is_light, Texture text)
{
	point[0] = a_p1;
	point[1] = a_p2;
	point[2] = a_p3;
	texture = text;
	m_is_light = a_is_light;
	
	normal = Cross(Vector(point[1]-point[0]),Vector(point[2]-point[0]));		//precalculating normal for intersection tests
	normal.Normalize();
// 	normal.CoutVector("Triangle normal");
	plane_d = DOT(point[0], normal);
	center = (point[0]+point[1]+point[2]) / 3;
	
	u = point[1]-point[0];		// going from 3d space to 2d plane u,v
	v = point[2]-point[0];
	
	rng.setSeed(time(NULL));
}

Vector Triangle::Normal(Vector a_intersection)
{
	return normal;
}

double Triangle::Intersect(Ray a_ray)
{
 	Vector ray_origin = a_ray.GetOrigin();
	Vector ray_vector = a_ray.GetVector();

	double numerator = plane_d - (DOT(ray_origin, normal));
	double denominator = DOT(ray_vector, normal);
	double distance;

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
		distance = numerator/denominator;

		if(distance <= 0 )	return -1;
	}
// 	std::cout << "triangle, num denum dist:  " << numerator << " " << denominator << " " << distance << std::endl;
		// reference http://www.softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm
	Vector intersection = ray_origin+ray_vector*distance; 

	if (Inside(intersection))	// so we hit the plane, but are we in the triangle area?
	{
// 		intersection.CoutVector("Intersection test");
		return distance;
	}
	else return -1;
}

bool Triangle::Inside(Vector a_point)
{
/*	Vector u = point[1]-point[0];		// going from 3d space to 2d plane u,v
	Vector v = point[2]-point[0];
	NOW defined in constructor
*/
	
	Vector w = a_point - point[0];	// intersectionpoint to plane
	
	double uv = DOT(u,v);			// precalculating some dots
	double uu = DOT(u,u);
	double vv = DOT(v,v);
	double wv = DOT(w,v);
	double wu = DOT(w,u);
	double denominator = (uv*uv-uu*vv);
	
	double s = (uv*wv-vv*wu)/denominator;
	double t = (uv*wu-uu*wv)/denominator;
	
	if (s >= 0 && t >= 0 && s+t <= 1)	//s = 0, t=1, s+t = 1 are edges
	{
		return true;
	}
	else return false;
}

Vector Triangle::RandomSurfacePoint()
{
	Vector rand_point = point[0], du, dv;
	double s=2, t=2;
	while ( s > 1 || t > 1 || s+t > 1)
	{
		s = rng.getNext()/ISAAC_MAX;
		t = rng.getNext()/ISAAC_MAX;
	}
	
	du = u*s;
	dv = v*t;
	rand_point += du;
	rand_point += dv;
	return rand_point;
	
}


void Triangle::Cout(std::string a_name)
{
	std::cout << "Triangle ( " << a_name << "): " << point[0] << " " << point[1] << " " << point[2] << std::endl;
}


Triangle::~Triangle()
{

}

