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
#include "RTEngine.h"

// RTEngine::RTEngine(Scene *a_scene) : scene(a_scene)
// {
// 
// 	srand(time(NULL));
// 	rng.setSeed(time(NULL));
// 
// 	scWidth = scene->Width();
// 	scHeight = scene->Height();
// }

RTEngine::RTEngine(Scene& a_scene) : scene(a_scene)
{
	srand(time(NULL));
	rng.setSeed(time(NULL));

	scWidth = scene.Width();
	scHeight = scene.Height();
	scene_objects_count = scene.CountObjects();
}

RTEngine::~RTEngine()
{

// 	scene = NULL;

	std::cout << "RTEngine closing.." << std::endl;
}




void RTEngine::Trace(void)
{
	Color rgb, tmprgb;
	
	double sc_x = ((double)rng.getNext()/ISAAC_MAX);		// ISAAC is faster!
	double sc_y = ((double)rng.getNext()/ISAAC_MAX);

// 	if(sc_x > 0.5) sc_x = 1-sc_x;
// 	if(sc_y > 0.5) sc_y = 1-sc_y;
	
	//turning off unidirectional tracing.. now! 
	//rgb = TraceFromCam(sc_x, sc_y);
	
/*		Let's implement bidirectional tracing! 		*/
	std::vector<struct intersectionPoint> camera_path;
	std::vector<struct intersectionPoint> light_path;
	
	TraceFromCam(sc_x,sc_y,camera_path);	// start a trace from camera
	TraceFromLight(light_path);		// start a trace from some random light source

	rgb = Color(0);
	unsigned int i,j;
	Color color, colorweight;
	Vector tmpdirect;
	double ambient, ldot, cdot;

// 	std::cout << "Looping.." << std::endl;
	for (i =0; i < camera_path.size(); ++i)
	{
		ambient = camera_path[i].ambient;
		if (i == 0 && ambient > 0)
			rgb = rgb + camera_path[i].color*ambient;
		else if(ambient > 0)
		{
			rgb = rgb + camera_path[i].color*ambient*camera_path[i-1].colorweight*camera_path[i].dot;
			
// 			camera_path[i-1].colorweight.CoutVector("colorweight");
// 			rgb.CoutVector("rgb");
		}

		for ( j=0; j < light_path.size(); ++j)
		{
			tmpdirect = light_path[j].point-camera_path[i].point;
			tmpdirect.Normalize();
			cdot = DOT(camera_path[i].normal,tmpdirect);
			ldot = DOT(light_path[j].normal,-tmpdirect);
			if(cdot > 0 && ldot > 0 && !camera_path[i].reflection && Connect(camera_path[i], light_path[j]))
			{
// 				
// 				std::cout << DOT(camera_path[i].normal,tmpdirect) << " and light ";
// 				std::cout << DOT(light_path[j].normal,-tmpdirect) << std::endl;
				
				rgb = rgb + cdot * camera_path[i].colorweight*light_path[j].colorweight;

// 				std::cout << "Connected! i: "<< i << " j: " << j << " cdot: " << cdot << std::endl;
// 				std::cout << "Normal: " << camera_path[i].normal << " rgb: " << rgb << " cw-camera: " << camera_path[i].colorweight << " cw-light: " << light_path[j].colorweight << std::endl;
			}
		}
	}
	
	if(rgb.Length() != 0)
	{
		scene.Pixel(sc_x*(scWidth-1), sc_y*(scHeight-1), rgb);
	}
}




void RTEngine::TraceFromCam(double a_sc_x, double a_sc_y, std::vector< intersectionPoint >& points)	// for bidirectional tracing
{	// 0 <= a_sc_x <= 1, 0 <= a_sc_y <= 1
	Camera camera = scene.GetCamera();
	
// 	RayTrace(Ray(camera.GetLoc(), camera.DirectionByPos(0.5, 0.5).Normalize()), 0, points);
	RayTrace(Ray(camera.GetLoc(), camera.DirectionByPos(a_sc_x, a_sc_y).Normalize()), 0, points);
}

void RTEngine::TraceFromLight(std::vector< intersectionPoint >& points)		// for bidirectional tracing
{
	Vector rand_dir;
	Vector normal(0,1,0);

	intersectionPoint light;
	
	// Selecting random object with ambient > 0
	//int objects_count = scene.CountObjects();	//moved to Constructor, as it's constant
	
	int i;
	do
	{
		i = rng.getNext()%scene_objects_count;
// 		std::cout << "Failing.." << std::endl;
	}
	while(scene.GetObject(i)->GetTexture().GetAmbient() <= 0);
	
	
	// Selecting random point withing object
	light.point = scene.GetObject(i)->RandomSurfacePoint();
	light.normal = scene.GetObject(i)->Normal(light.point);
	if(normal.Length() == 0)
	{
		std::cout << "Normal length zero!" << std::endl;
		return;
	}
	light.ambient = scene.GetObject(i)->GetTexture().GetAmbient();
	light.weight = light.ambient;
	light.color = scene.GetObject(i)->GetTexture().GetColor();
	light.colorweight = light.ambient*light.color;

	
	rand_dir = Vector(rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2));	// ISAAC is faster!
	rand_dir.Normalize();
	double dot = DOT(rand_dir, normal);
	if(dot < 0)		// create random vector in light-points hemisphere
	{
		rand_dir = -rand_dir;
		dot = DOT(rand_dir, normal);
		
	}
	
	light.color *= dot;
	points.push_back(light);
// 	RayTrace(Ray(light_loc.point, rand_dir), 0, points);
}


