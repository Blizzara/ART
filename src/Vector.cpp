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
#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}


Vector::~Vector()
{
}

void Vector::operator-= (Vector& param)
{
	x -= param.x;
	y -= param.y;
	z -= param.z;
}

void Vector::operator+= (Vector& param)
{
	x += param.x;
	y += param.y;
	z += param.z;
}
void Vector::operator*= (Vector& param)
{
	x *= param.x;
	y *= param.y;
	z *= param.z;
}
void Vector::operator-= (Vector* param)
{
	x -= param->x;
	y -= param->y;
	z -= param->z;
}
void Vector::operator+= (Vector* param)
{
	x += param->x;
	y += param->y;
	z += param->z;
}
void Vector::operator*= (Vector* param)
{
	x *= param->x;
	y *= param->y;
	z *= param->z;
}

void Vector::operator*= (double a_float)
{
	x *= a_float;
	y *= a_float;
	z *= a_float;
}




Vector operator - (const Vector& a_vector)
{
	return Vector(-a_vector.x,-a_vector.y,-a_vector.z);
}

Vector operator - (const Vector& a_vector1,const  Vector& a_vector2)
{
	return Vector(a_vector1.x-a_vector2.x, a_vector1.y-a_vector2.y,a_vector1.z-a_vector2.z);
}

Vector operator + (const Vector& a_vector1,const Vector& a_vector2)
{
	return Vector(a_vector1.x+a_vector2.x, a_vector1.y+a_vector2.y,a_vector1.z+a_vector2.z);
}

Vector operator * (const Vector& a_vector1, const Vector& a_vector2)
{
	return Vector(a_vector1.x*a_vector2.x, a_vector1.y*a_vector2.y,a_vector1.z*a_vector2.z);
}

Vector operator / (const Vector& a_vector1, const Vector& a_vector2)
{
	return Vector(a_vector1.x/a_vector2.x, a_vector1.y/a_vector2.y,a_vector1.z/a_vector2.z);
}

Vector operator * (const Vector& a_vector, double a_float)
{
	return Vector(a_vector.x*a_float, a_vector.y*a_float,a_vector.z*a_float);
}

Vector operator * (double a_float, const Vector& a_vector)
{
	return Vector(a_vector.x*a_float, a_vector.y*a_float,a_vector.z*a_float);
}

Vector operator / (const Vector& a_vector, const double a_float)
{
	return Vector(a_vector.x/a_float, a_vector.y/a_float,a_vector.z/a_float);
}

std::ostream& operator<<(std::ostream& os, const Vector& a_vector)
{
	os << "<" << a_vector.x << ", " << a_vector.y << ", " << a_vector.z << ">";
	return os;
}
 
double Vector::Length()
{
	return sqrt(x*x+y*y+z*z);
}

Vector Vector::Normalize()
{
	double leng = Length();
	x = x/leng;
	y = y/leng;
	z = z/leng;
	return Vector(x,y,z);
}

Vector Vector::RetUnit()
{
	Vector temp(x,y,z);
	return temp/Length();
}

Vector Vector::Rotate3DX(double a_alfa)
{
	double matrix[3][4];
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = cos(a_alfa);
	matrix[1][2] = -sin(a_alfa);
	matrix[1][3] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = sin(a_alfa);
	matrix[2][2] = cos(a_alfa);
	matrix[2][3] = 0;

	return MultiplyByMatrix(matrix);

}

Vector Vector::Rotate3DY(double a_alfa)
{
	double matrix[3][4];
	matrix[0][0] = cos(a_alfa);
	matrix[0][1] = 0;
	matrix[0][2] = sin(a_alfa);
	matrix[0][3] = 0;

	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	matrix[2][0] = -sin(a_alfa);
	matrix[2][1] = 0;
	matrix[2][2] = cos(a_alfa);
	matrix[2][3] = 0;

	return MultiplyByMatrix(matrix);

}

Vector Vector::Rotate3DZ(double a_alfa)
{
	double matrix[3][4];
	matrix[0][0] = cos(a_alfa);
	matrix[0][1] = -sin(a_alfa);
	matrix[0][2] = 0;
	matrix[0][3] = 0;

	matrix[1][0] = sin(a_alfa);
	matrix[1][1] = cos(a_alfa);
	matrix[1][2] = 0;
	matrix[1][3] = 0;

	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;

	return MultiplyByMatrix(matrix);

}

Vector Vector::MultiplyByMatrix(double a[3][4])
{
	Vector vec;
	vec.x = a[0][0]*x+a[0][1]*y+a[0][2]*z+a[0][3];
	vec.y = a[1][0]*x+a[1][1]*y+a[1][2]*z+a[1][3];
	vec.z = a[2][0]*x+a[2][1]*y+a[2][2]*z+a[2][3];

	return vec;
}

Vector Vector::Rotate3D(double a_alfa, double a_beta, double a_gamma)
{
	return Rotate3DX(a_alfa).Rotate3DY(a_beta).Rotate3DZ(a_gamma);
}

Vector Vector::Mirror(Vector a_normal)
{
	a_normal.Normalize();
	Vector vec = Vector(x,y,z).Normalize();
	return (vec-2*a_normal*(DOT(vec,a_normal)));
}

Vector Cross(Vector a_vector1, Vector a_vector2)
{
	Vector vec;
	//(a2b3 - a3b2) i + (a3b1 - a1b3) j + (a1b2 - a2b1) k
	vec.x = a_vector1.y*a_vector2.z-a_vector1.z*a_vector2.y;
	vec.y = a_vector1.z*a_vector2.x-a_vector1.x*a_vector2.z;
	vec.z = a_vector1.x*a_vector2.y-a_vector1.y*a_vector2.x;
	return vec;
}	
