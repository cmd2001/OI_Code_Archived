#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const char ans[][10]={"sunday","monday","tuesday","wednesday","thursday","friday","saturday"};
int y,m,d,c,lam;

int main()
{
	scanf("%d%d%d",&y,&m,&d);
	if(m<=2) m+=12,y--;
	c=y/100;
	y%=100;
	
	lam=(y+(y/4)+((c/4)-c*2+(13*(m+1)/5)+d-1))%7;
	if(lam<0) lam+=7;
	
	puts(ans[lam]);
	
	return 0;
}
	
