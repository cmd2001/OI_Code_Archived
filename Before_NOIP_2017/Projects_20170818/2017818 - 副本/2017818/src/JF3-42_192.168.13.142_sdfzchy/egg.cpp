#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
const int inf=(1<<30);
int n,m,base[1000];
int solve(int x,int y)
{
	int cnt=0;
	while(y>2&&x) x=x/2,y--,cnt++;
	if(x==0) return cnt;
	int tmp=lower_bound(base+1,base+n+1,x)-base;
	return tmp+cnt;
}
int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=1010;i++) base[i]=i*(i+1)/2;
	printf("%d\n",solve(n,m));
	return 0;
}

