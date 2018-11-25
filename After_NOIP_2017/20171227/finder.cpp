#include<bits/stdc++.h>
using namespace std;

char mm[10],ss[10];
int main() {
	FILE *my = fopen("my.txt","r") , *std = fopen("std.txt","r");
	for(int i=1;i<=200000;i++) {
		fscanf(my,"%s",mm),fscanf(std,"%s",ss);
		if( *mm != *ss ) {
			printf("%d\n",i);
			puts("std::"),puts(ss);
			puts("my::"),puts(mm);
			system("pause");
		}
	}
}
