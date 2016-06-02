#include<iostream>
#include<cmath>
#include<algorithm>
#include"magic.h"
#include"matrix.cc"
#include"combi.h"
using namespace std;

//unsigned MagicSquare::found = 0;
//unsigned MagicSquare::to_find = 0;
//Char2D MagicSquare::result = {};

MagicSquare::MagicSquare(int w) : Matrix<int>(w, w)
{
	line_sum = width * (1 + width * width) / 2;
	for(int i=0; i<width*width; i++) nums.push_back(i+1);
}

MagicSquare::MagicSquare(vector<vector<int>> v) : Matrix<int>(v) {
	line_sum = width * (1 + width * width) / 2;
}

//void MagicSquare::build()
//{
//	if(width == 3 || width == 4) {
//		vector<int> s;
//		for(int i=1; i<=width*width; i++) s.insert(i);
//		auto p = partial_nPr();
//		while(p.next()) {
//			int sum = 0;
//			for(int i-0; i<p.size(); i++) sum += p[i];
//			if(sum == line_sum) {
//				for(int i-0; i<p.size(); i++) s.erase(p[i]);
//			while(
//			for(int y=0, i=0; y<width; y++) {
//				for(int x=0; x<width; x++) {
//					arr[y][x] = p[i++];
//				}
//				if(add_line(y) != line_sum) break;
//				else if(y == width-1 && full_check()) show();
//			}
//		}
//	}
//}

void MagicSquare::partial_nPr()
{
	nPr p(nums.size(), width);
	while(p.next()) {
		int sum = 0;
		for(int i=0; i<width; i++) sum += nums[p[i]-1];
		if(sum == line_sum) {
			if(nums.size() == width) {
				if(full_check()) show();
			} else {
				vector<int> v;
				for(int i=0; i<width; i++) v.push_back(nums[p[i]-1]);
				nums.erase(remove_if(nums.begin(), nums.end(), [&v](int a) {
						return find(v.begin(), v.end(), a) != v.end();}), nums.end());
				parts.push_back(v);
				partial_nPr();
			}
		}
	}
	for(auto& a : parts.back()) nums.push_back(a);
	parts.pop_back();
	sort(nums.begin(), nums.end());
}



int MagicSquare::add_line(int n)
{
	int sum = 0;
	for(int x=0; x<width; x++) sum += arr[n][x];
	return sum;
}

int MagicSquare::add_row(int n)
{
	int sum = 0;
	for(int y=0; y<height; y++) sum += arr[y][n];
	return sum;
}

int MagicSquare::add_criss()
{
	int sum = 0;
	for(int x=0, y=0; x<width; x++, y++) sum += arr[y][x];
	return sum;
}

int MagicSquare::add_cross()
{
	int sum = 0;
	for(int x=width-1, y=0; y<height; x--, y++) sum += arr[y][x];
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

