#include<vector>
#include<algorithm>
#include<iostream>
#include"combi.h"
using namespace std;

int main()
{
	vector<int> list {1,2,1,3,1,4,4};
	vector<int> to_remove {1,1,4};
	vector<int> index;
	for(int i=0; i<list.size(); i++) {
		if(find(to_remove.begin(), to_remove.end(), list[i]) != to_remove.end())
			index.push_back(i);//insert index
	}
	bool sequence;
	nCr ncr(index.size(), to_remove.size());
	while(ncr.next()) {
		sequence = true;
		for(int i=0; i<to_remove.size(); i++) 
			if(list[index[ncr[i]-1]] != to_remove[i]) sequence = false;
		if(sequence) {
			for(int i=0, j=0; i<list.size(); i++) {
				if(i == index[ncr[j]-1]) j++;
				else cout << list[i] << ' ';
			}
			cout << endl;
		}
	}
}
