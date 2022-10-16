#include <iostream>
#include <vector>
using namespace std;

void sort(vector<int> &POKER); //理牌


//组合
int HAND(vector<int> hand);

vector<int> count(vector<int> hand);
vector<int> initial(vector<int> hand);
int in(vector<int> hand, int n);

bool isJ(vector<int> hand); //王炸 2 √               999
bool is4(vector<int> hand); //炸 4 √	                100
bool is4_2_2(vector<int> hand); //四带两对 8 √       	1
bool is4_1_1(vector<int> hand); //四带二 6 √        	2
bool is3(vector<int> hand); //三张 3 √              	3
bool is3_2(vector<int> hand); //三带二 5 √			4
bool is3_1(vector<int> hand); //三带一 4 √			5
bool is2(vector<int> hand); //一对 2 √				6
bool isFlash1(vector<int> hand); //一顺 >= 5 √		7
bool isFlash2(vector<int> hand); //两顺 >= 6 √		8
bool isPlane1(vector<int> hand); //二飞机带两单牌 8 √	9
bool isPlane2(vector<int> hand); //二飞机带两对牌 10 √	10
bool isPlane3(vector<int> hand); //三飞机带三单牌 12 √	11
bool isPlane4(vector<int> hand); //三飞机带三对牌 15 √	12
bool isPlane5(vector<int> hand); //四飞机带四张牌 16 √	13
bool isPlane6(vector<int> hand); //四飞机带四对牌 20 √	14
bool isPlane7(vector<int> hand); //五飞机带五张牌 20 √	15

int main(int argc, char *argv[]) {
	vector<int> hand = {3,3,3,4,4,4,8,9};
	sort(hand);
	cout << isPlane1(hand);
}

int HAND(vector<int> hand){
	int x = hand.size();
	if ( x == 1 )
		return 0;
	if ( x < 5 ){
		if ( isJ(hand) )
			return 999;
		if ( is4(hand) )
			return 100;
		if ( is3(hand) )
			return 3;
		if ( is3_1(hand) )
			return 5;
		if ( is2(hand) )
			return 6;
	}
	else if ( x < 10 ){
		if ( is3_2(hand) )
			return 4;
		if ( is4_2_2(hand) )
			return 1;
		if ( is4_1_1(hand) )
			return 2;
		if ( isFlash1(hand) )
			return 7;
		if ( isFlash2(hand) )
			return 8;
		if ( isPlane1(hand) )
			return 9;
	}
	else {
		if ( isFlash1(hand) )
			return 7;
		if ( isFlash2(hand) )
			return 8;
		if ( isPlane2(hand) )
			return 10;
		if ( isPlane3(hand) )
			return 11;
		if ( isPlane4(hand) )
			return 12;
		if ( isPlane5(hand) )
			return 13;
		if ( isPlane6(hand) )
			return 14;
		if ( isPlane7(hand) )
			return 15;
	}
	return 0;
}








vector<int> initial(vector<int> hand){
	vector<int> x;
	for ( int i = 0; i < hand.size(); i++ )
		x.push_back( hand[i] % 100 );
	return x;
}

void sort(vector<int> &POKER){
	for ( int i = 0; i < POKER.size(); i++ ){
		int min = POKER[i] % 100, idx = i;
		for ( int j = i + 1; j < POKER.size(); j++ ){
			if ( min > POKER[j] % 100 ){
				min = POKER[j] % 100;
				idx = j;
			}
		}
		swap(POKER[i],POKER[idx]);
	}
}

int in(vector<int> hand, int n){
	int c = 0;
	for ( int i = 0; i < hand.size(); i++ )
		if ( hand[i] == n )
			c++;
	return c;
}


vector<int> count(vector<int> hand){
	vector<int> counter;
	vector<int> x;
	vector<int> nv;
	x = initial(hand);
	for ( int i = 0; i < x.size(); i++ ){
		if ( !in(nv,x[i]) )
			nv.push_back(x[i]);
	}
	for ( int i = 0; i < nv.size(); i++ ){
		counter.push_back(in(x,nv[i]));
	}
	sort(counter); //small small lare
	return counter;
}

bool isJ(vector<int> hand){
	if ( hand.size() == 2 ){
		if ( hand [0] == 998 && hand[1] == 999 )
			return true;
	}
	return false;
}

bool is4(vector<int> hand){
	if ( hand.size() == 4 ){
		if ( count(hand).size() == 1 ){
			return true;
		}
	}
	return false;
}

bool is4_2_2(vector<int> hand){
	if ( hand.size() == 8 ){
		if ( count(hand).size() == 3 && count(hand)[1] == 2 )
			return true;
	}
	return false;
}

bool is4_1_1(vector<int> hand){
	if ( hand.size() == 6 ){
		if ( count(hand).size() == 3 && count(hand)[2] == 4 )
			return true;
	}
	return false;
}

bool is3(vector<int> hand){
	if ( hand.size() == 3 ){
		if ( count(hand).size() == 1 ){
			return true;
		}
	}
	return false;
}

bool is3_2(vector<int> hand){
	if ( hand.size() == 5 ){
		if ( count(hand).size() == 2 && count(hand)[1] == 3 )
			return true;
	}
	return false;
}

