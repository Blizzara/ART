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
#ifndef VECTOR_H
#define VECTOR_H

/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/

#include <cmath>
#include <iostream>

#define DOT(a,b) ((a.x*b.x)+(a.y*b.y)+(a.z*b.z))

class Vector{
public:
	Vector();
	Vector(double a, double b, double c=0) { SetVector(a,b,c); };
	Vector(double a) { SetVector(a,a,a); };

	int SetVector(double a, double b, double c) { x = a; y = b; z = c; return true;};

	Vector Normalize();
	Vector RetUnit();

	double Length();

	Vector Mirror(Vector a_normal);

	Vector Rotate3D(double a_alfa, double a_beta, double a_gamma);

	Vector Rotate3DX(double a_alfa);
	Vector Rotate3DY(double a_alfa);
	Vector Rotate3DZ(double a_alfa);

	~Vector();

 	void operator-= (Vector& param);
 	void operator+= (Vector& param);
 	void operator*= (Vector& param);

 	void operator-= (Vector* param);
 	void operator+= (Vector* param);
 	void operator*= (Vector* param);

	void operator*= (double a_float);
	

	friend Vector operator - (const Vector& a_vector); //unary minus
	friend Vector operator - (const Vector& a_vector1, const Vector& a_vector2);
	friend Vector operator + (const Vector& a_vector1, const Vector& a_vector2);
	friend Vector operator * (const Vector& a_vector1, const Vector& a_vector2);
	friend Vector operator / (const Vector& a_vector1, const Vector& a_vector2);
	friend Vector operator * (const Vector& a_vector, double a_float);
	friend Vector operator * (double a_float, const Vector& a_vector);
	friend Vector operator / (const Vector& a_vector, const double a_float);
	
	friend std::ostream& operator<<(std::ostream& os, const Vector& a_vector);

	union {
		struct { double x, y, z; };
 		struct { double r, g, b; };
		struct { double cell[3]; };
	};


private:
	Vector MultiplyByMatrix(double a[3][4]);

};

Vector Cross(Vector a_vector1, Vector a_vector2);

typedef Vector Color;

#endif
