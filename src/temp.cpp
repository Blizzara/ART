// The real tracing stuff

Color RTEngine::Trace(float a_sc_x, float a_sc_y)
{
		Color rgb;
	
	
	//	float sc_x = a_sc_x + (float)rand()/RAND_MAX;
	//	float sc_y = a_sc_y + (float)rand()/RAND_MAX;
	
		float sc_x = a_sc_x /*+ ((float)rng.getNext()/ISAAC_MAX)*/;		// ISAAC is faster!
		float sc_y = a_sc_y /*+ ((float)rng.getNext()/ISAAC_MAX)*/;
	// std::cout << "Isaac: " << ((float)rng.getNext()/ISAAC_MAX) << std::endl;
		rgb = TraceFromCam(sc_x, sc_y);
	
		scene->Pixel(sc_x, sc_y, rgb);
	
		if(rgb.x > 1) rgb.x =1;
		if(rgb.y > 1) rgb.y =1;
		if(rgb.z > 1) rgb.z =1;
	
		return rgb;
	}

Color RTEngine::TraceFromCam(float a_sc_x, float a_sc_y)	// unidirectional one
{
		Vector camera_loc = scene->GetCamera().GetLoc();
		Vector look_at = scene->GetCamera().GetLookat()-camera_loc;
	
		float dx = 8/(float)scWidth;
		float dy = 6/(float)scHeight;
	
		float look_at_x = look_at.x+a_sc_x*dx-4;
		float look_at_y = look_at.y+3-a_sc_y*dy;
		float look_at_z = look_at.z;
	
		Vector d(look_at_x, look_at_y, look_at_z);	// ray's direction
		d.Normalize();
	/*	d.CoutVector("ThisShouldBeOkay");*/
		Color rgb = RayTrace(Ray(camera_loc, d), 0);
		return rgb;
	}



/* this is the old unidirectional way */

Color RTEngine::RayTrace(Ray a_ray, int a_depth)
{
	std::cout << "Tracing Ray, depth " << a_depth << std::endl;
	int nearest;
	float distance = -1;
	nearest = IntersectObject(a_ray, &distance);
		if (nearest ==6) std::cout << "Box intersected! " << distance;
	if(nearest  == -1 || distance == -1 )	// if we didn't have any intersections
	{
		std::cout << "Me's got something wrong in RTEngine::RayTrace()!" << std::endl;
		return scene->BGColor();
	}
	if (nearest ==6) std::cout << " Distance: " << distance << std::endl;
		
	Vector intersection = a_ray.GetOrigin() + a_ray.GetVector() * distance;
	if(nearest == 6) intersection.CoutVector("RayTrace: intersection");
	
	std::cout << "Still tracing, nearest & distance: " << nearest << " & " << distance << std::endl;
		
		
	Texture obj_text = scene->GetObject(nearest)->GetTexture();
	Color obj_color = obj_text.GetColor();
	Color color = obj_color * obj_text.GetAmbient();
	
	Color light_color;
	Vector normal = scene->GetObject(nearest)->Normal(intersection);
		normal.CoutVector("normal");
		
	if (normal.Length() == 0)	return Vector(1,1,1); // It shouldn't be, but just in case.. box caused this to happen this
	if (DOT(normal,a_ray.GetVector()) > 0)		normal = Vector(0,0,0)-normal;
			
	float diffuse = obj_text.GetDiffuse();
	float specular = obj_text.GetSpecular();
	float reflection = obj_text.GetReflection();
		
	float dot;
	std::cout << "Still tracing" << std::endl;
		
	BRUTEFORCING THE LIFE!
		
	if(rand()%100 > 20 && obj_text.GetAmbient() < 1)	// do we continue or stop
	{
		if(diffuse > 0 && rand()%100 < diffuse*100)	// do we have diffuse ray?
		{
			Vector rand_vector(rand()-(RAND_MAX/2), rand()-(RAND_MAX/2), rand()-(RAND_MAX/2));
			dot = 0;
			Vector rand_vector;
			while(dot <= 0)
			{
				rand_vector = Vector(rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2), rng.getNext()-(ISAAC_MAX/2));		// ISAAC is faster!
				rand_vector.Normalize();
				rand_vector.CoutVector("Random vector");
				dot = DOT(rand_vector, normal);
			}
			if(dot > 0)
			{
				Color rands_result = dot* diffuse * obj_color * RayTrace(Ray(intersection,rand_vector), a_depth+1);
				color += rands_result;
			}
		}
		else if (reflection > 0 && rand()%100 < reflection*100)		// or do we have reflection?
		{
			Vector mirror = intersection.Mirror(normal);
			mirror.Normalize();
			Color mirror_result = reflection * RayTrace(Ray(intersection,mirror), a_depth+1);
			color += mirror_result;
		}
	}
	return color;
}	

int RTEngine::IntersectLightObj(Vector intersection, int obj)
{
		float distance =-1;
		int i, obj_2=-1;
	
		Ray tempRay;
	
		Vector tempVec;
	
		tempVec = scene->GetObject(obj)->GetLoc()-intersection;
		tempVec.Normalize();
		tempRay = Ray(intersection, tempVec);
		obj_2 = IntersectObject(tempRay,&distance);
	
		if(obj_2 == -1 || distance == -1)
		{
				return 1;
			}
			else
			{
					return 0;
				}
			}
			

int RTEngine::IntersectLight(Vector intersection, int light)
{
	float distance =-1;
	int obj=-1;
	
	Ray tempRay;
	
	Vector tempVec;
	
	tempVec = scene->GetLight(light).GetLoc()-intersection;
	tempVec.Normalize();
	tempRay = Ray(intersection, tempVec);
	obj = IntersectObject(tempRay,&distance);
	
	if(obj == -1 || distance == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


Color RTEngine::ConnectOld(intersectionPoint a_cam, struct intersectionPoint a_light)
{
	Vector origin = a_cam.point;
	Vector direction = a_light.point-origin;
	float distance = 0, lenght = direction.Length();
	// 	origin.CoutVector("origin");
	// 	direction.CoutVector("direction");
	// 	a_light.point.CoutVector("a_light.point");
	direction.Normalize();
	IntersectObject(Ray(origin, direction), &distance);
	
	Vector tmpcolor;
	
	float diff =fabs(distance-lenght);
	// 	std::cout << diff << std::endl;
	if (diff < (1.0/1000))
	{
		// 		std::cout << distance << " ok with " << lenght << std::endl;
		// 		tmpcolor = a_cam.color*a_light.color*a_cam.weight*a_light.weight;
		// 		tmpcolor.CoutVector("tmpcolor");
		// 		a_cam.color.CoutVector("acam");
		// 		a_light.color.CoutVector("alight");
		// 		std::cout << a_cam.weight << "   " << a_light.weight << std::endl;
		return a_cam.color*a_light.color*a_cam.weight*a_light.weight;
	}
	else
	{
		// 		std::cout << distance << " " << lenght << std::endl;
		return Color(0,0,0);
	}
}