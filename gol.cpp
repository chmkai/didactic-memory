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

#include <fstream>
#include <ncurses.h>
#include <unistd.h>

#include "globals.h"
#include "gol.h"

bool current[24][80];
bool next[24][80];
MEVENT event;

void _gol()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	for(int i = 0; i < 24; i++)
		for(int j = 0; j < 80; j++)
		{
			current[i][j] = 0;
			next[i][j] = 0;
		}
	loop();
	endwin();
}

void loop()
{	int cur_x = 1;
	int cur_y = 1;
	int isPaused = true;
	do
	{
		clear();
		for(int i = 1; i < 23; i++)
			for(int j = 1; j < 79; j++)
			{
				if(current[i][j] == true)
				{
					attrset(((i == cur_y && j == cur_x) ?COLOR_PAIR(2) | A_BOLD:COLOR_PAIR(1)) | A_BOLD);
					mvaddch(i,j, '*');
				}
				else
				{
					attrset((i == cur_y && j == cur_x) ? COLOR_PAIR(2) | A_BOLD :A_NORMAL);
					mvaddch(i,j,((i == cur_y && j == cur_x) ? '^' :'-'));
				}
			}	// mvaddch(i,j, (current[i][j] == true ? '+' : '-'));
		usleep(100000); // sleep one second
		refresh();
		if(!isPaused)
		{
			for(int i = 1; i < 23; i++)
				for(int j = 1; j < 79; j++)
				{
					int surr = 0;
					if(current[i][j-1] == true) surr++;
					if(current[i][j+1] == true) surr++;
					if(current[i-1][j] == true) surr++;
					if(current[i+1][j] == true) surr++;
					if(current[i-1][j-1] == true) surr++;
					if(current[i+1][j+1] == true) surr++;
					if(current[i-1][j+1] == true) surr++;
					if(current[i+1][j-1] == true) surr++;
					if(surr == 2 || surr == 3)
						if(surr == 3)
							next[i][j] = true;
						else
							next[i][j] = current[i][j];
					else
						next[i][j] = 0;
				}
			for(int i = 1; i < 23; i++)
				for(int j = 1; j < 79; j++)
					current[i][j] = next[i][j];
		}
		switch(getch())
		{
			case KEY_UP:
				if(cur_y > 1)
					cur_y--;
				break;
			case KEY_DOWN:
				if(cur_y < 22)
					cur_y++;
				break;
			case KEY_LEFT:
				if(cur_x > 1)
					cur_x--;
				break;
			case KEY_RIGHT:
				if(cur_x < 78)
					cur_x++;
				break;
			case 's':
				current[cur_y][cur_x] = (current[cur_y][cur_x] == true ? false : true);
				break;
			case 'c':
				for(int i = 0; i < 24; i++)
					for(int j = 0; j < 80; j++)
					{
						current[i][j] = false;
						next[i][j] = false;
					}
				break;
			case 32:
				isPaused = (isPaused == true ? false : true);
				break;
			case 'C':
				viewLicense();
		}
	}while(getch() != 27);
}

void viewLicense()
{
	clear();
	char line[81];
	int lno = 1;
	std::ifstream LICENSE("LICENSE");
	do
	{
		LICENSE.getline(line, 80);
		if(lno < 23)
		{
			mvprintw(lno, 2, "%s\n", line);
			lno++;
		}
		else
		{
			while(getch() == ERR);
			clear();
			mvprintw(lno, 2, "%s\n" ,line);
			lno = 1;
		}
	}while(!LICENSE.eof());
	while(getch() == ERR);
	LICENSE.close();
	refresh();
}
