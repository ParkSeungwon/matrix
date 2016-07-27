#include"matrix.cc"
#include"rational.h"
#include<iostream>
using namespace std;


int main()
{
	Matrix<Ratio> m{{{ 1, 1 },
					 { 2, 4 }}};
	Matrix<Ratio> m2{{{2},{3}}};
	(m*m).show();
	(m*m2).show();
}
