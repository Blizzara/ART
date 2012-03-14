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


#include "art.h"


int ART(Scene& scene)
{
	bool profiling = false;
	Timer timer("Main");

	int x,y;
	Color pixel;

	Write file(scene.Width(), scene.Height());
	
	SDLEngine sdl(scene.Width(), scene.Height());
	if(sdl.Status() == SDLENGINE_FAIL)
		return EXIT_FAILURE;

	RTEngine rt(scene);

	int time;
	double last_time=0, total_time =0;
	double last_rays=0, total_rays =0;

	std::cout << "Begin rendering" << std::endl;


	for(int iterations = 1;  !sdl.PollGetEscape() && (profiling == false || iterations <2); ++iterations)
	{
		time = timer.StartNew();
		for(last_rays = 0; ( !sdl.PollGetRefresh() && (last_time = timer.Elapsed(time)) < 2  /*&& last_rays < 500000*/); ++last_rays)
		{
			rt.Trace();
		}

		timer.StopLast();
		total_rays += last_rays;
		total_time += last_time;
		std::cout << iterations << "th iteration, shot " << last_rays << " rays, total " << total_rays << " rays shot, total time "<< total_time << " seconds" << std::endl;

		// Let's write the image and update screen! or just update
	
		for(x = 0; x < sdl.GetWidth(); x++)
		{
			for(y = 0; y < sdl.GetHeight(); y++)
			{
// 				std::cout << "Showing x:  "  << x << " and y: " << y << std::endl;
				pixel = scene.Pixel(x,y);
				sdl.SetPixel(x,y, (int)(pixel.x*255), (int)(pixel.y*255), (int)(pixel.z*255));
// 				image.plot(x,sdl.GetHeight()-y,pixel.x,pixel.y,pixel.z);
			}
		}
		sdl.UpdateSc();
	}				

	std::cout << "Total " << total_rays << " casted in " <<  total_time << " seconds, averaging to " << total_rays/total_time << " rays per second" << std::endl;

	
	file.WritePixels(scene);

// 	sdl.UpdateSc();

	timer.SinceStart();
	if (!profiling) sdl.Wait();
	
	return EXIT_SUCCESS;
}
