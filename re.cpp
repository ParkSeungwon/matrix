#include<iostream>
#include<string>
using namespace std;
int main(int argc, char** argv)
{
	if(argc < 2) return 0;
	std::string s = "./card.x | grep " + string(argv[1]);
	for(int i=0; i<5000; i++) system(s.c_str());
}
