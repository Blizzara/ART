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
#include "Scene.h"


Scene::~Scene()
{
	std::cout << "Scene closing.." << std::endl;

// 	std::cout << "Primitives size: " << primitives.size() << std::endl;

	for ( unsigned int i = 0; i < primitives.size(); ++i )
	{
// 		std::cout << "deleting primitive " << i << std::endl;
		delete primitives[i];	// must be deleted or the memory's not freed, cause those are created with 'new'
	}
	std::cout << "Primitives successfully deleted." << std::endl;
}


void Scene::Init()
{
	max_trace_level = 5;
	bg_color = Color ( 0,0,0 );
	scWidth = 800;
	scHeight = 600;
}

void Scene::Init2()
{
	//std::vector<Color>::iterator it_c = pixels.begin();
	pixels.resize ( scWidth*scHeight, Color ( 0,0,0 ) );
	//pixels.insert(it_c, scWidth*scHeight, bg_color);

//	std::vector<double>::iterator  it_i = pixel_count.begin();
//	pixel_count.insert(it_i, scWidth*scHeight, 0);
	pixel_count.resize ( scWidth*scHeight, 0 );
}

void Scene::Pixel ( double a_x, double a_y, Color a_color )
{
	int x = ( int ) floor ( a_x );
	int y = ( int ) floor ( a_y );

	double dx = a_x - x;
	double dy = a_y - y;

	if ( a_color.x > 1 ) a_color.x =1;
	if ( a_color.y > 1 ) a_color.y =1;
	if ( a_color.z > 1 ) a_color.z =1;

	double weight[4] = { ( 1-dx ) * ( 1-dy ), ( dx ) * ( 1-dy ), ( 1-dx ) * ( dy ), ( dx ) * ( dy ) };
	Color color[4] = {a_color*weight[0], a_color*weight[1], a_color*weight[2], a_color*weight[3]};
// 	color[0].CoutVector("Color 0");
// 	color[1].CoutVector("Color 1");
// 	color[2].CoutVector("Color 2");
// 	color[3].CoutVector("Color 3");

	pixels[y*scWidth+x] += color[0];
	pixel_count[y*scWidth+x] += weight[0];

	if ( x < scWidth-1 )
	{
		pixels[y*scWidth+x+1] += color[1];
		pixel_count[y*scWidth+x+1] += weight[1];
	}

	if ( y < scHeight-1 )
	{
		pixels[ ( y+1 ) *scWidth+x] += color[2];
		pixel_count[ ( y+1 ) *scWidth+x] += weight[2];
//
		if ( x < scWidth-1)
		{
			pixels[ ( y+1 ) *scWidth+x+1] += color[3];
			pixel_count[ ( y+1 ) *scWidth+x+1] += weight[3];
		}
	}

// 	pixels[y*scWidth+x] += a_color;
// 	pixel_count[y*scWidth+x] += 1;
}
