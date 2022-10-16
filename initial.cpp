#include <iostream>
#include <map>

using namespace std;

void swap(int * a, int * b){
	int * p;
	*p = *a;
	*a = *b;
	*b = * p;
}


void setPoker(int Poker[]){
	for ( int i = 0; i < 52; i++ )
		Poker[i] = i;
	srand( time( NULL ) );
	
	Poker[52] = 100; // big joker
	Poker[53] = 101; // small joker
	
	for ( int i = 0; i < 54; i++ ){
		int j = rand() % 54;
		while ( j == i ) j = rand() % 54;
		swap( &(Poker[i]), &(Poker[j]) );
	}
}

void DealHand(int * Player, int Poker[], int i, int size){
	for ( int n = 0; n < size - i; n++ ){
		Player[n] = Poker[i+n];
	}
}


void landlord(int &n1, int &n2, int &n3) {
	srand( time( NULL ) );
	int n = rand() % 3 + 1;
	if ( n == 1 ) {
		n1 = 20, n2 = 17, n3 = 17;
		cout << "You are the landlord" << endl;
	}
	else if ( n == 2) {
		n1 = 17, n2 = 20, n3 = 17;
		printf("Computer%d is the landlord.\n",n);
	}
	
	else {
		n1 = 17; n2 = 17; n3 = 20;
		printf("Computer%d is the landlord.\n",n);
	}
}


map<int, int> change(int * Player, int size){
	map<int,int> a;
	for ( int i = 0; i < size; i++ ){
		int number = Player[i] % 13 + 1;
		int card = 52 / Player[i] + 1;
		a[number] = card;
	}
	return a;
}