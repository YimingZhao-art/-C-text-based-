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

struct doublelink{
	vector<int> p;
	doublelink * next;
}; //链表

//**************************************************************************************************************************************
vector<int> POKER; //扑克牌
vector<int> p1, p2, p3; //三个玩家
vector<int> lord;
int n; //出牌人
int COUNT[15]={4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1}; //初始记牌器
string sets[] = { SPADE, CLUB, HEART, DIAMOND };
string numbers[] = { "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A", "2","joker", "JOKER" };
int nu[] = {3,4,5,6,7,8,9,10,11,12,13,14,15}; //initialized 扑克牌里A是14，2是15
//**************************************************************************************************************************************


//**************************************************************************************************************************************
void linklist(doublelink * &head); //生成双向链表
void set_poker(vector<int> &POKER); //初始扑克牌
void swap(int * a, int * b); //交换数字
void shuffle(vector<int> &POKER); //洗牌
void distribute(vector<int> &p1, vector<int> &p2, vector<int> &p3); //发牌
int landlord(vector<int> &p1, vector<int> &p2, vector<int> &p3); //选择地主，并发牌
void print(vector<int> hand); //牌与数字转换打印，包含在打印手牌中
void printcount(); //打印记牌器，包含在打印手牌中，以p1的视角
int check(doublelink * head, vector<int> p); //游戏是否结束，返回赢得人
//**************************************************************************************************************************************

//**************************************************************************************************************************************
void del(vector<int> &hand, int n); //删除某个元素
void add(int n); //记牌器改变
vector<int> count(vector<int> hand); //出现次数
vector<int> initial(vector<int> hand); //将扑克转化成两位数
int in(vector<int> hand, int n); //是否在	,返回出现次数，0即不在
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
//**************************************************************************************************************************************

doublelink * ntop(doublelink * head, int n); //给一个数字n，来返回链表中对应的向量的位置
int pton(doublelink * head, vector<int> p); //给一个向量，返回对应值
void readin(vector<int> &place); //读取扑克牌index
void readin1(vector<int> &poker); //读取扑克牌点数
void clean(vector<int> &place); //清空一个向量
void printstatus(vector<int> lord); //打印地主牌
vector<int> lordpoker(vector<int> POKER); //返回地主牌
void printeveryone(doublelink * curr, int n); //打印所有人手牌数量

//**************************************************************************************************************************************


