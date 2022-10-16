#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
using namespace std;

#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

vector<int> POKER; //扑克牌
vector<int> p1, p2, p3; //三个玩家

int n; //出牌人

struct doublelink{
	vector<int> p;
	doublelink * next;
};


int COUNT[15]={4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1}; //初始记牌器

string sets[] = { SPADE, CLUB, HEART, DIAMOND };
string numbers[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "joker", "JOKER" };

void linklist(doublelink * &head); //生成双向链表

void set_poker(vector<int> &POKER); //初始扑克牌
void swap(int * a, int * b); //交换数字
void shuffle(vector<int> &POKER); //洗牌
void distribute(vector<int> &p1, vector<int> &p2, vector<int> &p3); //发牌
int landlord(vector<int> &p1, vector<int> &p2, vector<int> &p3); //选择地主，并发牌

//出牌
void add(int n); //记牌器改变

//打印
void printself(vector<int> p1); //打印手牌
void sort(vector<int> &POKER); //理牌
void print(vector<int> hand); //牌与数字转换打印，包含在打印手牌中
void printcount(); //打印记牌器，包含在打印手牌中

int check(); //游戏是否结束
void play(); //回合








int main() {
	doublelink * head = NULL;
	
	
	cout << "You are p1.\n";
	set_poker(POKER); //设置扑克牌
	
	for ( int i = 0; i < 7; i++ )
		shuffle(POKER); //洗牌
	
	n = landlord(p1, p2, p3); //确认地主并发牌
	linklist(head); //形成双向链表，用来出牌，得保持更新
	for ( int i = 0; i < p1.size(); i++ )
		add(p1[i]); //记牌器初始化
	
	/*while ( !check()  ){ //没有人打完手牌
		//确定出牌人
		//选取牌
		//判断大小
		printself(p1);
		break;
	}*/
}


void set_poker(vector<int> &POKER){
	for ( int i = 1; i <= 4; i++ ){
		for ( int j = 1; j <= 13; j++ ){
			POKER.push_back( 100 * i + j);
		}
	}
	POKER.push_back(998); //small joker
	POKER.push_back(999); //big joker
}

void swap( int &a, int  &b ){
	int c = a;
	a = b;
	b = c;
}

void shuffle(vector<int> &POKER){
	for ( int i = 0; i < POKER.size(); i++ ){
		srand(time(NULL));
		for ( int j = 0; j < POKER.size(); j++ ){
			if ( j == i ) continue;
			if ( rand() % 2 == 0 ){
				swap( POKER[i], POKER[j] );
			}
		}
	}
}



void sort(vector<int> &POKER){
	for ( int i = 0; i < POKER.size(); i++ ){
		int max = POKER[i] % 100, idx = i;
		for ( int j = i + 1; j < POKER.size(); j++ ){
			if ( max > POKER[j] % 100 ){
				max = POKER[j] % 100;
				idx = j;
			}
		}
		swap(POKER[i],POKER[idx]);
	}
}


void distribute(vector<int> &p1, vector<int> &p2, vector<int> &p3){
	for ( int i = 0; i < 20; i++ )
		p1.push_back(POKER[i]);
	for ( int i = 20; i < 37; i++ )
		p2.push_back(POKER[i]);
	for ( int i = 37; i < 54; i++ )
		p3.push_back(POKER[i]);
}

int landlord(vector<int> &p1, vector<int> &p2, vector<int> &p3){
	vector<int> landlord;
	for ( int i = 0; i < 3; i++ )
		landlord.push_back(POKER[i]);
	srand(time(NULL));
	int n = rand() % 3;
	if ( n == 0 ){
		cout << "p1 is the landlord.\n";
		distribute(p1, p2, p3);
	}
	else if ( n == 1 ){
		cout << "p2 is the landlord.\n";
		distribute(p2, p1, p3);
	}
	else{
		cout << "p3 is the landlord.\n";
		distribute(p3, p2, p1);
	}
	cout << "The landlord pokers are: \n";
	sort(landlord);
	print(landlord);
	cout << endl;
	cout << endl;
	return n + 1;
}


void print(vector<int> hand){
	int set, number;
	for ( int i = 0; i < hand.size(); i++ ){
		if ( hand[i] == 998 ){
			cout << "joker" << ' ';
			continue;
		}
		else if ( hand[i] == 999 ){
			cout << "JOKER" << ' ';
			continue;
		}
		set = hand[i] / 100 - 1;
		number = hand[i] % 100 - 1;
		cout << setw(4) << numbers[number];
		cout << sets[set] << ' ';
	}
	cout << endl;
}

void printself(vector<int> p1){
	cout << "Amount: " << p1.size() << endl;
	sort(p1);
	print(p1);
	printcount();
}

void add(int n){
	int set, number;
	if ( n == 998 )
		COUNT[13] -= 1;
	else if ( n == 999 )
		COUNT[14] -= 1;
	else{
		number = n % 13 - 1;
		COUNT[number] -= 1;
	}
}

void printcount(){
	cout << endl;
	cout << "Card counter: \n";
	for ( int i = 0; i < 15; i++ ){
		cout << setw(5) << numbers[i] << ' ';
	}
	cout << endl;
	for ( int i = 0; i < 15; i++ ){
		cout << setw(5) << COUNT[i] << ' ';
	}
	cout << endl;
	cout << endl;
}

int check(){
	if ( p1.size() == 0 )
		return 1;
	if ( p2.size() == 0 )
		return 2;
	if ( p3.size() == 0 )
		return 3;
	return 0;
}


void play(){
	
}

void linklist(doublelink * &head){
	doublelink * x = new doublelink, * y = new doublelink, * z = new doublelink;
	x->p = p1, y->p = p2; z->p = p3;
	x->next = NULL;
	head = x;
	y->next = NULL;
	head->next = y;
	z->next = head;
	head->next->next = z;
}