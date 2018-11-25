#include<bits/stdc++.h>
using namespace std;
const int maxn=1e4+1e2;
struct node
{
	int h,w,pos;
	friend bool operator < (const node &a,const node &b) {return a.h==b.h?a.w<b.w:a.h<b.h;}
}sta[maxn];
int n;
long long int ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&sta[i].h,&sta[i].w),sta[i].pos=i;
	stable_sort(sta+1,sta+1+n);
	for(int i=1;i<=n;i++) ans+=abs(i-sta[i].pos);
	printf("%lld\n",ans);
	return 0;
}
