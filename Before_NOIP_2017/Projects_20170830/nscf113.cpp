#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e4+5;
const int maxl=32;
const int maxk=26;

int f[maxn][maxk][maxl];
short nxt[maxn][maxk][maxl];
char str[120005];

int n,k,mod,ans;

inline void gen()
{
	for(int i=1;i<32;i++)
		for(int j=1;j<=n;j++)
			for(int kk=0;kk<k;kk++)
			{
				f[j][kk][i]=(f[j][kk][i-1]+f[nxt[j][kk][i-1]][kk][i-1])%mod,
				nxt[j][kk][i]=nxt[nxt[j][kk][i-1]][kk][i-1];
				//printf("f[%d][%d][%d]=%d\n",j,kk,i,f[j][kk][i]);
			}
}
inline int core_move(int &pos,int step,int k)
{
	int ret=0;
	for(int i=30;i>=0;i--)
	{
		//debug<<"in move i="<<i<<endl;
		if(step&(1<<i))
		{
			step-=(1<<i);
			//debug<<"pos="<<pos<<"k="<<k<<"i="<<i<<endl;
			ret=(ret+f[pos][k][i])%mod;
			pos=nxt[pos][k][i];
		}
	}
	return ret;
}
inline void calc()
{
	int len=strlen(str+1),pos=1,l,tmp;
	
	for(int i=1;i<=len;)
	{
		//debug<<"i="<<i<<endl;
		if(str[i]=='[')
		{
			l=0,i++;
			while(str[i]>='0'&&str[i]<='9') l=l*10+(str[i]-'0'),i++;
			tmp=core_move(pos,l,str[i]-'A');
			ans=(ans+tmp)%mod;
			i+=2;
		}
		else if(str[i]>='A'&&str[i]<='Z')
		{
			tmp=core_move(pos,1,str[i]-'A');
			ans=(ans+tmp)%mod;
			i++;
		}
	}
}
			
				
		
		

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	n=getint(),k=getint();
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<k;j++)
			nxt[i][j][0]=getint(),f[i][j][0]=getint();
	}
	scanf("%s",str+1);
	mod=getint();
	
	gen();
	
	calc();
	
	printf("%d\n",ans);
	
	return 0;
}
