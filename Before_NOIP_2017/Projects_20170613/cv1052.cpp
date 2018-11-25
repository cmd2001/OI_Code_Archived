#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+1e1;

int tme[maxn],val[maxn],n,ans,maxt;
bool vis[maxn];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",tme+i),maxt=max(maxt,tme[i]);
	for(int i=1;i<=n;i++) scanf("%d",val+i);
	for(int i=maxt,p;i>0;i--)
	{
		p=0;
		for(int k=1;k<=n;k++) if(tme[k]>=i&&val[k]>val[p]&&!vis[k]) p=k;
		vis[p]=1;
		ans+=val[p];
	}
	printf("%d\n",ans);
}
