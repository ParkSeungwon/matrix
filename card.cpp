#include<random>
#include<algorithm>
#include<iostream>
#include"combi.h"
using namespace std;

class Card
{
public:
	int num;
	char c;
	bool operator<(const Card& r) const {//const const needed for algorithm
		if(num == r.num) return comp_c() < r.comp_c();
		else return comp_n() < r.comp_n();
	}
	bool operator==(const int r) const {
		if(num == r) return true;
		else return false;
	}
	friend ostream& operator<<(ostream& o, Card& c) {
		o << c.c << c.num;
		return o;//necessary
	}

protected:
private:
	char comp_c() const {
		if(c == 'C') return 'E';
		else return c;
	}
	int comp_n() const {
		if(num == 1) return 14;
		else return num;
	}
};

auto f = [](Card a, Card b) { return !(a<b); };

class Hand
{
public:
	Hand(array<Card, 5> h) { hand = h;}
	void assign(array<Card, 5> h) { hand = h;}
	array<Card, 5> hand;
	bool operator<(Hand r) {//'&'?
		if(point == r.point) return best_card < r.best_card;
		else return point < r.point;
	}
	void read_card() {
		if(straight) cout << "straight ";
		if(flush) cout << "flush ";
		else if(four_card) cout << "4card ";
		else if(two_pair) cout << "two_pair ";
		else if(triple && one_pair) cout << "full house ";
		else if(triple) cout << "triple ";
		else if(one_pair) cout << "one pair ";
	}

	void diagnose() {
		reset_flag();
		auto h = hand;

		flush = true;
		for(int i=0; i<4; i++) if(h[i].c != h[i+1].c) flush = false;
		sort(h.begin(), h.end(), [](Card a, Card b) { return a.num < b.num; });

		int serial = 0;
		for(int i=0; i<4; i++)	if(h[i].num == h[i+1].num - 1) serial++; 
		if(serial == 4) straight = true;
		else if(h[0].num == 1 && h[1].num == 10 && serial == 3) straight = true;
		if(flush || straight) sort(h.begin(), h.end(), f);

		for(int i=0, c=0; i<5; i++) {
			if(straight || flush) break;
			if(i < 4 && h[i].num == h[i+1].num) c++;
			else {
				if(c == 3) four_card = true;
				else if(c == 2) triple = true;
				else if(c == 1) {
					if(one_pair != true) one_pair = true;
					else {
						one_pair = false;
						two_pair = true;
					}
				}
				c = 0;
			}
		}

		if(four_card) {
			remove_if(h.begin(), h.end(), [&h](Card a) { 
					return count(h.begin(), h.end(), a.num) == 1;});
			sort(h.begin(), h.begin()+4, f);
			point += 7;
		} else if(flush) {
			point += 5;
		} else if(one_pair && triple) {
			remove_if(h.begin(), h.end(), [&h](Card a) {
					return count(h.begin(), h.end(), a.num) == 2;});
			sort(h.begin(), h.begin()+3, f);
			point += 6;
		} else if(two_pair) {
			remove_if(h.begin(), h.end(), [&h](Card a) {
					return count(h.begin(), h.end(), a.num) == 1;});
			sort(h.begin(), h.begin()+4, f);
			point += 2; 
		} else if(one_pair) {
			remove_if(h.begin(), h.end(), [&h](Card a) {
					return count(h.begin(), h.end(), a.num) == 1;});
			sort(h.begin(), h.begin()+2, f);
			point += 1;
		} else if(triple) {
			remove_if(h.begin(), h.end(), [&h](Card a) {
					return count(h.begin(), h.end(), a.num) == 1;});
			sort(h.begin(), h.begin()+3, f);
			point += 3;
		}
		if(straight) {
			point += 4;
		}
		best_card = h[0];
	}

	int point = 0;
	Card best_card;

protected:
private:
	void reset_flag() {
		four_card = false, flush = false, straight = false, 
		 triple = false, two_pair = false, one_pair = false;
	}
	bool four_card = false, flush = false, straight = false, 
		 triple = false, two_pair = false, one_pair = false;
};

int main()
{
	Card card;
	array<Card, 52> deck;
	array<Card, 7> player1, player2;
	char g[4] {'C', 'D', 'H', 'S'};
	for(int i=0, k=0; i<4; i++) {
		for(int j=1; j<14; j++) {
			card.num = j;
			card.c = g[i];
			deck[k++] = card;
		}
	}

	shuffle(deck.begin(), deck.end(), random_device());
//	sort(deck.begin(), deck.begin()+5, f);
//	sort(deck.begin()+5, deck.begin()+10, f);
	cout << "Player 1 has : ";
	for(int i=0; i<7; i++) cout << deck[i].c << deck[i].num << ' ';
	cout << endl;
	cout << "Player 2 has : ";
	for(int i=7; i<14; i++) cout << deck[i].c << deck[i].num << ' ';
	cout << endl;
//	player1.resize(5);//resize before copy
//	player2.resize(5);
	copy_n(deck.begin(), 7, player1.begin());
	copy_n(deck.begin()+7, 7, player2.begin());
	nCr c(7, 5);
	array<Card, 5> card1, card2, tmp;
	copy(player1.begin(), player1.begin()+5, card1.begin());
	copy(player2.begin(), player2.begin()+5, card2.begin());
	Hand h1(card1), h2(tmp);
	while(c.next()) {
		for(int i=0; i<5; i++) tmp[i] = player1[c[i]-1];
		h1.assign(card1); h2.assign(tmp);
		h1.diagnose(); h2.diagnose();
		if(h1 < h2) card1 = tmp;
		for(int i=0; i<5; i++) tmp[i] = player2[c[i]-1];
		h1.assign(card2); h2.assign(tmp);
		h1.diagnose(); h2.diagnose();
		if(h1 < h2) card2 = tmp;
	}
	for(auto& a : card1) cout << a << ' ';
	cout << endl;
	for(auto& a : card2) cout << a << ' ';
	cout << endl;

	h1.assign(card1);
	h2.assign(card2);
	h1.diagnose();
	h2.diagnose();
	cout << "1 : ";
	h1.read_card();
	cout << endl << "2 : ";
	h2.read_card();
	cout << endl;
	if(h1<h2) cout << "Player 2 won !!" << endl;
	else cout << "Player 1 won !!" << endl;
}


