#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

char tmp[maxn],tar[maxn];
int fail[maxn];
int n,m;

inline void getfail(char *p,int *f)
{
    memset(f,0,sizeof(f));
    int n=strlen(p);
    f[0]=f[1]=0;
    for(int i=1;i<n;i++)
    {
        int j=f[i];
        while(j&&p[i]!=p[j]) j=f[j];
        f[i+1]=(p[i]==p[j]?j+1:0);
    }
}
inline int kmp(char *t,char *p,int *f)
{
    int m=strlen(t),n=strlen(p),ret=0;
    getfail(p,f);
    int j=0;
    for(int i=1;i<m;i++)
    {
        while(j&&t[i]!=p[j]) j=f[j];
        if(t[i]==p[j]) j++;
        ret=max(ret,j);
		debug<<"i="<<i<<"j="<<j<<endl;
    }
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
    getin();
    mulchar();
    debug<<calc()<<endl;
    return 0;
}

