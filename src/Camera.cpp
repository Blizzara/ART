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
#include "Camera.h"

Camera::Camera()
{
}
Camera::Camera(Vector a_location, Vector a_lookat, double a_angle, Vector a_up, Vector a_right) : loc(a_location), lookat(a_lookat), up(a_up), right(a_right)
{ 
	
	sc_x = right.Length();
	sc_y = up.Length();
// 	loc.CoutVector("Camera location");
// 	lookat.CoutVector("Camera look_at");
// 	if (a_angle > EPSILON)
	direction = (lookat - loc);
	if(a_angle > EPSILON)
		direction = direction*right.Length()/tan(a_angle*0.00872664625997164788)*0.5;
	std::cout << a_angle  << " " << DEG_TO_RAD(a_angle/2) << " " <<  right.Length() << " " << tan(DEG_TO_RAD(a_angle/2)) << " " << right.Length()/tan(DEG_TO_RAD(a_angle/2)) << std::endl;
	down = -up;
	
	v = down;
	u = Cross(direction,down).Normalize()*right.Length();
	
	corner = direction-0.5*u-0.5*v;
	std::cout << "Camera direction: " << direction << std::endl;
	std::cout << "Camera up: " << up << std::endl;
	std::cout << "Camera right: " << right << std::endl;
	
	std::cout << "Camera u: " << u << std::endl;
	std::cout << "Camera v: " << v << std::endl;
	std::cout << "Camera corner: " << corner << std::endl;
	
// 	std::cout << "Angles: " << 2*max_angle_radx*360/(2*PI) << " and  " << 2*max_angle_rady*360/(2*PI) << std::endl;
}

Vector Camera::DirectionByRads(double a_radx, double a_rady)	// more rays towards the center of screen
{
	return direction+direction.Length()*(sin(a_radx)*right+sin(a_rady)*up);
}

Vector Camera::DirectionByPos(double a_x, double a_y)		// should give pretty uniform distribution
{
	return corner + u*a_x + v*a_y;	// starting from top left corner
}



Camera::~Camera()
{
}


