#include<bits/stdc++.h>
using namespace std;
unsigned long long int n,x,y;
long long int mid;
int main()
{
	cin>>n>>x>>y;
	//if(n==9&&x==4&&y==32) {puts("8");return 0;}
	mid=n-ceil((double)y/x);
	cout<<max((long long)0,mid)<<endl;
	return 0;
}
