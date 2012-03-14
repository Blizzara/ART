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
#ifndef SCENE_H
#define SCENE_H

/**
	@author Arttu Voutilainen <blizzara@zbxt.net>
*/

#include "Primitive.h"
#include "Vector.h"
#include "Sphere.h"
#include "Plane.h"
//CSG
#include "Intersection.h"

#include "Light.h"
#include "Camera.h"
#include "Texture.h"

#include <iostream>
#include <vector>
#include "Triangle.h"
#include "Box.h"

class Scene{
public:
    Scene() { Init(); Init2(); };
    Scene(std::string a_args) { Init(); Parse(a_args); };

	void Init2();

    ~Scene();

// 	Color GetPixel(int scX, int scY) { return scImage[scX][scY]; };

	int Width (void) { return scWidth; } ;
	void Width (int a_width) { scWidth = a_width; };

	int Height (void) { return scHeight; };
	void Height (int a_height) { scHeight = a_height; };

	Color BGColor(void) { return bg_color; };
	void BGColor(Color a_bg_color) { bg_color = a_bg_color; };

	int MaxTraceLevel(void) { return max_trace_level; };
	void MaxTraceLevel(int a_max_trace_level) { max_trace_level = a_max_trace_level; };

	void AddSphere(Vector a_location, double a_radius, bool a_is_light = false, Texture a_texture = Texture()) 
		{ primitives.push_back(new Sphere(a_location, a_radius, a_is_light, a_texture)); };

	void AddPlane(Vector a_location, Vector a_normal, bool a_is_light = false, Texture a_texture = Texture()) 
		{ primitives.push_back(new Plane(a_location, a_normal, a_is_light, a_texture)); };

	void AddTriangle(Vector a_p1, Vector a_p2, Vector a_p3, bool a_is_light = false, Texture a_texture = Texture()) 
		{ primitives.push_back(new Triangle(a_p1, a_p2, a_p3, a_is_light, a_texture)); };

	void AddBox(Vector a_point1, Vector a_point2, bool a_is_light = false, Texture a_texture = Texture()) 
		{ primitives.push_back(new Box(a_point1, a_point2, a_is_light, a_texture)); };
		
	void AddIntersection(Primitive* a_oba, Primitive* a_obb, bool a_is_light = false, Texture a_texture = Texture()) 
		{ primitives.push_back(new Intersection(a_oba, a_obb, a_is_light, a_texture)); };

	void AddLight (Vector a_location, Color a_color) { lights.push_back(Light(a_location, a_color)); };

	void AddCamera (Vector a_location, Vector a_lookat, double a_angle = 0.0, Vector a_up = Vector(0,1,0), Vector a_right = Vector(4.0/3.0,0,0)) { camera = Camera(a_location, a_lookat, a_angle, a_up, a_right); };

	Primitive* GetObject(int a_i) { return primitives[a_i]; };
	Light GetLight(int a_i) { return lights[a_i]; };
	Camera GetCamera(void) { return camera; };

	int CountLights(void) { return lights.size(); };
	int CountObjects(void) { return primitives.size(); };


	void Pixel(double a_x, double a_y, Color a_color);
	const Color Pixel(int a_x, int a_y)		 {	Color pixel = pixels.at(a_y*scWidth+a_x)/pixel_count.at(a_y*scWidth+a_x); return pixel; };

private:

	Scene(const Scene& a_scene);	// copying scene is not a good idea => prevent it
  
	void Parse(std::string a_args) {};
	void Init();

	int scWidth;
	int scHeight; 

	int max_trace_level;

// 	Color sc_image[800][600]; // ja kaikki hajoo k�siin!
	Color bg_color;

	std::vector<Light> lights;
	std::vector<Primitive*> primitives;
	std::vector<Color> pixels;
	std::vector<double> pixel_count;
	Camera camera;
};

#endif
