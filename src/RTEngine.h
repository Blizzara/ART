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
#ifndef RTENGINE_H
#define RTENGINE_H



#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

#define EPSILON (1.0/10000)

#include "IsaacRand.hh"
#define ISAAC_MAX 4294967296
/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/


struct sColor {
	double r;
	double g;
	double b;
};

#include <vector>

#include "Vector.h"
#include "Scene.h"

struct intersectionPoint {
	Vector point;
	Vector ray_direction;
	Vector normal;
	Vector color;
	Vector colorweight;
	double weight;
	double dot;
	double dot_weight;
	double ambient;
	bool reflection;
};

// #include "Primitive.h"
// #include "Sphere.h"
// #include "Plane.h"
// #include "Camera.h"
// #include "Light.h"

class RTEngine{
public:
    RTEngine(Scene* a_scene);
    RTEngine(Scene& a_scene);

	Color Trace(double a_sc_x, double a_sc_y);
	void Trace(void);


    ~RTEngine();


private:

	IsaacRand rng;

// 	Color TraceFromCam(double a_sc_x, double a_sc_y);
// 	Color RayTrace(Ray a_ray, int a_depth);

	int IntersectObject(Ray a_ray, double& distance);
	double TestShadow(Ray a_ray);
// 	int IntersectLight(Vector intersection, int light);
	
	void TraceFromCam(double a_sc_x, double a_sc_y, std::vector<struct intersectionPoint>& points);
	void TraceFromLight(std::vector<struct intersectionPoint>& points);
	void RayTrace(Ray a_ray, int a_depth, std::vector< intersectionPoint >& points, double a_dot = 1);
	
	bool Connect(struct intersectionPoint a_cam, struct intersectionPoint a_light);
	Color ConnectOld(struct intersectionPoint a_cam, struct intersectionPoint a_light);
	
// 	int IntersectLightObj(Vector intersection, int obj);

	int scWidth;
	int scHeight;
	int scene_objects_count;
	Scene& scene;
};

#endif
