#pragma once

class Card
{
public:
	int n;
	char c;
	bool operator<(const Card& r) const { return comp_n() < r.comp_n(); }
	bool operator==(int r) const { return n == r; }
	char comp_c() const { return c == 'C' ? 'E' : c ; }
	int comp_n() const { return n == 1 ? 14 : n ; }
	friend std::ostream& operator<<(std::ostream& l, const Card& r);
	void family(bool f) {family_ = f;}
	bool family() const { return family_;}

protected:
	static constexpr const char* glyph[4]  {"♠ ", "♣ ", "♥ ", "♦ "};
	static constexpr const char g[4] {'C', 'H', 'D', 'S'};
	bool family_ = false;

private:
};

class Hand
{
public:
	Hand(std::array<Card, 5> h);
//	int drop_card(int n);
//	int get_card(Card c);
	bool operator<(const Hand& r) const;
	void show();
	int point() const {return point_;}
	void point(int p) {point_ = p;}
	std::array<Card, 5> hand;

protected:
	int point_;

private:
	void read_hand();
	bool is_straight() const;
	bool is_flush() const;
	int count_same();
};
