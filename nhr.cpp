#include"combi.h"
#include<iostream>
using namespace std;

int main()
{
//	cout << nHr(10, 7).count();
	long h = 0;
	nHr nhr(10, 10);
	while(nhr.next()) h++;;
	float f;
	for(int i=1; i<10; i++) {
		int c = 0;
		nCr ncr(10, i);
		while(ncr.next()) c++;
		nHr nhr(i, 10-i);
		int hh = 0;
		while(nhr.next()) hh++;
		f = float(c * hh) / h;
		cout << f << endl;
	}
}

