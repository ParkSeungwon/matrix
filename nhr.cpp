#include"combi.h"
#include<iostream>
#include<map>
using namespace std;

int main(int c, char** v)
{
	if(c < 3) return 0;
	int x = atoi(v[1]);
	int y = atoi(v[2]);
	nHr nhr(y, x-y);
	map<int, int> m;
	while(nhr.next()) {
		for(int i=1; i<=y; i++) m[i]++;
		for(int i=0; i<nhr.size(); i++) m[nhr[i]]++;
		for(auto& a : m) cout << a.second << ',';
		cout << endl;
		m.clear();
	}
}
