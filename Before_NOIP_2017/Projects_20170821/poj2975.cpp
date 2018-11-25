#include<cstdio>
using namespace std;
const int maxn=1e3+1e2;

int in[maxn],n,x,ans;

int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		ans=x=0;
		for(int i=1;i<=n;i++) scanf("%d",in+i),x^=*(in+i);
		
		for(int i=1;i<=n;i++)
			ans+=((x^in[i])<in[i]);
		
		printf("%d\n",ans);
		
	}
	
	return 0;
}
