#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<string>
#include "card.h"
#include"combi.h"
using namespace std;

constexpr const char* Card::glyph[4];
constexpr const char Card::g[4];

Hand::Hand(array<Card, 5> h) 
{ 
	hand = h;
	read_hand();
}

bool Hand::is_flush() const
{
	for(int i=0; i<4; i++) if(hand[i].c != hand[i+1].c) return false;
	return true;
}

bool Hand::is_straight() const
{
	auto h = hand;
	sort(h.begin(), h.end());
	int serial = 0;
	for(int i=0; i<4; i++)	if(h[i].comp_n() == h[i+1].comp_n() - 1) serial++; 
	return serial == 4 ? true : (serial == 3 && h[3].n == 5 && h[4].n == 1); 
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
	sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
			return (!a.family() && b.family()) || (a.family() && !b.family())
				? a.family() && !b.family() : !(a < b); });
}

bool Hand::operator<(const Hand& r) const
{
	return point() == r.point() ? hand < r.hand : point() < r.point();
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
	l << r.glyph[i];
	char ch;
	switch(r.n) {
		case 1: ch = 'A'; break;
		case 11: ch = 'J'; break;
		case 12: ch = 'Q'; break;
		case 13: ch = 'K'; break;
		default: ch = r.n;
	}
	ch > 1 && ch < 11 ? l << +ch : l << ch;
	return l;
}



int main()
{
	Card card;
	array<Card, 52> deck;
	array<Card, 5> player1, player2;
	for(int i=1, k=0; i<14; i++) {
		for(char a : {'C', 'D', 'H', 'S'}) {
			card.n = i;
			card.c = a;
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
	array<Card, 5> tmp;
	while(c.next()) {
		for(int i=0; i<5; i++) tmp[i] = deck[c[i]-1];
		if(Hand(player1) < Hand(tmp)) player1 = tmp;
		for(int i=0; i<5; i++) tmp[i] = deck[c[i]-1+7];
		if(Hand(player2) < Hand(tmp)) player2 = tmp;
	}
	Hand h1(player1);
	Hand h2(player2);
	h1.show();
	h2.show();
	cout << "Player " << (h1 < h2 ? 2 : 1) << " won !!" << endl;
}


