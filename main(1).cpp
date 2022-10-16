//Fight Landlord

//52 + 2
//random mess up the array and attribute



#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <map>

#include "status.h"
#include "initial.h"

#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

using namespace std;

int Poker[54];


void PrintHand(int hand[]); // print


/*
0 others
1 onepair
2 twopair
3 three
4 flush
5 full house
6 four
*/


int main() {
	setPoker(Poker);
	int * Player, * C1, * C2;
	int n1, n2, n3;
	landlord(n1, n2, n3);
	Player = new int [n1], C1 = new int [n2], C2 = new int [n3];
	DealHand(Player, Poker, 0, n1);
	DealHand(C1, Poker, n1, n2+n1);
	DealHand(C2, Poker, n2+n1, n3);
}













