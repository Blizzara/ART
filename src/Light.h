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
#ifndef LIGHT_H
#define LIGHT_H

/**
	@author Arttu Voutilainen <blizzara@blizzard>
*/

#include "Vector.h"
#include "Ray.h"

class Light{
public:
	Light();
	Light(Vector location, Color color) : loc(location), col(color) { };

	~Light();

	Vector GetLoc() { return loc; };
	Color GetColor() { return col; };

	double Intersect(Ray ray);

private:
	Vector loc;
	Color col;
};

#endif