vector<int> GivenPlace(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //返回出牌序列
vector<int> GivenPlace1(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //返回跟牌序列
vector<int> Given1(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //出牌，自己是地主
vector<int> Given2(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //出牌，下一个是地主
vector<int> Given3(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //出牌，下一个人是队友
vector<int> Given4(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //跟牌，自己是地主
vector<int> Given5(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //跟牌，上一个人是地主
vector<int> Given6(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l); //跟牌，上一个人是队友
vector<int> PokerToPlace(vector<int> poker, vector<int> hand); // 扑克牌点数转化为index
vector<int> transfer(vector<string> poker1);// 读取牌号返回数字
vector<int> Killer(vector<int> hand); //返回手牌中所有的炸弹代数和王炸代数
vector<int> SameType(vector<int> hand); //返回同种类

void HandGive(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head); //人是擂主
void HandSolve(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head); //人对付上一个

void ComputerGive(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head, doublelink * l); //计算机是擂主
void ComputerSolve(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head, doublelink * l); //计算机跟牌



//**************************************************************************************************************************************
//组合
void printself(vector<int> p1); //打印手牌
void sort(vector<int> &POKER); //理牌
void play(doublelink * head, int n); //回合
int HAND(vector<int> hand); //手牌状态
int dominant(vector<int> hand); // 决定大小的量
bool compete(vector<int> now, vector<int> next); //比较大小 
vector<int> out(vector<int> &hand, vector<int> place); //出牌
vector<int> testout(vector<int> hand, vector<int> place); //预出牌
//**************************************************************************************************************************************





int main() {
	doublelink * head = NULL;
	
	string code;
	//cout << "You are p1.\n";
	set_poker(POKER); //设置扑克牌
	
	for ( int i = 0; i < 7; i++ )
		shuffle(POKER); //洗牌
	
	lord = lordpoker(POKER);
	n = landlord(p1, p2, p3); //确认地主并发牌
	
	sort(p1), sort(p2), sort(p3);
	linklist(head); //形成双向链表，用来出牌，得保持更新
	for ( int i = 0; i < p1.size(); i++ ){
		add(p1[i]); //记牌器初始化
	}
	
	
	play(head, n);
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

void distribute(vector<int> &p1, vector<int> &p2, vector<int> &p3){
	for ( int i = 0; i < 20; i++ ){
		p1.push_back(POKER[i]);
	}
	for ( int i = 20; i < 37; i++ ){
		p2.push_back(POKER[i]);
	}
	for ( int i =37; i < 54; i++ ){
		p3.push_back(POKER[i]);
	}
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
	cout << endl;
	cout << endl;
	return n;
}


void print(vector<int> hand){
	int set, number;
	for ( int i = 0; i < hand.size(); i++ ){
		if ( hand[i] == 998 ){
			printf("\033[01;37mjoker \033[0m");
			//cout << "joker" << ' ';
			continue;
		}
		else if ( hand[i] == 999 ){
			printf("\033[01;31mJOKER\033[0m");
			//cout << "JOKER" << ' ';
			continue;
		}
		set = hand[i] / 100 - 1;
		number = hand[i] % 100 - 1;
		//cout << setw(4) << numbers[number];
		if ( set < 2 ){
			string x = sets[set];
			printf("\033[01;30m%4s%s \033[0m",numbers[number].c_str(),x.c_str());
		}
		else {
			string x = sets[set];
			printf("\033[01;31m%4s%s \033[0m",numbers[number].c_str(),x.c_str());
		}
			
	}
	cout << endl;
}

void printself(vector<int> p1){
	//cout << "Amount: " << p1.size() << endl;
	sort(p1);
	/*for ( int i = 0; i < p1.size(); i++ ){
		cout << setw(5) << p1[i] << ' ';
	} */
	//cout << endl;
	cout << endl;
	for ( int i = 0; i < p1.size(); i++ )
		cout << "------";
	cout << endl;
	//cout << "|";
	print(p1);
	for ( int i = 0; i < p1.size(); i++ )
		cout << "------";
	cout << endl;
	//printcount();
}

void add(int n){
	int set, number;
	if ( n == 998 )
		COUNT[13] -= 1;
	else if ( n == 999 )
		COUNT[14] -= 1;
	else{
		number = (n % 100) % 14 - 1;
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

int check(doublelink * head, vector<int> p){
	if ( p.size() == 0 )
		return pton(head, p);
	return -1;
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

int HAND(vector<int> hand){
	sort(hand);
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
	return -1;
}



vector<int> initial(vector<int> hand){
	vector<int> x;
	for ( int i = 0; i < hand.size(); i++ ){
		if ( hand[i] < 998 )
			x.push_back( nu[(hand[i] % 100) - 1]);
		else
			x.push_back(hand[i]);
	}
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
		if ( in(x,15) )
			return false;
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
		if ( x.size() == hand.size() / 2 && hand.size() % 2 == 0 ){
			for ( int i = 0; i < x.size(); i++ )
				if ( x[i] != 2 )
					return false;
			vector<int> sort(hand);
			vector<int> nv;
			for ( int i = 0; i < hand.size(); i += 2 ){
				nv.push_back(hand[i]);
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

void del(vector<int> &hand, int n){
	for ( vector<int>::iterator i = hand.begin(); i < hand.end(); i++ )
		if ( *i == n ){
			hand.erase(i);
			return;
		}
}

vector<int> testout(vector<int> hand, vector<int> place){
	vector<int> to;
	for ( int i = 0; i < place.size(); i++ ){
		to.push_back(hand[place[i]]);
	}
	return to;
}

vector<int> out(vector<int> &hand, vector<int> place){
	vector<int> to;
	for ( int i = 0; i < place.size(); i++ ){
		to.push_back(hand[place[i]]);
	}
	
	for ( int i = 0; i < to.size(); i++ ){
		add(to[i]);
		del(hand, to[i]);
	}
	cout << "Given out: \n";
	print(to);
	return to;
}


bool compete(vector<int> now, vector<int> next){
	int x = HAND(now), y = HAND(next);
	int p = dominant(now), q = dominant(next);
	if ( x == 999 )
		return false;
	if ( y == 999 )
		return  true;
	else if ( x != 100 && y == 100 )
		return true;
	else if ( x == 100 && y != 100 )
		return false;
	else if ( x == 100 && y == 100 ){
		return p < q;
	}
	if ( x != y ) return false;
	return p < q;
}

int dominant(vector<int> hand){
	vector<int> c = count(hand), nv ,newhand = initial(hand);
	for ( int i = 0; i < newhand.size(); i++ ){
		if ( !in(nv,newhand[i]) && in(newhand, newhand[i]) == c[c.size() - 1] ){
				nv.push_back(newhand[i]);
		}
	}
	return nv[nv.size() - 1];
}

doublelink * ntop(doublelink * head, int n){
	switch (n%3) {
		case 0:
			return head;
		case 1:
			return head->next;
		case 2:
			return head->next->next;
	}
	return head;
}

int pton(doublelink * head, vector<int> p){
	for ( int n = 0; n < 3; n++ )
		if ( ntop(head, n)->p == p )
			return n;
	return 0;
}

void readin(vector<int> &place){
	cout << "Input the index of poker, end by inputing -1: \n";
	int command;
	cin >> command;
	while ( command != -1 ){
		place.push_back(command);
		cin >> command;
	}
}

vector<int> transfer(vector<string> poker1){
	vector<int> a;
	for ( int i = 0; i < poker1.size(); i++ ){
		if ( poker1[i].length() > 1 ){
			if ( poker1[i] == "JOKER" )
				a.push_back(999);
			else if ( poker1[i] == "joker" ){
				a.push_back(998);
			}
			else if ( poker1[i] == "10" ){
				a.push_back(10);
			}
		}
		else {
			if ( poker1[i][0] <= '9' && poker1[i][0] >= '1' ){
				int na = poker1[i][0] - '0';
				a.push_back(na);
			}
			else {
				if ( poker1[i][0] == 'A' || poker1[i][0] == 'a' )
					a.push_back(1);
				else if ( poker1[i][0] == 'J' || poker1[i][0] == 'j' )
					a.push_back(11);
				else if ( poker1[i][0] == 'Q' || poker1[i][0] == 'q' )
					a.push_back(12);
				else if ( poker1[i][0] == 'K' || poker1[i][0] == 'k')
					a.push_back(13);
			}
		}
	}
	return  a;
}

void readin1(vector<int> &poker){
	vector<string> p1;
	cout << "Input the poker, end by inputing exit: \n";
	string command;
	cin >> command;
	while ( command != "exit" ){
		p1.push_back(command);
		cin >> command;
	}
	poker = transfer(p1);
}

vector<int> PokerToPlace(vector<int> poker, vector<int> hand){
	vector<int> place, nv = initial(hand);
	
	for ( int  j = 0; j < nv.size(); j++ ){
		if ( nv[j] == 14 || nv[j] == 15 )
			nv[j] -= 13;
	}
	
	for ( int i = 0; i < poker.size(); i++ ){
		for ( int j = 0; j < nv.size(); j++ ){
			if ( nv[j] == -1 || poker[i] == -1 ) continue;
			if ( nv[j] == poker[i] ){
				place.push_back(j);
				nv[j] = -1;
				poker[i] = -1;
			}
		}
	}
	return place;
}

void clean(vector<int> &place){
	while ( place.size() )
		place.pop_back();
}

void printstatus(vector<int> lord){
	cout << "The poker of lord:\n";
	print(lord);
	cout << endl;
	cout << endl;
}

vector<int> lordpoker(vector<int> POKER){
	vector<int> lord;
	for ( int i = 0; i < 3; i++ )
		lord.push_back(POKER[i]);
	sort(lord);
	return lord;
}

void printeveryone(doublelink * curr, int n){
	if ( n%3 + 1 == 1 ){
		int x = curr->p.size(), y = curr->next->p.size(), z = curr->next->next->p.size();
		printf("\033[01;31mp1: %2d                                                               \033[0m", x);
		printf("\033[01;33mp3: %2d\033[0m\n", z);
		cout << "\n\n\n";
		printf("\033[01;33m                                   p2: %2d\033[0m\n\n", y);
	}
	else if ( n%3 + 1 == 2){
		int y = curr->p.size(), z = curr->next->p.size(), x = curr->next->next->p.size();
		printf("\033[01;33mp1: %2d                                                               \033[0m", x);
		printf("\033[01;33mp3: %2d\033[0m\n", z);
		cout << "\n\n\n";
		printf("\033[01;31m                                   p2: %2d\033[0m\n\n", y);
	}
	else {
		int z = curr->p.size(), x = curr->next->p.size(), y = curr->next->next->p.size();
		printf("\033[01;33mp1: %2d                                                               \033[0m", x);
		printf("\033[01;31mp3: %2d\033[0m\n", z);
		cout << "\n\n\n";
		printf("\033[01;33m                                   p2: %2d\033[0m\n\n", y);
	}
}

void HandGive(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head){
	cout << "\n\n";
	cout << "Poker of p"<< n%3 + 1 << ": \n";
	printself(curr->p);
	vector<int> poker;
	
	readin1(poker);
	place = PokerToPlace(poker, curr->p);
	
	while ( place.size() == 0 || HAND(testout(curr->p, place)) == -1 ){
		clean(place);
		clean(poker);
		readin1(poker);
		place = PokerToPlace(poker, curr->p);
	}
	nowhand = out(curr->p, place);
	//linklist(head); //形成双向链表，用来出牌，得保持更新
	clean(place);
	clean(poker);
	last = curr;
	curr = curr->next;
	n++;
}

void HandSolve(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head){
	int exit;
	vector<int> poker;
	cout << "last hand: \n";
	print(nowhand);
	cout << "\n\n";
	cout << "Poker of p"<< n%3 + 1 << ": \n";
	printself(curr->p);
	cout << "If you want to skip, input -1, otherwise, input any other number to continue.\n";
	cin >> exit;
	if ( exit == -1 ){
		curr = curr->next;
		n++;
		return;
	}
	else{
		readin1(poker);
		place = PokerToPlace(poker, curr->p);
		
		while ( place.size() == 0 || !compete(nowhand, testout(curr->p, place)) ){
			clean(place);
			clean(poker);
			cout << "If you want to skip, input -1, otherwise, input any other number to continue.\n";
			cin >> exit;
			if ( exit == -1 ) break;
			readin1(poker);
			place = PokerToPlace(poker, curr->p);
		}
		if ( place.size() != 0 && compete(nowhand, testout(curr->p, place)) ){
			nowhand = out(curr->p, place);
			clean(place);
			clean(poker);
			//linklist(head);
			last = curr;
		}
		//linklist(head);
		curr = curr->next;
		n++;
	}
	return;
}

void play(doublelink * head, int n){
	doublelink * curr = ntop(head, n), * last = curr, * l = curr;
	vector<int> place, nowhand;
	
	
	while ( check(head, curr->p) == -1 ){
		//printcount();
		system("clear");
		printeveryone(curr, n);
		printstatus(lord);
		
		
		if ( last == curr ){
			
			HandGive(last, curr, n, nowhand, place, head);
			if ( check(head, last->p) != -1 ){
				cout << "p" << check(head, last->p) + 1 << " wins.\n";
				return;
			}
		}
		else{
			if ( HAND(nowhand) == 999 ){
				curr = curr->next;
				continue;;
			}
			
			HandSolve(last, curr, n, nowhand, place, head);
			if ( check(head, last->p) != -1 ){
				cout << "p" << check(head, last->p) + 1 << " wins.\n";
				return;
			}
		}
	}
}


void ComputerGive(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head, doublelink * l){
	cout << "\n\n";
	cout << "Round of p"<< n%3 + 1 << ": \n";
	//printself(curr->p);
	place = GivenPlace(nowhand, last, curr, l); // 得出出牌方式
	nowhand = out(curr->p, place);
	//linklist(head); //形成双向链表，用来出牌，得保持更新
	clean(place);
	last = curr;
	curr = curr->next;
	n++;
}

void ComputerSolve(doublelink * &last, doublelink * &curr, int &n, vector<int> &nowhand, vector<int> &place, doublelink * &head, doublelink * l){
	int exit;
	cout << "last hand: \n";
	print(nowhand);
	cout << "\n\n";
	cout << "Round of p"<< n%3 + 1 << ": \n";
	//printself(curr->p);
	
	place = GivenPlace1(nowhand, last, curr, l);
	
	if ( place.size() == 0 ){
		curr = curr->next;
		n++;
		return;
	}
	else{
		/*
		readin(place);
		while ( !compete(nowhand, testout(curr->p, place)) ){
			clean(place);
			cout << "If you want to skip, input -1, otherwise, input any other number to continue.\n";
			cin >> exit;
			if ( exit == -1 ) break;
			readin(place);
		}
		if ( compete(nowhand, testout(curr->p, place)) ){
			nowhand = out(curr->p, place);
			clean(place);
			//linklist(head);
			last = curr;
		}
		*/
		//linklist(head);
		nowhand = out(curr->p, place);
		clean(place);
		last = curr;
		curr = curr->next;
		n++;
	}
	return;
}

vector<int> GivenPlace(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l){
	vector<int> place;
	if ( curr == l ){
		//自己是地主
	}
	else {
		if ( curr->next == l ){
			//下一个人是地主
		}
		else{
			//下一个人是队友
		}
	}
	return place;
}

vector<int> GivenPlace1(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l){
	//l is the *doublelink of landlord
	vector<int> place;
	
	if ( curr == l ){
		//自己一队
		place = Given4(nowhand, last, curr, l);
	}
	if ( last == l ){
		place = Given5(nowhand, last, curr, l);
		
	}
	else if ( last != l ){
		Given6(nowhand, last, curr, l);
	}
	return place;
}

vector<int> Killer(vector<int> hand){
	vector<int> killer, nhand=initial(hand), counter = count(hand);
	if ( in(counter,4)  ){
		for ( int i = 0; i < nhand.size(); i++ ){
			if ( in(nhand, nhand[i]) == 4 ){
				killer.push_back(hand[i]);
			}
		}
	}
	if ( in(nhand,998) && in(nhand,999) ){
		killer.push_back(998);
		killer.push_back(999);
	}
	sort(killer);
	return killer;
}




//跟牌，自己是地主
vector<int> Given4(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l){
	vector<int> place, hand = initial(curr->p), counter = count(hand), can, killer = Killer(curr->p);
	int status = HAND(nowhand);
	int x = dominant(nowhand);
	
	if ( HAND(nowhand) == 100 ){
		if ( x < dominant(killer) ){
			for ( int i = 0; i < killer.size(); i += 4 ){
				if ( nu[killer[i]%100] > x ){
					for ( int n = 0; n < 4; n++ )
						place.push_back(killer[i+n]);
					return place;
				}
			}
		}
		else if ( in(killer, 998) ){
			place.push_back(998);
			place.push_back(999);
			return place;
		}
		else {
			return place;
		}
	}
	
	
	
	
	
	return place;
}


//跟牌，上一个人是地主
vector<int> Given5(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l){
	vector<int> place;
	return place;
}


//跟牌，上一个人是队友
vector<int> Given6(vector<int> nowhand, doublelink * last, doublelink * curr, doublelink * l){
	vector<int> place;
	return place;
}
