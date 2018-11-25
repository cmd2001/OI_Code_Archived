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
		debug<<"unt1 working"<<endl;
		t1=clock();
		system("Untitled1.exe < in.txt > o1.txt");
		t2=clock();
		debug<<"unt1 finished"<<endl;
		system("std.exe < in.txt > o2.txt");
		if(system("fc o1.txt o2.txt"))system("pause");
		printf("Time Used=%f s\n",(float)(t2-t1)/CLOCKS_PER_SEC);
	}
	return 0;
}

