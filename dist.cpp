#include"irrational.h"
#include<iostream>
#include"imaginary.h"
using namespace std;

int main()
{
	auto x = 4-Root(5, 2) * 12/5;
	cout << x << endl;
	auto y = -8 - Root(5,2) * 6/5;
	cout << y << endl;
	Imag im(x, y);
	Imag im2(9,2);
	auto im3 = im-im2;

	cout << im3 << endl;
	cout << im3.abs() << endl;
}

