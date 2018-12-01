#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<string>
#include<map>
#include<algorithm>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifdef WIN32
#define python "py"
#elif __linux__
#define python "python3"
#endif
#define PORT 8888

using namespace std;

string def_dir("./CheckPoint/");
int enpass;
int board[8][8];
string brd("ZPPPPPPPPQRRBBKKZPPPPPPPPQRRBBKK");

int siner();
void disp_help();
int check_pos(vector<int>&, int, int);
int touch_pos(int, int);
void disp_brd();
string t_string(int);
int freak_counter(vector<string>&);
void make_server();

#include "peice.h"	//For the Base/Parent Class Peice
#include "zer0.h"	//For the derived/child Class Zero
#include "pawn.h"	//For the derived/child Class Pawn
#include "queen.h"	//For the derived/child Class Queen
#include "bishop.h"	//For the derived/child Class Bishop
#include "rook.h"	//For the derived/child Class Rook
#include "knight.h"	//For the derived/child Class Knight
#include "sock.h"	//For the Sock(socket) class

#include "game.h"	//For the main class which hanndels all the peices and the board

#include "glob.h"	//For the defination of Globaly declared function
