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

#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "Primitive.h"
#include "Plane.h"

#include <cmath>

class Triangle : public Primitive
{
public:
	Triangle();
	Triangle(Vector a_p1, Vector a_p2, Vector a_p3, bool a_is_light = false, Texture text = Texture());

	void Cout(std::string a_name);
	
	Vector Normal(Vector a_intersection = Vector());
	double Intersect(Ray a_ray);
	Vector RandomSurfacePoint();
	
	bool Inside(Vector a_point);
	~Triangle();
  private:
// 	Plane plane;
	Vector center;
	Vector normal;	// used for plane-
	double plane_d;	// intersecion -testing
	
	Vector point[3];
	Vector v;
	Vector u;
	
};

#endif // TRIANGLE_H
