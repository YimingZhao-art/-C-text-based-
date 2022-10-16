#ifndef STATUS_H
#define STATUS_H

bool Check(int hand[],int number);

bool IsFourOfAKind(int hand[]); //*
bool IsFullHouse(int hand[]); //*
bool IsFlush(int hand[]);
bool IsThreeOfAKind(int hand[]); //*
bool IsTwoPair(int hand[]); //*
bool IsOnePair(int hand[]); //*

int Status(int hand[]);

#endif