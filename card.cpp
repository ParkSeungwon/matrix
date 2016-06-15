#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<string>
#include "card.h"
#include"combi.h"
using namespace std;

string Card::glyph[4] = {"♠", "♣", "♥", "♦"};

bool Card::operator<(const Card& r) const 
{//const const needed
	return comp_n() < r.comp_n();
}

bool Card::operator==(int r) const {
	if(n == r) return true;
	else return false;
}

char Card::comp_c() const {
	if(c == 'C') return 'E';
	else return c;
}

int Card::comp_n() const {
	if(n == 1) return 14;
	else return n;
}

auto f = [](Card a, Card b) { return !(a<b); };

Hand::Hand(array<Card, 5> h) 
{ 
	hand = h;
	read_hand();
}

bool Hand::is_flush() const
{
	bool flush = true;
	for(int i=0; i<4; i++) if(hand[i].c != hand[i+1].c) flush = false;
	return flush;
}

bool Hand::is_straight() const
{
	auto h = hand;
	sort(h.begin(), h.end());
	int serial = 0;
	for(int i=0; i<4; i++)	if(h[i].comp_n() == h[i+1].comp_n() - 1) serial++; 
	if(serial == 4) return true;
	else if(serial == 3 && h[3].n == 5 && h[4].n == 1) return true; 
	return false;
}

int Hand::count_same()
{//one pair 1, two pair 2, triple 3, fullhouse 6, four card 7,  return else 0
	map<int, int> m;
	for(auto& a : hand) m[a.n]++;
	int k = 0, l = 0;
	for(auto& a : m) {
		if(a.second == 2) k++;
		else if(a.second == 3) l = 3;
		else if(a.second == 4) l = 7;
		if(a.second > 1) for(auto& b : hand) if(b.n == a.first) b.family(true);
	}
	return k+l == 4 ? 6 : k+l;
}

void Hand::read_hand()
{
	point(count_same());
	if(is_flush()) point(point() + 5);
	if(is_straight()) point(point() + 4);
	if(point() == 6) {
		for(auto& a : hand) 
			if(count(hand.begin(), hand.end(), a.n) == 2) a.family(false);
	}
	sort(hand.begin(), hand.end(), [](Card a, Card b) {
			if((!a.family() && b.family()) || (a.family() && !b.family()))
				return a.family() && !b.family();
			else return !(a < b);
			});
}

bool Hand::operator<(const Hand& r) const
{
	if(point() == r.point()) {
		return hand < r.hand;
	} else return point() < r.point();
}

void Hand::show()
{
	for(auto& a : hand) cout << a << ' ';
	switch(point()) {
		case 1: cout << "one pair"; break;
		case 2: cout << "two pair"; break;
		case 3: cout << "triple"; break;
		case 4: cout << "straight"; break;
		case 5: cout << "flush"; break;
		case 6: cout << "full house"; break;
		case 7: cout << "four card"; break;
		case 9: cout << "straight flush"; break;
	}
	cout << endl;
}

ostream& operator<<(ostream& l, const Card& r)
{
	int i;
	switch(r.c) {
		case 'C': i = 1; break;
		case 'H': i = 2; break;
		case 'D': i = 3; break;
		case 'S': i = 0;
	}
	l << r.glyph[i] << ' ' << r.n;
	return l;
}



int main()
{
	Card card;
	array<Card, 52> deck;
	array<Card, 5> player1, player2;
	char g[4] {'C', 'D', 'H', 'S'};
	for(int i=0, k=0; i<4; i++) {
		for(int j=1; j<14; j++) {
			card.n = j;
			card.c = g[i];
			deck[k++] = card;
		}
	}

	shuffle(deck.begin(), deck.end(), random_device());
	cout << "Player 1 has : ";
	for(int i=0; i<7; i++) cout << deck[i] << ' ';
	cout << endl;
	cout << "Player 2 has : ";
	for(int i=7; i<14; i++) cout << deck[i] << ' ';
	cout << endl;
	copy_n(deck.begin(), 5, player1.begin());
	copy_n(deck.begin()+7, 5, player2.begin());
	nCr c(7, 5);
	while(c.next()) {
		array<Card, 5> tmp;
		for(int i=0; i<5; i++) tmp[i] = deck[c[i]-1];
		if(Hand(player1) < Hand(tmp)) player1 = tmp;
		for(int i=0; i<5; i++) tmp[i] = deck[c[i]-1+7];
		if(Hand(player2) < Hand(tmp)) player2 = tmp;
	}
	Hand h1(player1);
	Hand h2(player2);
	h1.show();
	h2.show();
	if(h1<h2) cout << "Player 2 won !!" << endl;
	else cout << "Player 1 won !!" << endl;
}


