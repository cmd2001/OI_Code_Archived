#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=25;

int miv[maxn],m,v;
int ans;

void dfs(int dep,int lastr,int lasth,int leftv,int siz)
{
	if(leftv<0) return;
	//debug<<"dep="<<dep<<"lastr="<<lastr<<"lasth="<<lasth<<"leftv="<<leftv<<"siz="<<siz<<endl;
	if(!dep)
	{
		if(!leftv) ans=min(ans,siz);
		return;
	}
	
	if(miv[dep]>leftv) return;
	if(leftv/(2*lastr)+siz>ans) return;
	
	for(int i=lastr-1;i>=dep;i--)
	{
		int fix=((dep==m)?i*i:0);
		for(int h=lasth-1;h>=dep;h--)
			if(leftv-i*i*h>=0) dfs(dep-1,i,h,leftv-i*i*h,siz+fix+2*i*h);
	}
}

int main()
{
	for(int i=1;i<=20;i++) miv[i]=miv[i-1]+i*i*i;
	
	scanf("%d%d",&v,&m);
	
	ans=0x3f3f3f3f;
	
	dfs(m,sqrt(v/m)+1,v/(m*m)+1,v,0);
	
	printf("%d\n",ans);
	
	return 0;
}
