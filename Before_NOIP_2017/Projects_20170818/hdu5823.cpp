#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=(1<<18)+1;

unsigned f[maxn],ans=0;
int g[maxn],n,m,d;
bool ok[maxn];
char s[20];

inline unsigned fastpow(int tme)
{
    unsigned ret=1,now=233;
    while(tme)
    {
        if(tme&1) ret*=now;
        now*=now;
        tme>>=1;
    }
    return ret;
}

inline void judge_ok()
{
    for(unsigned i=0;i<d;i++)
    {
        ok[i]=1;
        for(unsigned k=1;k<=n;k++)
        if((i&(1<<(k-1)))&&(i&g[k]))
        {
            ok[i]=0;
            break;
        }
    }
}

inline unsigned getf()
{
    for(int i=1;i<d;i++)
    {
        unsigned t=0x3f3f3f3f;
        for(int ss=i;ss;ss=(ss-1)&i)
            if(ok[ss])
                t=min(t,f[i^ss]+1);
        f[i]=t;
        //printf("f[%d]=%d\n",i,t);
        ans+=t*fastpow(i);
    }
}


int main()
{
    static int t;
    scanf("%d",&t);
    while(t--)
    {
        memset(g,0,sizeof(g));
        memset(ok,0,sizeof(ok));
        memset(f,0,sizeof(f));
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s+1);
            for(int j=1;j<=n;j++) g[i]|=((s[j]-'0')<<(j-1));
        }

        d=1<<n;

        judge_ok();


        getf();

        printf("%u\n",ans);
    }

    return 0;
}
