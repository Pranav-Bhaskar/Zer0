#include<iostream>
#include<vector>

using namespace std;

int board[8][8];
char brd[] = {'Z', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'Q', 'R', 'R', 'B', 'B', 'K', 'K'};

void disp_help();
int check_pos(vector<int>&, int, int);
void disp_brd();

#include "peice.h"	//For the Base/Parent Class Peice
#include "zer0.h"	//For the derived/child Class Zero
#include "pawn.h"	//For the derived/child Class Pawn
#include "queen.h"	//For the derived/child Class Queen
#include "bishop.h"	//For the derived/child Class Bishop
#include "rook.h"	//For the derived/child Class Rook
#include "knight.h"	//For the derived/child Class Knight

#include "game.h"	//For the main class which hanndels all the peices and the board

#include "glob.h"	//For the defination of Globaly declared function 