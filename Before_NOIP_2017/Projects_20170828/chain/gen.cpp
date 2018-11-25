#include<bits/stdc++.h>
using namespace std;

int r()
{
	return rand()+rand()<<15;
}

int main()
{
	srand(time(0));
	//freopen("arg.txt","r",stdin);
	int k;
	cin>>k;
	if(k<=10) k*=100;
	else k*=5000;
	
	for(int i=1;i<=k;i++)
	{
		printf("%d\n",r()%4999999+1);
	}
	printf("0\n");
	
	fclose(stdout);
	
	return 0;
}
