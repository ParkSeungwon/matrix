#include<iostream>
#include<exception>
#include"combi.h"
#include"rational.h"
using namespace std;

bool on[100] {};

Ratio cal(Ratio a, int c, Ratio b) {
	switch (c) {
		case 1: return a+b;
		case 2: return a-b;
		case 3: return a*b;
		case 4: 
				try {
					if(b == 0) throw 1;
					else return a/b;
				} catch (int e){}
	}
}

Ratio cal(Ratio a, int c1, Ratio b, int c2, Ratio c) {
	if((c1 == 1 || c1 == 2) && (c2 == 3 || c2 == 4)) return cal(a, c1, cal(b, c2, c));
	else return cal(cal(a, c1, b), c2, c);
}

void set_on(Ratio r) {
	if(r.den == 1) {
		if(r.n < 100 && r.n >= 0) on[r.n] = true;
	}
}

int e(int n[5]) {
	nPr p(4, 4);
	nTr t(4, 3);
	Ratio f;
	while(p.next()) {
		while(t.next()) {
			f = cal(cal(n[p[0]], t[0], n[p[1]]), t[1], n[p[2]], t[2], n[p[3]]);
			set_on(f);
			f = cal(n[p[0]], t[0], n[p[1]], t[1], cal(n[p[2]], t[2], n[p[3]]));
			set_on(f);
			f = cal(n[p[0]], t[0], cal(n[p[1]], t[1], n[p[2]]), t[2], n[p[3]]);
			set_on(f);
			f = cal(cal(n[p[0]], t[0], n[p[1]], t[1], n[p[2]]), t[2], n[p[3]]);
			set_on(f);
			f = cal(n[p[0]], t[0], cal(n[p[1]], t[1], n[p[2]], t[2], n[p[3]]));
			set_on(f);
		}
	}
	int k=1;
	while(on[k++]);
	for(int i=0; i<1000; i++) on[i] = false;
	return k-2;
}


int main()
{
	int n[5];
	nCr c(20, 4);
	while(c.next()) {
		for(int i=0; i<4; i++) n[i+1] = c[i];
		cout << "e(";
		for(int i=0; i<4; i++) cout << c[i] << ',';
		cout << ") = " << e(n) << endl;
	}
}
