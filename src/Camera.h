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
#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#define PI 3.14159265
#define EPSILON (1.0/10000)

#define DEG_TO_RAD(deg) (deg/360.0*2.0*PI)
#define RAD_TO_DEG(rad) (rad*360.0/2.0/PI)

/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/
#include "Vector.h"

class Camera{
public:
	Camera(Vector a_location, Vector a_lookat, double a_angle =0.0, Vector a_up = Vector(0,1,0), Vector a_right = Vector(4.0/3.0,0,0));
	Camera();
    ~Camera();

	Vector GetLoc() { return loc; };
	Vector GetLookat() { return lookat; };
	Vector DirectionByRads(double a_radx = 0, double a_rady = 0);
	Vector DirectionByPos(double a_x = 0, double a_y = 0);
	double GetMaxRadX(void) { return max_angle_radx; };
	double GetMaxRadY(void) { return max_angle_rady; };
	
private:
	Vector loc;
	Vector lookat;
	Vector direction;
	Vector corner;
	
	Vector up;
	Vector down;
	Vector right;
	Vector u;	// left-right (right)
	Vector v;	// up-down    (down)
	double max_angle_radx;
	double max_angle_rady;
	int sc_x;
	int sc_y;
	
};

#endif
