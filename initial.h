#include <iostream>
#include <map>

using namespace std;

#ifndef INITIAL_H
#define INITIAL_H

void setPoker(int Poker[]);
void swap(int * a, int * b);
void DealHand(int * Player, int Poker[], int i, int j); // set the hand
void landlord(int &n1, int &n2, int &n3);

map<int, int> change(int * Player, int size);

#endif