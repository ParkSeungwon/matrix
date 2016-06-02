#pragma once
#include"matrix.h"

class MagicSquare : public Matrix<int>
{
public:
	MagicSquare(int w);
	MagicSquare(std::vector<std::vector<int>> l);
	void build();
	static Matrix<int> result;
	void partial_nPr();

protected:
	int add_line(int);
	int add_row(int);
	int add_criss();
	int add_cross();
	bool full_check();

private:
	int line_sum;
	std::vector<int> nums;
	std::vector<std::vector<int>> parts;
};
