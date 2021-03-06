#include "./header/prog.h"

/*
		Important Notes
	*Some standard for the code;
	*The black will have side value as 1;
	*The white will have side value as 3;
	*The Black will be on the upper half of the board;
	*The white will be on the lower half of the board;
	*The empty spaces on the board will be represented by 0;
	*If the peice is no longer on the board the position of the peice sould be equal to -1;
	*The white peices will be represented by capital letters.
	*The black peices will be represented by small letters.
	Z -> ZER0;	(0)
	P -> PAWN;	(1 -> 8)
	K -> KNIGHT;	(14 -> 15)
	R -> ROOK;	(10 -> 11)
	Q -> QUEEN;	(9)
	B -> BISHOP;	(12 -> 13)


		Board For Reference
	+++++++++++++++++++++++++++++++++++++++++	-
	| 56 | 57 | 58 | 59 | 60 | 61 | 62 | 63 |	 |Black Side -> 1;
	+++++++++++++++++++++++++++++++++++++++++	 | 59 -> Queen ; 60 -> Zer0;
	| 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 |	-
	+++++++++++++++++++++++++++++++++++++++++
	| 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |
	+++++++++++++++++++++++++++++++++++++++++
	| 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |
	+++++++++++++++++++++++++++++++++++++++++
	| 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 |
	+++++++++++++++++++++++++++++++++++++++++
	| 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |
	+++++++++++++++++++++++++++++++++++++++++
	| 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 |	-
	+++++++++++++++++++++++++++++++++++++++++	 |White Side -> 3;
	| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  |	 | 3 -> Queen ; 4 -> Zer0;
	+++++++++++++++++++++++++++++++++++++++++	-
*/

int main (int argc, char const* argv[])
{
	Game g(((argc == 2) && !(strcmp(argv[1], "TRAIN"))) ? true : false);
	int r = g.begin();
	string s = python;
	s += string(" collector.py ");
	s += t_string(r);
	cout<<"\nCollecting data for training...";
	system(s.c_str());
	return 0;
}
