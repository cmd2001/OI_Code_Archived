#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

char in[maxn];
int fst[20],cnt[20],f[20],mvd[20],mxd[20],xv[20],n,k,tar,ans;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=(ret<<3)+(ret<<1)+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	n=getint(),k=getint();
	//debug<<"n = "<<n<<endl;
	//debug<<"k = "<<k<<endl;
	scanf("%s",in+1);
	
	for(int i=1;i<=n;i++)
	{
		cnt[(in[i]-='0')]++;
		if(!fst[in[i]]) fst[in[i]]=i;
	}
	//for(int i=0;i<10;i++) debug<<cnt[i]<<" ";debug<<endl;
	
	for(int tar=0;tar<10;tar++)
	{
		if(cnt[tar]<k) for(int delta=1,res=cnt[tar],now=0;delta<10;delta++,now=0)
		{
			if(tar-delta>=0) now+=cnt[tar-delta];
			if(tar+delta<10) now+=cnt[tar+delta];
			//if(tar==8) debug<<"cnt[8] = "<<cnt[8]<<endl;
			//if(tar==8) debug<<"delta = "<<delta<<"now = "<<now<<endl;
			if(res+now<k) f[tar]+=now*delta,mvd[tar]=mxd[tar]=delta;
			else f[tar]+=(k-res)*delta,mxd[tar]=delta,xv[tar]=k-res;
			res+=now;
			if(res>=k) break;
		}
		//if(tar==8) debug<<"mvd = "<<mvd[tar]<<"mxd = "<<mxd[tar]<<endl;
	}
	ans=0x3f3f3f3f;
	for(int i=0;i<10;i++)
		if(f[i]<ans) ans=f[i],tar=i;
		else if(f[i]==ans)
		{
			if(n==k&&i>tar) continue;
			if(i+mxd[i]<=9&&tar+mxd[tar]<=9&&i+mxd[i]<=tar+mxd[tar]&&fst[i+mxd[i]]<=fst[tar+mxd[tar]]) tar=i;
			else if(fst[i]<fst[tar]) tar=i;
			
		}
	
	//debug<<"tar = "<<tar<<endl;
	
	for(int i=1;i<=mvd[tar];i++)
		for(int j=1;j<=n;j++)
			if(in[j]==tar+i||in[j]==tar-i) in[j]=tar;
	int cnt=0;
	//debug<<"xv = "<<xv[tar]<<endl;
	if(tar+mxd[tar]<10)
		for(int i=1;i<=n&&cnt<xv[tar];i++)
			if(in[i]==tar+mxd[tar]) in[i]=tar,cnt++;
	if(tar-mxd[tar]>=0)
		for(int i=n;i&&cnt<xv[tar];i--)
			if(in[i]==tar-mxd[tar])
				in[i]=tar,cnt++;
	
	//debug<<"ans = "<<ans<<endl;
	printf("%d\n",ans);
	for(int i=1;i<=n;i++) printf("%d",in[i]);
	putchar('\n');
	
	return 0;
}
