#include<bits/stdc++.h>
using namespace std;
long long int h[20],n;
int main()
{
	h[1]=1;
	scanf("%d",&n);
	for(int i=2;i<=n;i++) h[i]=h[i-1]*(4*i-2)/(i+1);
	cout<<h[n]<<endl;
	return 0;
}
