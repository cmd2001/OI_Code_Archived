#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,k,ans;
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	while(n)
	{
		n/=(m+1);k++;
	}
	cout<<k*m<<endl;
	fclose(stdin);
	fclose(stdout);
}
