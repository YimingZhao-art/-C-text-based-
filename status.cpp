#include <iostream>

using namespace std;
//A function return whether an element in an array
bool Check(int hand[],int number)
{
	for ( int i= 0; i < 5; i++ )
		if ( hand[i] == number )
		return true;
	return false;
}



// whether have the same number but 4 kind
bool IsFourOfAKind(int hand[])
{
	for ( int i= 0; i < 5; i++ )
		{
			if ( Check(hand,hand[i]+13) && Check(hand,hand[i]+26) && Check(hand,hand[i]+39)  )
				return true;
		}
	return false;
}

// whether have 3 same number and a pair
bool IsFullHouse(int hand[])
{
	for ( int i = 0; i < 5; i++ )
		{
			if ( (Check(hand,hand[i]+13) && Check(hand,hand[i]+26)) || (Check(hand,hand[i]+13) && Check(hand,hand[i]+39)) || (Check(hand,hand[i]+39) && Check(hand,hand[i]+26)) )
				//three kind
			{
				for ( int j = 0; j < 5; j++)
					{
						if ( hand[j] == hand[i] || hand[j] == hand[i] + 13 || hand[j] == hand[i] + 26 || hand[j] == hand[i] + 39 )
							continue;
						else if ( (Check(hand, hand[j] + 26)) || (Check(hand, hand[j] + 13)) || (Check(hand, hand[j] + 39)) )
							return true;
					}
			}
		}
	return false;
}

//whether is flush
bool IsFlush(int hand[])
{
	int card[5];
	for ( int i = 0; i < 5; i++ )
		{
			int b = ( hand[i] ) / 13;
			card[i] = b;
			if ( i == 0)
				continue;
			else if ( b != card[i-1]) 
				return false;
		}
	return true;
}

//whether is 3 of kind
bool IsThreeOfAKind(int hand[])
{
	for ( int i = 0; i < 5; i++ )
		{
			if ( (Check(hand,hand[i]+13) && Check(hand,hand[i]+26)) || (Check(hand,hand[i]+13) && Check(hand,hand[i]+39)) || (Check(hand,hand[i]+39) && Check(hand,hand[i]+26)) )
				return true;
		}
	return false;
}

//whether have two pairs
bool IsTwoPair(int hand[])
{
	for ( int i = 0; i < 5; i++ )
		{
			if ( Check(hand,hand[i]+13)  ||  Check(hand,hand[i]+39) ||  Check(hand,hand[i]+26) )
				{
					for ( int j = 0; j < 5; j++)
						{
							if ( hand[j] == hand[i] || hand[j] == hand[i] + 13 || hand[j] == hand[i] + 26 || hand[j] == hand[i] + 39 )
								continue;
							else if ( (Check(hand, hand[j]+ 26)) || (Check(hand, hand[j] + 13)) || (Check(hand, hand[j] + 39)) )
								return true;
						}
				}
		}
	return false;
}

//whether have a pair
bool IsOnePair(int hand[])
{
	for ( int i = 0; i < 5; i++ )
		{
			if ( Check(hand,hand[i]+13)  ||  Check(hand,hand[i]+39) ||  Check(hand,hand[i]+26) )
				{
					return true;
				}
		}
	return false;
}


int Status(int hand[]){
	if ( IsFourOfAKind(hand) )
		return 6;
	else if ( IsFullHouse(hand) )
		return 5;
	else if ( IsFlush(hand) )
		return 4;
	else if ( IsThreeOfAKind(hand) )
		return 3;
	else if ( IsTwoPair(hand) )
		return 2;
	else if ( IsOnePair(hand) )
		return 1;
	else
		return 0;
}


