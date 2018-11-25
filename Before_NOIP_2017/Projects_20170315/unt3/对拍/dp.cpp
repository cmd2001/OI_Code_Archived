#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include<ctime>
#define debug cout
using namespace std;
int main(){
	int lala=0;
	int t1,t2;
	while(true){
		cout<<++lala<<endl;
		system("maker.exe > in.txt");
		t1=clock();
		system("Untitled3.exe < in.txt > o1.txt");
		t2=clock();
		debug<<"unt3"<<endl;
		system("std.exe < in.txt > o2.txt");printf("lala\n");
		if(system("fc o1.txt o2.txt"))system("pause");
		printf("Time Used=%f s\n",(float)(t2-t1)/CLOCKS_PER_SEC);
	}
	return 0;
}

