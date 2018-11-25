#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int in[maxn],n,ans;
int f[maxn],tar[maxn],len=1;

int upper(int x)
{
	int ll=1,rr=len,mid;
	while(rr>ll+1)
	{
		mid=(ll+rr)>>1;
		if(tar[mid]>x) ll=mid+1;
		else rr=mid;
	}
	return ll;
}

int main()
{
	//freopen("ark1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",in+i);
	
	memset(f,0x3f,sizeof(f));
	
	f[n+1]=0,tar[1]=n+1;
	
	
	cout<< ans <<endl;
	
	return 0;
}
