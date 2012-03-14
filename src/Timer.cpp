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
#include "Timer.h"

Timer::Timer(std::string a_caller) : caller(a_caller)
{
  //otetaan aika, clock aloittaa laskun ohjelman k‰ynnistyksess‰ joten nykyinen aika pit‰‰ v‰hent‰‰ tuloksesta
	StartNew();
}


Timer::~Timer()
{
	std::cout << "Timer (" << caller << ") quitting: " << Elapsed(0) << " seconds elapsed since start." << std::endl;
}

double Timer::Elapsed(int i)
{
	clock_t after = clock();

// 	std::cout << "After: " << after << " atBeginning: " << atBeginning << " CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << std::endl;

	return (double)(after-timers.at(i))/CLOCKS_PER_SEC;
}

int Timer::StartNew()
{
	timers.push_back(clock());
	return timers.size()-1;
}

void Timer::StopLast()
{
	timers.pop_back();
}	

void Timer::SinceStart()
{
	std::cout << "Timer (" << caller << "): " << Elapsed(0) << " seconds elapsed since start." << std::endl;
}
