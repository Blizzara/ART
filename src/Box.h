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

/**
@author Arttu Voutilainen <blizzara@blizzard>
*/


#ifndef BOX_H
#define BOX_H

#include <cmath>

#define EPSILON (1.0/10000)


#include "Primitive.h"
// #include "Triangle.h"

#define SMALL_NUM 10^-5

class Box : public Primitive
{

public:
// 	Box();
	Box(Vector a_point1, Vector a_point2, bool a_is_light, Texture text);
	Vector Normal(Vector a_intersection);
	Vector RandomSurfacePoint(void);
	double Intersect(Ray a_ray);
	~Box();

private:
// 	Triangle triangle[6][2];
	Vector bounds[2];	// min-corner and max-corner
	double dx,dy,dz;
};

#endif // BOX_H
