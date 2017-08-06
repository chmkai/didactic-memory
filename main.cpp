/*	Cellular Automata Implementations -  Game of Life + Others
 *  Copyright (c) 2017 Anand Menon
 *
 *  This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cstdint>
#include <array>
#include <unistd.h>

#include "gol.h"
#include "globals.h"

uint8_t birthCondition;
std::array<uint8_t, 9> survivalCondition = {0,0,0,0,0,0,0,0};

const std::string Version = "0.2.1 Alpha";

int main()
{
	std::cout
		<< "------------------------------------------------\n"
	 	<< "Cellular Automata Implementations (GoL + others)\n"
		<< "Copyright (c) 2017 Anand Menon\n"
		<< "------------------------------------------------\n\n"
		<< "Version " << Version << "\n\n"
		<< "This program comes with ABSOLUTELY NO WARRANTY.\n"
		<< "This is free software, and you are welcome to redistribute\n"
		<< "it under certain conditions. To view the full text \n"
		<< "of the GNU GPL Licence, Press `Shift+C`.\n\n"
		<< "How to use: \n"
		<< "\tSpacebar to start/pause the simulation.\n"
		<< "\tArrow keys to move the cursor\n"
		<< "\t\'s\' to toggle cell at cursor\n"
		<< "\t\'c\' to clear the grid\n\n";
	birthCondition = 2;
	survivalCondition = {2,3};
	usleep(5000000);
	_gol();
}
