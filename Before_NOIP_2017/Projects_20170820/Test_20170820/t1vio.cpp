#include<bits/stdc++.h>
#define lli long long int
using namespace std;

inline int calc(lli x)
{
	int ret=0;
	lli sq=sqrt(x);
	
	for(int i=1;i<=sq;i++)
		if(!(x%i)) ret+=2;
	
	if(sq*sq==x) --ret;
	
	return ret;
}
int ans,cnt,n;

int main()
{
	freopen("dat.txt","r",stdin);
	freopen("vio.txt","w",stdout);
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		int c=calc(i);
		if(c>cnt) cnt=c,ans=i;
	}
	
	printf("%d\n",ans);
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
	
