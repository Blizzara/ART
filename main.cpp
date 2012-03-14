#include "src/art.h"

void SphereWall(Scene& scene) //Scene has no copy constructor, can't be returned
{
	//Texture(Color a_color, float a_ambient, float a_diffuse, float a_specular, float a_reflection, float a_transmit)

	scene.AddSphere(Vector(3,10,0), 1, true, Texture(Color(1), 1, 0,0,0,0)); // Light
// 	
	scene.AddPlane(Vector( 0,-1,0), Vector(0,1,0), false, Texture(Color(0.5),0,0.2,0,0.8,0));
	
	scene.AddCamera(Vector(0,3,-10), Vector(0,3,-8.5));
		
	for(float x = -7; x <= 7; ++x)
	{
		for(float y = -0.5; y <= 6.5; ++y)
		{
			scene.AddSphere(Vector( x, y, 8), 0.45, false, Texture(Color((x+7)/14, 1-((y+0.5)/7),(x+y+8)/21),0,0.7,0.3,0,0));
		}
	}
}

void BuildAnotherScene(Scene& scene) //Scene has no copy constructor, can't be returned
{
// 	Scene scene;
	// 	scene.AddLight(Vector(-3,10,0), Vector(1,1,1));
	// 	Texture(Color a_color, a_ambient = 0,a_diffuse = 0.6, a_specular = 0, a_reflection = 0, a_transmit = 0)
	
	
	scene.AddSphere(Vector(3,0,5), 1, false, Texture(Vector(1,0,0), 0, 0.6,0,0,0));

	scene.AddSphere(Vector(0,0,2), 1, false, Texture(Vector(1,1,1), 1, 0.0,0,0,0));

 	scene.AddSphere(Vector(-2,0,0), 1, false, Texture(Vector(0,1,1), 0, 0.6,0,0,0));
	
// 	scene.AddBox(Vector(-3,-1,-1), Vector(-1,1,1), false, Texture(Vector(0,1,1), 0, 0.6,0,0,0));
	scene.AddSphere(Vector(2.5,0,1), 1, false, Texture(Vector(1,1,1), 0, 0.0,0,1,0));
	
	scene.AddPlane(Vector( 0,-1,0), Vector(0,1,0), false, Texture(Color(0.5,0.5,0.5),0,0.6,0,0,0));
	
// 	scene.AddSphere(Vector(0,0,-8),1, false,Texture(Color(1,0,1), 0,0.5)); // tests for see-through
	scene.AddCamera(Vector(0,0,-8), Vector(0,0,-7));
	
// 	return scene;
}

void CornellBox(Scene& scene)
{
// 	Scene scene;
	Color white(1,1,1);
	Color red(1,0,0);
	Color green(0,1,0);
	Color blue(0,0,1);
	Color yellow(0,1,1);
	Color lila(1,0,1);
	
	scene.AddPlane(Vector(5,0,0), Vector(-1,0,0), false, Texture(green,0,0.6));	// right
	scene.AddPlane(Vector(-5,0,0), Vector( 1,0,0), false, Texture(red,0,0.6));	// left
	scene.AddPlane(Vector(0,0,5), Vector( 0,0,-1), false, Texture(lila,0,0.6));	// back 
	scene.AddPlane(Vector(0,0,-5), Vector(0,0,1), false, Texture(white,0,0.6));	// front (behind camera)
// 	scene.AddBox(Vector(5,5,5), Vector(-5,6,-5), false, Texture(white,1,0.0));	// top
	scene.AddPlane(Vector(0,5,0), Vector(0,-1,0), false, Texture(blue,0,0.6));	// top
	scene.AddPlane(Vector(0,0,0), Vector(0,1,0), false, Texture(white,0,0.6));	// bottom
	
// 	scene.AddBox(Vector(-4,-5,4.5), Vector(-2,-1,2.5), false, Texture(blue,0,0.6));
// 	scene.AddBox(Vector( 0,-5,3.5), Vector( 2,-3,4.5), false, Texture(white,0,0.6));
	scene.AddBox(Vector( -4,0,4.5), Vector( -2,2,2.5), false, Texture(white,0,0,0,0.7)); //reflection
	scene.AddBox(Vector(  4,0,4.5), Vector(  2,2,2.5), false, Texture(white,0,0,0,0,1)); //transmit/refraction

	scene.AddSphere(Vector(3.5,3.5,3), 1, false, Texture(white,1,0));	//the lamp

	scene.AddCamera(Vector(0,2.5,-4.9), Vector(0,2.5,-3.9));
	
	// 	Sphere sphere(Vector(0.1,0,0), 0.3, false, Texture());
	// 	Sphere sphere2(Vector(-0.1,0,0), 0.2, false, Texture());
	// 	
	// 	scene.AddIntersection(&sphere, &sphere2);
	
	
// 	return (Scene&)scene;
}

// Scene CameraTest(void)
// {
// 	Scene scene;
// 	scene.AddBox(Vector(-0.5,-0.5,1.0), Vector(0.5,0.5,1.1), false, Texture(Color(0,1,0),1,0,0,0));
// 	scene.AddCamera(Vector(0,0,0), Vector(0,0,1));
// 	return scene;
// }


void TransmitTest(Scene& scene) //Scene has no copy constructor, can't be returned
{
	//Texture(Color a_color, float a_ambient, float a_diffuse, float a_specular, float a_reflection, float a_transmit)

// 	scene.AddPlane(Vector( 0,-0.1,0), Vector(0,1,0), false, Texture(Color(0.5),0,0.2,0,0.8,0));
	
	scene.AddCamera(Vector(0,0,-10), Vector(0,0,8));
	scene.AddSphere(Vector( 5, 8, 8), 0.45, false, Texture(Color(1, 1,1),1,0,0,0,0));
	scene.AddSphere(Vector( 0, 0, 8), 0.1, false, Texture(Color(1, 1,0),0,0,0,0,1));

}
int main(int argc, char *argv[])
{

	int width = 800;
	int height = 600;
	Scene scene; // as Scene has no copy constructor, those scene-building-functions can't return it
//  	Scene scene = SphereWall();	
// 	Scene scene = BuildAnotherScene();
//  	Scene &scene = CornellBox();
	SphereWall(scene);
// 	CornellBox(scene);
// 	TransmitTest(scene);
// 	Scene scene = CameraTest();
	
	scene.Width(width);
	scene.Height(height);
	scene.Init2();
	
	ART(scene);
// 	CmdParser parser(argc, argv);
	
}