#pragma once
#include"matrix.h"
#include<vector>
class nPr;
class MagicSquare : public Matrix<int>
{
public:
	MagicSquare(int w);
	MagicSquare(std::vector<std::vector<int>> l);
	void build();
	static Matrix<int> result;

protected:
	int add_line(int);
	int add_row(int);
	int add_criss();
	int add_cross();
	bool full_check();

private:
	nPr **p;
	int line_sum;
	std::vector<int> nums;
};
