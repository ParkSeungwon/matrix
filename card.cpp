#include<map>
#include<random>
#include<algorithm>
#include<iostream>
#include<exception>
#include<string>
#include"card.h"
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

bool Card::operator>(const Card& r)const
{//In hand array compare, this should not be used before < compare.
	return comp_n()==r.comp_n() ? comp_c()>r.comp_c() : comp_n()>r.comp_n();
}

void Hand::read_hand()
{
	point(count_same());
	if(is_flush()) point_ += 5;
	if(is_straight()) point_ += 4;
	if(point() == 6) {//for sorting flush case 
		for(auto& a : hand) 
			if(count(hand.begin(), hand.end(), a.n) == 2) a.family(false);
	}
	auto it = partition(hand.begin(), hand.end(), [](const Card& a) {
			return a.family();});
	sort(hand.begin(), it, greater<Card>());
	sort(it, hand.end(), greater<Card>());
//	sort(hand.begin(), hand.end(), [](const Card& a, const Card& b) {
//			return (!a.family() && b.family()) || (a.family() && !b.family())
//				? a.family() && !b.family() : a > b; });
}

bool Hand::operator<(const Hand& r) const
{
	if(point() == r.point()) {
		if(hand == r.hand) return !(hand[0] > r.hand[0]);//compare card
		else return hand < r.hand;//compare array
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
//	if(!r.show()) return l << Card::utf8chr(static_cast<int>(Unicode::CARDBACK));
	Unicode u;
	switch(r.c) {
		case 'C': u = Unicode::CLUB; break;
		case 'H': u = Unicode::HEART; break;
		case 'D': u = Unicode::DIAMOND; break;
		case 'S': u = Unicode::SPADE;
	}

	l << Card::utf8chr(static_cast<int>(u));
	l << ' ';
	//l << r.glyph[i];
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

string Card::utf8chr(int cp)
{
	char c[5]={ 0x00,0x00,0x00,0x00,0x00 };
	if     (cp<=0x7F) { c[0] = cp;  }
	else if(cp<=0x7FF) { c[0] = (cp>>6)+192; c[1] = (cp&63)+128; }
	else if(0xd800<=cp && cp<=0xdfff) {} //invalid block of utf8
	else if(cp<=0xFFFF) { c[0] = (cp>>12)+224; c[1]= ((cp>>6)&63)+128; c[2]=(cp&63)+128; }
	else if(cp<=0x10FFFF) { c[0] = (cp>>18)+240; c[1] = ((cp>>12)&63)+128; c[2] = ((cp>>6)&63)+128; c[3]=(cp&63)+128; }
	return string(c);
}

Deck::Deck()
{
	Card card;
	for(int i=1, k=0; i<14; i++) {
		for(char a : {'C', 'D', 'H', 'S'}) {
			card.n = i;
			card.c = a;
			deck[k++] = card;
		}
	}
}

void Deck::shuffle_deck()
{ 
	for(auto& a : deck) a.show(false);
	shuffle(deck.begin(), deck.end(), random_device());
	top = 0;
}
	
Card Deck::distribute_card()
{
	if(top < 52) return deck[top++];
	else throw No_card_exception();
}

int Player::cal_point(const array<Card, 52>& deck)
{
	int open = count_if(deck.begin(), deck.end(), [](Card c){return !c.show();});
	nCr ncr(52 - open, 7 - 4);
}
int main()
{
	Deck deck;
	deck.shuffle_deck();
	array<Card, 5> player1, player2;

	cout << "Player 1 has : ";
	for(int i=0; i<7; i++) cout << deck[i] << ' ';
	cout << endl;
	cout << "Player 2 has : ";
	for(int i=7; i<14; i++) cout << deck[i] << ' ';
	cout << endl;
	for(auto& a : player1) a = deck.distribute_card();
	deck.distribute_card();
	deck.distribute_card();
	for(auto& a : player2) a = deck.distribute_card();
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


