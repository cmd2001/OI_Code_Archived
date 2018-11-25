#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
int in[maxn],a[maxn],b[maxn],ad,bd,k,n,cnt,asd;
char ans[2*maxn];
inline bool check(int k)
{
    if(!bd) return 1;
    int i,j;
    for(i=k+1;i<=n;i++) if(in[i]>in[k]&&in[i]>b[bd]) break;
    for(j=i+1;j<=n;j++) if(in[j]<in[k]) return 0;
    return 1;
}
int main()
{
    bool able=1;
    int at=1;
    scanf("%d",&n);
    a[0]=b[0]=1e4,asd=1;
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=(n<<1);i++)
    {
        if(a[ad]==asd)
        {
            ad--,asd++;
            ans[++cnt]='b';
            continue;
        }
        if(b[bd]==asd)
        {
            bd--,asd++;
            ans[++cnt]='d';
            continue;
        }
        if(at<=n&&in[at]<a[ad]&&check(at))
        {
            a[++ad]=in[at];
            ans[++cnt]='a';
            at++;
            continue;
        }
        if(at<=n&&in[at]<b[bd])
        {
            b[++bd]=in[at];
            ans[++cnt]='c';
            at++;
            continue;
        }
        able=0;break;
    }
    if(able) for(int i=1;i<=cnt;i++) putchar(ans[i]),putchar(' ');
    else putchar('0');
    putchar('\n');
    return 0;
}