bool is3_1(vector<int> hand){
	if ( hand.size() == 4 ){
		if ( count(hand).size() == 2 && count(hand)[1] == 3)
			return true;
	}
	return false;
}


bool is2(vector<int> hand){
	if ( hand.size() == 2 ){
		if ( count(hand).size() == 1 ){
			return true;
		}
	}
	return false;
}

bool isFlash1(vector<int> hand){
	if ( 1 ){
		vector<int> x = initial(hand);
		if ( count(hand).size() == hand.size() ){
			int n = hand.size();
			for ( int i = 1; i < n; i++ ){
				if ( x[i] - x[0] != i )
					return false;
			}
			return true;
		}
	}
	return false;
}

bool isFlash2(vector<int> hand){
	if ( hand.size() >= 6 ){
		vector<int> x = count(hand);
		if ( x.size() == hand.size() / 2 ){
			for ( int i = 0; i < x.size(); i++ )
				if ( x[i] != 2 )
					return false;
			vector<int> v = initial(hand);
			vector<int> nv;
			for ( int i = 0; i < v.size(); i += 2 ){
				nv.push_back(v[i]);
			}
			if ( isFlash1(nv) )
				return true;
		}
	}
	return false;
}

bool isPlane1(vector<int> hand){
	if ( hand.size() == 8 ){
		vector<int> x = count(hand);
		if ( x.size() == 4 ){
			if ( x[2] == 3 && x[3] == 3 ){
				vector<int> nv;
				for ( int i = 0; i < hand.size(); i++ )
					if ( in(hand,hand[i]) == 3 )
						if ( in(nv,hand[i]) == 0 )
							nv.push_back(hand[i]);
				if ( isFlash1(nv) )
					return true;
			}
		}
	}
	return false;
}

bool isPlane2(vector<int> hand){
	if ( hand.size() == 10 ){
		vector<int> x = count(hand);
		if ( x.size() == 4 ){
			if ( x[2] == 3 && x[3] == 3 && x[1] == 2 ){
				vector<int> nv;
				for ( int i = 0; i < hand.size(); i++ )
					if ( in(hand,hand[i]) == 3 )
						if ( in(nv,hand[i]) == 0 )
							nv.push_back(hand[i]);
				if ( isFlash1(nv) )
					return true;
			}
		}
	}
	return false;
}


bool isPlane3(vector<int> hand){
	if ( hand.size() == 12 ){
		vector<int> x = count(hand);
		if ( x.size() == 6 ){
			if ( x[5] == x[4] && x[4] == x[3] && x[3] == 3 ){
				vector<int> nv;
				for ( int i = 0; i < hand.size(); i++ )
					if ( in(hand,hand[i]) == 3 )
						if ( in(nv,hand[i]) == 0 )
							nv.push_back(hand[i]);
				if ( isFlash1(nv) )
					return true;
			}
		}
	}
	return  false;
}

bool isPlane4(vector<int> hand){
	if ( hand.size() == 15 ){
		vector<int> x = count(hand);
		if ( x.size() == 6 ){
			if ( x[5] == x[4] && x[4] == x[3] && x[3] == 3 && x[2] == 2 && x[1] == 2){
				vector<int> nv;
				for ( int i = 0; i < hand.size(); i++ )
					if ( in(hand,hand[i]) == 3 )
						if ( in(nv,hand[i]) == 0 )
					nv.push_back(hand[i]);
				if ( isFlash1(nv) )
					return true;
			}
		}
	}
	return  false;
}


bool isPlane5(vector<int> hand){
	if ( hand.size() == 16 ){
		vector<int> x = count(hand);
		if ( x.size() == 8 ){
			if ( x[7] == x[6] && x[6] == x[5] && x[5] == x[4] && x[4] == 3){
				vector<int> nv;
				for ( int i = 0; i < hand.size(); i++ )
					if ( in(hand,hand[i]) == 3 )
						if ( in(nv,hand[i]) == 0 )
					nv.push_back(hand[i]);
				if ( isFlash1(nv) )
					return true;
			}
		}
	}
	return  false;
}

bool isPlane6(vector<int> hand){
	if ( hand.size() == 20 ){
		vector<int> x = count(hand);
		if ( x.size() == 8 ){
			if ( x[7] == x[6] && x[6] == x[5] && x[5] == x[4] && x[4] == 3)
				if ( x[3] == x[2] && x[2] == x[1] && x[1] == 2 ){
					vector<int> nv;
					for ( int i = 0; i < hand.size(); i++ )
						if ( in(hand,hand[i]) == 3 )
							if ( in(nv,hand[i]) == 0 )
						nv.push_back(hand[i]);
					if ( isFlash1(nv) )
						return true;
				}
		}
	}
	return  false;

}

bool isPlane7(vector<int> hand){
	if ( hand.size() == 20 ){
		vector<int> x = count(hand);
		if ( x.size() == 10 ){
			if ( x[9] == 3 && x[8] == 3 && x[7] == 3 && x[6] == 3 && x[5] == 3 ){
					vector<int> nv;
					for ( int i = 0; i < hand.size(); i++ )
						if ( in(hand,hand[i]) == 3 )
							if ( in(nv,hand[i]) == 0 )
						nv.push_back(hand[i]);
					if ( isFlash1(nv) )
						return true;
				}
		}
	}
	return  false;
}