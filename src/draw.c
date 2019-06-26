/*
 ============================================================================
 Name        : draw.c
 Author      : Iain Hill
 Version     : 1
 Copyright   : GPL

 Description : naughts and crosses / tic tac toe

    Copyright (C) 2017 Iain Hill. 

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ============================================================================
     _   _     _____         _____           
    | |_(_) __|_   _|_ _  __|_   _|__   ___  
    | __| |/ __|| |/ _` |/ __|| |/ _ \ / _ \
    | |_| | (__ | | (_| | (__ | | (_) |  __/ 
     \__|_|\___||_|\__,_|\___||_|\___/ \___| 
    
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "ticTacToe.h"

/*
 * The heading what!
 */
void ticTacToe()
{
	puts(" _   _     _____         _____ ");
	puts("| |_(_) __|_   _|_ _  __|_   _|__   ___");
	puts("| __| |/ __|| |/ _` |/ __|| |/ _ \\ / _ \\");
	puts("| |_| | (__ | | (_| | (__ | | (_) |  __/ ");
	puts(" \\__|_|\\___||_|\\__,_|\\___||_|\\___/ \\___|");
	puts("\n");
}

/*
 * For those of you with high high-definition wide screen TVs, here it is, the
 * big screen ...
 */
static int bigScreen[19][80] =
{//           0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31   32   33   34   35   36   37   38   39    40    41   42   43   44   45    46   47   48   49   50    51   52   53   54   55    56   57   58   59   60    61   62   63   64   65    66   67   68   69   70    71   72   73   74   75    76   77   78   79   
/* 0	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', 'b', ' ', ' ', ' ', ' ', ' ', '_', ' ', ' ', ' ', ' ', 'c', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 80	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 160	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 240	*/ { ' ', ' ', '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 320	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 400	*/ { ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 480	*/ { ' ', ' ', ' ', ' ', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 560	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 640	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 720	*/ { ' ', ' ', '2', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 800	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 880	*/ { ' ', ' ', ' ', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 960	*/ { ' ', ' ', ' ', ' ', ' ', '|', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', ' ', ' ', ' ', '_', '_', '_', '_', '_', '_', '_', '_', '|', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 1040	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 1120	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 1200	*/ { ' ', ' ', '3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 1280	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 1360	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', '_', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  },
/* 1440	*/ { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' '  }
};

/*
 * For us lesser mortals, the grid quoi ...
 */
static int grid[6][13] =
{
	{ '\t', ' ', ' ', 'a', ' ', ' ', ' ', 'b', ' ', ' ', ' ', 'c', ' ' },
	{ '\t', '1', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '2', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' },
	{ '\t', ' ', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
	{ '\t', '3', ' ', ' ', ' ', '|', ' ', ' ', ' ', '|', ' ', ' ', ' ' }
};

/*
 * The game glyphs, naughts and crosses ...
 */
static int glyphX[4][7] =
{
	{ ' ', '_', '_', ' ', ' ', '_', '_'  },
	{ ' ', '\\',' ', '\\','/', ' ', '/'  },
	{ ' ', ' ', '>', ' ', ' ', '<', ' '  },
	{ ' ', '/', '_', '/', '\\','_', '\\' }
};

static int glyphO[4][7] =
{
	{ ' ', ' ', '_', '_', '_', ' ', ' ', },
	{ ' ', '/', ' ', '_', ' ', '\\',' ', },
	{ '|', ' ', '(', '_', ')', ' ', '|', },
	{ ' ', '\\','_', '_', '_', '/', ' ', }
};

static int glyphBlank[4][7] =
{
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', }
};

/*
 * Translates the stored moves recorded in the moves array in the file logic.c,
 * into the values displayed on screen in both the grid arrays, found above.
 */
void writeMoves(int *moves)
{
	/*
	 * Map the 3*3 grid into the corresponding display, no fancy math here
	 * just plain hard coded coordinates.
	 */
	int map1[9] = { 16, 20, 24, 42, 46, 50, 68, 72, 76 };
	int map2[9] = { 86, 97,108, 566, 577, 588, 1046, 1057, 1068 };

	for (int i = 0; i < 9; i++) {

		if (*(moves+i) == 1)
		{
			*(*grid+*(map1+i)) = 'O';
			writeGlyphToGrid(*glyphO, *(map2+i));
		}
		else if (*(moves+i) == 2)
		{
			*(*grid+*(map1+i)) = 'X';
			writeGlyphToGrid(*glyphX, *(map2+i));
		}
		else if (*(moves+i) == 0)
		{
			*(*grid+*(map1+i)) = ' ';
			writeGlyphToGrid(*glyphBlank, *(map2+i));
		}
	}
}

/*
 * Map the required glyph array onto the main grid array.
 */
void writeGlyphToGrid(int* glyph, int j)
{
	// Scroll through the glyph.
	for (int i = 0; i < 28; i++)
	{
		// If i is divisible exactly by 7, go to the next row.
		if (i % 7 == 0 && i != 0) {
			j = j + 73;
		}
		*(*bigScreen+j) = *(glyph+i);
		j++;
	}
}

/*
 * Keep score of wins aside the board.
 */
void scoreBarCharts(int score1, int score2)
{
	int bar1 = 1482;
	int bar2 = bar1 + 6;
	int max = 17;

	*(*bigScreen+bar1) 	= 'P';
	*(*bigScreen+bar1+1) 	= '1';
	*(*bigScreen+bar2) 	= 'P';
	*(*bigScreen+bar2+1) 	= '2';

	/* Clear */
	for (int i = 0; i <= max && score1 <= max; i++) {
		*(*bigScreen+bar1 - ((80*i)+1))		= ' ';
		*(*bigScreen+bar1 - ((80*i)-2))		= ' ';
		*(*bigScreen+bar1 - (80*(i+1)))		= ' ';
		*(*bigScreen+bar1 - (80*(i+1))+1)	= ' ';
	}

	for (int i = 0; i <= max && score2 <= max; i++) {
		*(*bigScreen+bar2 - ((80*i)+1))		= ' ';
		*(*bigScreen+bar2 - ((80*i)-2))		= ' ';
		*(*bigScreen+bar2 - (80*(i+1)))		= ' ';
		*(*bigScreen+bar2 - (80*(i+1))+1)	= ' ';
	}

	/* Draw */
	for (int i = 1; i <= score1 && score1 <= max; i++) {
		*(*bigScreen+bar1 - ((80*i)+1))		= '|';
		*(*bigScreen+bar1 - ((80*i)-2))		= '|';
	}
	*(*bigScreen+bar1 - ((80*(score1+1)) ))		= '_';
	*(*bigScreen+bar1 - ((80*(score1+1))-1))	= '_';

	for (int i = 1; i <= score2  && score2 <= max; i++) {
		*(*bigScreen+bar2 - ((80*i)+1))		= '|';
		*(*bigScreen+bar2 - ((80*i)-2))		= '|';
	}
	*(*bigScreen+bar2 - ((80*(score2+1)) ))		= '_';
	*(*bigScreen+bar2 - ((80*(score2+1))-1))	= '_';
}

/*
 * Scribe a line across the grid over the winning pieces.
 */
void drawWinningLine(int line)
{
	int lenVerti = 17;
	int lenHoriz = 32;
	int lenDiag = 15;
	int startPoint;
	unsigned int delay = 30000;

	switch(line)
	{
		case 1: startPoint = 244;
			break;
		case 2: startPoint = 724;
			break;
		case 3: startPoint = 1204;
			break;
		case 4: startPoint = 166;
			break;
		case 5: startPoint = 1370;
			break;
		case 6: startPoint = 1380;
			break;
		case 7: startPoint = 1391;
			break;
		case 8: startPoint = 1287;
			break;
	}

	usleep(delay);
	if (line > 0 && line < 4)
	{
		for (int i = 0; i < lenHoriz; i++) {
			*(*bigScreen+startPoint+i+1) = '-';
			usleep(delay);
			drawGrid();
		}
	}
	else if (line == 4)
	{
		for (int i = 0; i < lenDiag; i++) {
			*(*bigScreen+startPoint+(80*i)+(i*2)) = '\\';
			usleep(delay);
			drawGrid();
		}
	}
	else if (line > 4 && line < 8)
	{
		for (int i = 0; i < lenVerti; i++) {
			*(*bigScreen+startPoint-(80*i)) = '|';
			usleep(delay);
			drawGrid();
		}
	}
	else if (line == 8)
	{
		for (int i = 0; i < lenDiag; i++) {
			*(*bigScreen+startPoint-(80*i)+(i*2)) = '/';
			usleep(delay);
			drawGrid();
		}
	}
}

/*
 * Write the grid array to screen.
 */
void drawGrid()
{
	int max;

	max = clearScreen();
	ticTacToe();

	if (DEBUG)
		printDebugMoves();

	if (max > 22) {
		for (int i = 0; i < 19; i++) {
			for (int j = 0; j < 80; j++)
				printf("%c",bigScreen[i][j]);
			puts("");
		}
	} else {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 13; j++)
				printf("%c",grid[i][j]);
			puts("");
		}
	}
	puts("\n");
}

/*
 * Clean up the grid after a win 'crossing out' line has been drawn.
 */
void redrawGrid(int line)
{
	// The major axis.
	int one   = 240;
	int two   = 720;
	int three = 1200;

	int five  = 10;
	int six   = 20;
	int seven = 31;

	switch(line)
	{
		case 1:
			*(*bigScreen+one+5 ) = ' ';
			*(*bigScreen+one+13) = ' ';
			*(*bigScreen+one+14) = '|';
			*(*bigScreen+one+15) = ' ';
			*(*bigScreen+one+16) = '|';
			*(*bigScreen+one+24) = ' ';
			*(*bigScreen+one+25) = '|';
			*(*bigScreen+one+26) = ' ';
			*(*bigScreen+one+27) = '|';
			*(*bigScreen+one+35) = ' ';
			*(*bigScreen+one+36) = ' ';
			break;
		case 2:
			*(*bigScreen+two+5 ) = ' ';
			*(*bigScreen+two+13) = ' ';
			*(*bigScreen+two+14) = '|';
			*(*bigScreen+two+15) = ' ';
			*(*bigScreen+two+16) = '|';
			*(*bigScreen+two+24) = ' ';
			*(*bigScreen+two+25) = '|';
			*(*bigScreen+two+26) = ' ';
			*(*bigScreen+two+27) = '|';
			*(*bigScreen+two+35) = ' ';
			*(*bigScreen+two+36) = ' ';
			break;
		case 3:
			*(*bigScreen+three+5 ) = ' ';
			*(*bigScreen+three+13) = ' ';
			*(*bigScreen+three+14) = '|';
			*(*bigScreen+three+15) = ' ';
			*(*bigScreen+three+16) = '|';
			*(*bigScreen+three+24) = ' ';
			*(*bigScreen+three+25) = '|';
			*(*bigScreen+three+26) = ' ';
			*(*bigScreen+three+27) = '|';
			*(*bigScreen+three+35) = ' ';
			*(*bigScreen+three+36) = ' ';
			break;
		case 4:
			*(*bigScreen+400 +12) = '_';
			*(*bigScreen+480 +14) = ' ';
			*(*bigScreen+560 +16) = '|';
			*(*bigScreen+880 +24) = '_';
			*(*bigScreen+960 +26) = ' ';
			*(*bigScreen+1360+28) = ' ';
			break;
		case 5:
			*(*bigScreen+five+400 ) = '_';
			*(*bigScreen+five+480 ) = '_';
			*(*bigScreen+five+880 ) = '_';
			*(*bigScreen+five+960 ) = '_';
			*(*bigScreen+five+1360) = ' ';
			break;
		case 6:
			*(*bigScreen+six+400 ) = '_';
			*(*bigScreen+six+480 ) = '_';
			*(*bigScreen+six+880 ) = '_';
			*(*bigScreen+six+960 ) = '_';
			*(*bigScreen+six+1360) = ' ';
			break;
		case 7:
			*(*bigScreen+seven+400 ) = '_';
			*(*bigScreen+seven+480 ) = '_';
			*(*bigScreen+seven+880 ) = '_';
			*(*bigScreen+seven+960 ) = '_';
			*(*bigScreen+seven+1360) = ' ';
			break;
		case 8:
			*(*bigScreen+160 +35) = ' ';
			*(*bigScreen+400 +29) = '_';
			*(*bigScreen+480 +27) = ' ';
			*(*bigScreen+560 +25) = '|';
			*(*bigScreen+880 +17) = '_';
			*(*bigScreen+960 +15) = ' ';
			*(*bigScreen+1040+13) = ' ';
			break;
		default:
			break;
	}
}

/*
 * As its name suggests, this function clears the screen between player moves.
 */
int clearScreen()
{
	struct winsize max;
	ioctl(0, TIOCGWINSZ , &max);
	puts("\033[H\033[J");	/* Clear screen */
	return max.ws_row;
}

/*
 * The start menu.
 */
void sysOutMenu()
{
	puts("Welcome to the pro ticTacToe league and congratulations on making");
	puts("it this far ... Not many would have bothered.");
	puts("\n");
	puts("\tTo be or not to be, that is the question; ...");
	puts("");
	puts("	~~~ Press enter to start ~~~");
	puts("\n\n\n\n\n\n");
}

/*
 * The wordy part; This function sends all of the programs text phrases out
 * into the world, well to the screen at least, and believe it or not, just at
 * the appropriate moment. Be warned, at times creating the illusion of an
 * opponent, when there is really no one there. That is, other than the poor
 * NSA operative, who has had the misfortune of being assigned to your sad
 * deluded arse. Clever stuff this programming thingy; Could get your self in
 * to hot water with it I am sure; It really is that civilised.
 */
void sysOut(int write, int player) {
/*
 * If player is > 0 then -1; Corrects the value of 'player' for use in the
 * printf statement, that is, when the output is player dependant. 
 */
	if (player) player = player - 1;

	char* text[9] = {
		"Congratulations, you are the winner!",			// 0
		"I am the winner, better luck next time ...",		// 1
		"Stale-mate, nobody wins ...",				// 2
		"Would you like to play again? y/n or m for menu: ",	// 3
		"Please choose, heads or tails 'h' or 't' ? ",		// 4
		"You have won the toss. ",				// 5
		"I have won the toss. ",				// 6
		"It is your move ...  ",				// 7
		"My turn, now then, let me see ..."			// 8
	};

	printf("%s", text[ write + (player) ]);
}
