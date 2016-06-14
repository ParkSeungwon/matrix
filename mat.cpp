#include"combi.h"
#include"irrational.h"
#include<iostream>
#include<map>
using namespace std;

int main()
{
	nHr h(5,20);
	float f[5] {5.9, 11.4, 2.72, 1.72, 7.24};
	float sum = 0;
	map<short, short> m;
	while(h.next()) {
		for(int i=0; i<20; i++) {
			sum += f[h[i]-1];
			m[h[i]]++;
		}
		sum /= 20;
		if(sum >= 4.95 && sum <= 5.05) { 
			cout << "Zinc " << m[1]*5 << "% Tin " << m[2]*5 << "% Al ";
			cout << m[3]*5 << "% Cu " << m[4]*5 << "% Ni " << m[5]*5;
			cout << "% = ohm " << sum << endl; 
		}
		m.clear();
		sum = 0;
	}

	{
		nHr h(6, 3);
		int m = 0, n = 0;
		while(h.next()) {
			if(h[0]+h[1]+h[2] == 10) {
				cout << h[0] << h[1] << h[2] << endl;
				m++;
			}
		}
		cout << m << endl;
	}
	{
		cout << 10/Root(27,2).approx() << endl;
	}
}
