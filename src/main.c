/*
 ============================================================================
 Name        : main.c
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
 */

/* TODO
 *  - Develop some form of instructions page,
 *  - Give access to settings.
 *  - Add a way for players to quit whilst the game is running.
 *  - automatic game end when stalemate is inevitable.
 */

#include "ticTacToe.h"
#include <unistd.h>

#define RESET	0

#define WIN		4
#define STALE_MATE	5
#define UN_SPUN		3

#define RESET	0
#define INC	1
#define MINUS2	2

int main(void)
{
/*
 * Value 1 represents the initial condition, any subsequent calls to play() can
 * be made with other values, to enable the storing of variables between games
 * and also to permit the launching of different commands upon the games first
 * launch.
 */
	menu();
	play(1);
	return EXIT_SUCCESS;
}

void menu()
{
	int verif = 0;

	clearScreen();
	ticTacToe();
	sysOutMenu();

	while (!verif)
	{
		getchar();
		verif = setLevel(48);
	}
	resetMoves();
}

/*
 * Oh dear, what a mess this function turned into, hmm ... One of those
 * 'things to do' that you keep ignoring, the tangled mess that is the
 * beginning of this program, bears witness to code which has yet to come; that
 * is my excuse, if you are buying.
 */
void play(int firstRun)
{
	int choice;
	int coin;
	int winner;
	int status;
	int stale_mate = 0;
	winner = 0;
	coin = 3;

	while(!winner)
	{
		while (firstRun)
		{
/*
 * updateGame refreshes the graphical display, the int entered represents the
 * player, 1 for player 1 and 2 for player 2, 0 initiates a total reset.
 */
			updateGame(RESET);
/*
 * keepCount is used to inform the computer how many moves remain, this function
 * has several uses, each defined by the integer value entered.
 *
 * 0 -> return count
 * 1 -> count
 * 2 -> reset
 */
			keepCount(RESET);

			firstRun = 0;
			if (coin == UN_SPUN) {
				choice = headsOrTails();
			}
			coin = coinToss(2);

			if (choice != coin)
			{
				player2WinsToss(PLAYER2);
				break;
			}

			playet1WinsTheToss(PLAYER1);

			if (coin)
				coin = 0;
			else
				coin = 1;
		}

		status = yourMove(PLAYER1);
		if(status == WIN) {
/*
 * This function is found at the end of draw.c, it is simply a text output to
 * screen, the first int defines the situation and the second the player, 0
 * being anyone and 1 and 2, player one and two consecutively.
 */
			// You win (text out).
			sysOut(0, 0);
			keepScore(PLAYER1, INC);
			keepScore(PLAYER2, RESET);
			winner = 1;
		} else
			if (status == STALE_MATE)
				stale_mate = 1;

		if(!winner && !stale_mate)
			status = computerMove(PLAYER2);

		stale_mate = 0;

		if(status == WIN && !winner) {
			//updateGame(WIN);
			// I win.
			sysOut(1, 0);
			keepScore(PLAYER2, INC);
			keepScore(PLAYER1, RESET);
			winner = 1;
		}

		if (status == STALE_MATE) {
			updateGame(PLAYER1);
			// Stale-mate
			sysOut(2, 0);
			keepScore(PLAYER1, MINUS2);
			keepScore(PLAYER2, MINUS2);
			winner = 1;
		}


		if(winner)
		{
			winner = 0;
			firstRun = 1;
			winningLine();
			sleep(2);
		}
	}
}
