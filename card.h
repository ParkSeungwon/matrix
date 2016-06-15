#pragma once

class Card
{
public:
	int n;
	char c;
	bool operator<(const Card& r) const;
	bool operator==(int r) const;
	char comp_c() const;
	int comp_n() const;
	friend std::ostream& operator<<(std::ostream& l, const Card& r);
	void family(bool f) {family_ = f;}
	bool family() { return family_;}

protected:
	static std::string glyph[4];
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
