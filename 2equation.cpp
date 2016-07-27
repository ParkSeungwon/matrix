#include<iostream>
#include"imaginary.h"
using namespace std;

int main(int argc, char** v)
{
	if(argc < 4) {
		cout << "usage : " << v[0] << "[a] [b] [c]" << endl;
		return 0;
	}
	int a = stoi(v[1]);
	int b = stoi(v[2]);
	int c = stoi(v[3]);

	int D = b*b - 4*a*c;
	if(D>=0) {
		Root d{D, 2};
		cout << (-b+d)/(2*a) << '\t' << (-b-d)/(2*a) << endl;
	} else {
		Imag d{0, Root(-D, 2)};
		cout << (-b+d)/(2*a) << '\t' << (-b-d)/(2*a) << endl;
	}
}
