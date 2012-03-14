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
#ifndef TEXTURE_H
#define TEXTURE_H

/**
	@author Arttu Voutilainen <blizzara@zbxt.net>
*/

#include "Vector.h"

class Texture{
public:
//     Texture();
    ~Texture();

	Texture(Color a_color = Color(0.5,0.5,0.5), double a_ambient = 0, double a_diffuse = 0.6, double a_specular = 0, double a_reflection = 0, double a_transmit = 0) : color(a_color), ambient(a_ambient), diffuse(a_diffuse), specular(a_specular), reflection(a_reflection), transmit(a_transmit) {};

	Color GetColor() { return color; };
	double GetDiffuse() { return diffuse; };
	double GetSpecular() { return specular; };
	double GetReflection() { return reflection; };
	double GetTransmit() { return transmit; };

	double GetAmbient() { return ambient; };
    void GetRefraction();

private:
	Color color;
	double ambient;
	double diffuse;
	double specular;
	double reflection;
	double transmit;
};

#endif
