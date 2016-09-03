#include<iostream>
#include"irrational.h"
using namespace std;
int main()
{
	Root r{6, 2};
	r = 1 - r;
	cout << r*r -3*r - 3 << endl;
}

