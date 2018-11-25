#include<bits/stdc++.h>
using namespace std;

int main()
{
	freopen("arg.txt","r",stdin);
	
	int len;
	
	srand(time(NULL));
	
	cin>>len;
	
	for(int i=1;i<=len;i++) cout<<rand()%10;
	cout<<endl;
	for(int i=1;i<=len;i++) cout<<rand()%10;
	cout<<endl;
	
	return 0;
}
