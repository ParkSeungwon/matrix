#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using namespace std::placeholders;

class A
{
	public:
		vector<int> v;
		bool comp(int a, int b) {
			return count(v.begin(), v.end(), a) > count(v.begin(), v.end(), b);
		}
		bool f2(int a, int b) { return a > b;}

};

bool f(int a, int b) { cout << a << ' ' << b; return a > b;}

int main()
{
	A a;
	vector<int> v;
	for(int i=0; i<10; i++) {
		v.push_back(i);
		a.v.push_back(i);
	}
	auto ff = bind(&A::f2, &a, 3, 4);
	ff();
	sort(v.begin(), v.end(), bind(&A::f2, &a, _1, _2));//bind(&A::comp, a));
	for(auto& a : v) cout << a;
}
