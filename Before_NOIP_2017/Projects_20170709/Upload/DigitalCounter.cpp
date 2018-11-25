#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=20;

const int refer[]={6,2,5,5,4,5,6,3,7,5};
int in[maxn],cur[maxn],n,c;
lli org,ans;
bool flag;

inline lli convert(int *dst)
{
    lli ret=0;
    for(int i=1;i<=n;i++) ret=ret*10+dst[i];
    return ret;
}
inline int cont(int *dst)
{
    int ret=0;
    for(int i=1;i<=n;i++) ret+=refer[dst[i]];
    return ret;
}
inline bool dfs(int pos,int tar)
{
    if(pos>n&&tar==0) return 1;
    if(tar<0||(n-pos+1)*7<tar) return 0;
    for(int i=in[pos];i<10;i++)
    {
        cur[pos]=i;
        if(dfs(pos+1,tar-refer[i])) return 1;
    }
    return 0;
}
inline char nextchar()
{
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    return ch;
}
inline void fix()
{
    for(int i=n;i;i--)
    {
        in[i-1]+=in[i]/10;
        in[i]%=10;
    }
    flag=in[0];
}
int main()
{
    freopen("DigitalCounter.in","r",stdin);
    freopen("DigitalCounter.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) in[i]=nextchar()-'0';
    org=convert(in);
    c=cont(in);
    in[n]++;
    fix();
    if((!dfs(1,c))||flag)
    {
        memset(in,0,sizeof(in));
        dfs(1,c);
        ans=convert(cur);
        ans+=pow(10,n);
        ans-=org;
        printf("%lld\n",ans);
    }
    else printf("%lld\n",convert(cur)-org);

    fclose(stdin);
    fclose(stdout);

    return 0;
}

