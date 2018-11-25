#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
int delta[maxn],ope[maxn],m,n,sum,a,b;
int x[maxn],f[maxn],t[maxn];
bool test(int pos)
{
	bool able=1;
	long long int sum=0;
    memcpy(ope,delta,sizeof(ope));
    for(int i=1;i<=pos;i++)
    {
        ope[f[i]]-=x[i];
        ope[t[i]+1]+=x[i];
    }
    for(int i=1;i<=n;i++)
    {
        sum+=ope[i];
        if(sum<0) {able=0;break;}
    }
    return able;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        delta[i]=a-b;
        b=a;
    }
    for(int i=1;i<=m;i++) scanf("%d%d%d",x+i,f+i,t+i);
    int ll=0,rr=m+1,mid=(ll+rr)>>1;
    do
    {
    	if(test(mid)) ll=mid;
    	else rr=mid;
		mid=(ll+rr)>>1;
    }
    while(ll!=mid);
    if(rr>m) printf("0\n");
    else puts("-1"),printf("%d\n",rr);
    return 0;
}



