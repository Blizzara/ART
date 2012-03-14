/*
    Copyright (c) <year> <copyright holders>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "Write.h"


Write::Write(int a_width, int a_height)
{
	std::string filename("out-");
	filename += ToString(time(NULL));	// give each file timestamp so don't need to overwrite
	filename += ".png";			
	height = a_height;
	width = a_width;
	image.resize(width, height);
	image.pngwriter_rename(filename.c_str());
}

int Write::Filename(std::string a_filename)
{
	image.pngwriter_rename(a_filename.c_str());
	return true;
}


Write::~Write()
{
	image.close();
}


int Write::WritePixels(Scene& scene)
{

	Vector pixel;
	
  // Let's write the image!
	std::cout << "Writing image to disk.. ";

	for(int x = 0; x < width; x++)
	{
		for(int y = 0; y < height; y++)
		{
			pixel = scene.Pixel(x,y);
			image.plot(x,height-y,pixel.x,pixel.y,pixel.z);
		}
	}
	image.close();
	std::cout << "Image writing completed!" << std::endl;
	return true;
}
