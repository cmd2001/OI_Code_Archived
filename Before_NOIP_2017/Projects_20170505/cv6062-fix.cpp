#include<cstdio>
using namespace std;
const int maxn=1e5+1e2;
int in[maxn],cnt[3][maxn],sum[3],n,ans=3;
int getint()
{
    int ret=0;
    char ch=getchar();
    while(ch>'9'||ch<'0') ch=getchar();
    while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
int main()
{
    n=getint();
    for(int i=1,tmp;i<=n;i++)
    {
        tmp=getint();
        for(int j=0;j<3;j++) cnt[j][i]=cnt[j][i-1];
        ++cnt[tmp][i],++sum[tmp];
    }
    for(int i=0;i<3;i++) sum[i]>>=1;
    n>>=1;
    for(int i=0;i<n;i++)
    {
        if(cnt[0][i+n]-cnt[0][i]==sum[0]&&cnt[1][i+n]-cnt[1][i]==sum[1]&&cnt[2][i+n]-cnt[2][i]==sum[2])
        {
            ans=2;
            if(!i)
            {
                ans=1;
                break;
            }
        }
    }
    putchar(ans+'0');
    return 0;
}

