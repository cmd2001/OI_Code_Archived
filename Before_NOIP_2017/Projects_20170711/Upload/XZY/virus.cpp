#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

char tmp[maxn+5000],tar[maxn];
int fail[maxn+5000];
int n,m,ans;

inline void getFail(char *P,int *f)
{
    //debug<<"len="<<strlen(P)<<endl;
	int n=strlen(P);
	f[0]=f[1]=0;
	for(int i=1;i<n;i++)
	{
		int j=f[i];
		while(j&&P[i]!=P[j]) j=f[j];
		f[i+1]=(P[j]==P[i]?j+1:0);
	}
}
inline int kmp(char *T,char *P,int *f)
{
    //debug<<"temp="<<P<<endl;
    int ret=0;
	int m=strlen(T),n=strlen(P);
	getFail(P,f);
	int j=0;
	for(int i=0;i<m;i++)
	{
		while(j&&T[i]!=P[j]) j=f[j];
		if(T[i]==P[j]) j++;
		ret=max(ret,j);
		//debug<<"i="<<i<<"j="<<j<<endl;
	}
	//debug<<"ret="<<ret<<endl;
	return ret;
}
inline int calc()
{
    int ret=0;
    for(int i=1;i<=n;i++)
    {
        ret=max(ret,kmp(tar+1,tmp+i,fail));
    }
    return ret;
}
inline void mulchar()
{
    for(int i=n+1;i<=n+m;i++) tmp[i]=tmp[i-n];
}
inline void getin()
{
    scanf("%d",&n);
    scanf("%s",tmp+1);
    scanf("%d",&m);
    scanf("%s",tar+1);
}

int main()
{
    freopen("virus.in","r",stdin);
    freopen("virus.out","w",stdout);
    getin();
    mulchar();
    ans=calc();
    printf("%d\n",ans);

    fclose(stdin);
    fclose(stdout);

    return 0;
}


