#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include"magic.h"
#include"matrix.cc"
#include"combi.h"
using namespace std;

MagicSquare::MagicSquare(int w) : Matrix<int>(w, w)
{
	line_sum = width * (1 + width * width) / 2;
	for(int i=0; i<width*width; i++) nums.push_back(i+1);
}

MagicSquare::MagicSquare(vector<vector<int>> v) : Matrix<int>(v) {
	line_sum = width * (1 + width * width) / 2;
}

void MagicSquare::build()
{
	vector<int> v;
	int sz = nums.size();
	if(sz == 0) {
		if(full_check()) {
			show();
			cout << endl;
		}
	} else {
		nPr p(sz, width);
		while(p.next()) {
			int sum = 0;
			for(int i=0; i<width; i++) sum += nums[p[i]-1];
			if(sum == line_sum) {
				for(int i=0; i<width; i++) {
					v.push_back(nums[p[i]-1]);
					arr[width*width-sz + i] = nums[p[i]-1];
				}
				auto it = remove_if(nums.begin(), nums.end(), [&v](int a) {
						return find(v.begin(), v.end(), a) != v.end();});
				nums.erase(it, nums.end());
				build();
				nums.insert(nums.end(), v.begin(), v.end());
				v.clear();
				sort(nums.begin(), nums.end());
			}
		}
	}
}

int MagicSquare::add_line(int n)
{
	int sum = 0;
	for(int x=0; x<width; x++) sum += arr[n*width+x];
	return sum;
}

int MagicSquare::add_row(int n)
{
	int sum = 0;
	for(int y=0; y<height; y++) sum += arr[y*width+n];
	return sum;
}

int MagicSquare::add_criss()
{
	int sum = 0;
	for(int x=0, y=0; x<width; x++, y++) sum += arr[y*width+x];
	return sum;
}

int MagicSquare::add_cross()
{
	int sum = 0;
	for(int x=width-1, y=0; y<height; x--, y++) sum += arr[y*width+x];
	return sum;
}

bool MagicSquare::full_check()
{
	if(add_criss() != line_sum) return false;
	if(add_cross() != line_sum) return false;
	for(int x=0; x<width; x++) {
	//	if(line_sum != add_line(x)) return false;
		if(line_sum != add_row(x)) return false;
	}
	return true;
}

