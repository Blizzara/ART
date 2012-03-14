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
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef WRITE_H
#define WRITE_H

#include "Scene.h"
#include "Vector.h"

#include <pngwriter.h> // to be moved to Write.h
#include <iostream>

#include <ctime> // use timestamp to create unique filenames
#include <cstdio>


#include <sstream>

template <class T>
inline std::string ToString(const T& t) 
{
  std::stringstream ss;
  ss << t;
  return ss.str();
}

class Write
{
public:
	Write(int a_width, int a_height); //constructor, initializes file
	~Write(); //destructor, closes image

	int WritePixels(Scene& scene);	// writes image to file
	int Filename(std::string a_filename);
private:
	pngwriter image;
	int height;
	int width;
};


#endif // WRITE_H