// tests if there is a free path between two points
bool RTEngine::Connect(intersectionPoint a_cam, struct intersectionPoint a_light)
{	
	Vector origin = a_cam.point;
	Vector direction = a_light.point-origin;
	double distance = 0, lenght = direction.Length();

	direction.Normalize();
	distance = TestShadow(Ray(origin, direction));
	
	double diff =fabs(distance-lenght);
	if (diff < (1.0/1000000)) //account for rounding errors
	{
		return true;
	}
	else
	{
		return false;
	}
}



/* the bidirectional path tracing way */
void RTEngine::RayTrace(Ray a_ray, int a_depth, std::vector<intersectionPoint>& points, double a_dot)
{
	// 	std::cout << "Tracing Ray, depth " << a_depth << std::endl;

	
	double distance = -1;
	int nearest = IntersectObject(a_ray, distance);
	if(nearest  == -1 || distance <=0 )	// if we didn't have any intersections
		return;

	struct intersectionPoint intersection;
	intersection.ray_direction = a_ray.GetVector().Normalize();//any reason why GetVector is not normalized by default?
	intersection.point = a_ray.GetOrigin() + a_ray.GetVector() * distance; 
	
	Texture obj_text = scene.GetObject(nearest)->GetTexture();
	Color obj_color = obj_text.GetColor();
	double ambient = obj_text.GetAmbient();
	double diffuse = obj_text.GetDiffuse();
	double reflection = obj_text.GetReflection();
	double transmit = obj_text.GetTransmit();
	
	Vector normal = scene.GetObject(nearest)->Normal(intersection.point).Normalize(); //any reason why Normal is not normalized by default?

	if (normal.Length() == 0)	return; // It shouldn't be, but just in case.. box caused this to happen

// 	if (DOT(normal,a_ray.GetVector()) > 0)		normal = -normal; //might be the right way, if inside object, normal directs the other way?

	
	double dot;

	double prev_weight, prev_dot;
	Color prev_colorweight;
	
	if (points.size() > 0)
	{
		prev_weight = points.back().weight;
		prev_dot = points.back().dot;
		prev_colorweight = points.back().colorweight;
	}
	else
	{
		prev_weight = 1;
		prev_dot = 1;
		prev_colorweight = Color(1);
	}
	intersection.normal = normal;
	intersection.color = obj_color;
	intersection.ambient = ambient;
// 	intersection.weight = prev_weight*diffuse;
	intersection.colorweight = prev_colorweight*obj_color*a_dot;	// *diffuse if diff. refl; *reflection if specular refl
	intersection.dot = prev_dot*a_dot;
	
// 	if(intersection.colorweight.x < 0) //used for some testing, but why?
// 	{
// 		std::cout << "Colorweight < 0 - dot = " << a_dot << std::endl;
// 	}
	
	bool do_diffuse = false, do_reflection = false, do_refraction = false;		// whether we do diffuse, reflection or refraction FOR THE NEXT RAYAS 
	if(obj_text.GetAmbient() < 1  /*&& a_depth < 0*/) // a_depth used just for testing - < 0 limits to normal pov-style
	{
		if(diffuse > 0 && rand()%100 < diffuse*100)	// do we have diffuse ray?
		{
			do_diffuse = true;
			intersection.colorweight *= diffuse;
		}
		else if (reflection > 0 && rand()%100 < reflection*100)		// or do we have reflection?
		{
			do_reflection = true;
			intersection.colorweight *= reflection;
		}
		else if (transmit> 0 && rand()%100 < transmit*100)		// or maybe refracion?
		{
			do_refraction = true;
			intersection.colorweight *= transmit;
		}
		else
		{
			intersection.colorweight *= diffuse;	// not the best way, I guess
		}
	}
	else
	{
		intersection.colorweight *= diffuse;		// not the best way, either
	}
	
	intersection.reflection = do_reflection;
	points.push_back(intersection);
	
	//BRUTEFORCING THE LIFE!
	
	if(do_diffuse)	// do we have diffuse ray next?
	{
		Vector rand_vector;
		rand_vector = Vector(rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2));		// ISAAC is faster!
		rand_vector.Normalize();
		if (DOT(rand_vector,normal) <= 0) rand_vector = -rand_vector;
		dot = DOT(rand_vector,normal);

		RayTrace(Ray(intersection.point,rand_vector), a_depth+1,points,dot);
	}
	else if (do_reflection)		// or do we have reflection?
	{
		Vector mirror = intersection.ray_direction.Mirror(normal);
		RayTrace(Ray(intersection.point,mirror), a_depth+1,points,1);
	}
	else if (do_refraction)		// or do we have transmittanse/refraction?
	{
		Vector refracted = intersection.ray_direction; // just transmit, don't refract yet..
		RayTrace(Ray(intersection.point,refracted), a_depth+1,points,1); //works somehow, but causes tangent-hits to Sphere
	}
}	

double RTEngine::TestShadow(Ray a_ray)
{
	double dist;
	double near_distance = 0;

	
	for(int i = 0; i < scene.CountObjects(); i++)
	{
		dist = scene.GetObject(i)->Intersect(a_ray);
		if(dist > EPSILON && (dist < near_distance  || near_distance == 0))
		{
			near_distance = dist;
		}
	}
	if( near_distance != 0)
	{
		return near_distance;
	}
	else
	{
		return -1;
	}
}



int RTEngine::IntersectObject(Ray a_ray, double& distance)
{
	double dist;
	double nearest = 0;
	int i, iBack =-1;

	for(i = 0; i < scene.CountObjects(); i++)
	{

		dist = scene.GetObject(i)->Intersect(a_ray);
		if(dist > EPSILON && (dist < nearest  || nearest == 0))
		{
			nearest = dist;
			iBack = i;
		}
	}
	if(iBack != -1 || nearest != 0)
	{
		distance = nearest; //distance is reference
		return iBack;
	}
	else
	{
		distance = -1; //distance is reference
		return -1;
	}
}





