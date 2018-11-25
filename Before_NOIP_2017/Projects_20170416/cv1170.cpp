#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1e2;
int a[maxn],b[maxn],ad,bd,asd,cnt,n,in[maxn];
char ans[2*maxn];
bool dfs(int at)
{
    if(asd>n) return 1;
    if(in[at]>a[ad]&&in[at]>b[bd]) return 0;
    if(a[ad]>in[at]&&at<=n)
    {
        a[++ad]=in[at];
        ans[++cnt]='a';
        if(dfs(at+1)) return 1;
        ad--,cnt--;
    }
    if(a[ad]==asd)
    {
        ad--,asd++;
        ans[++cnt]='b';
        if(dfs(at)) return 1;
        a[++ad]=--asd,cnt--;
    }
    if(b[bd]>in[at]&&at<=n)
    {
        b[++bd]=in[at];
        ans[++cnt]='c';
        if(dfs(at+1)) return 1;
        bd--,cnt--;
    }
    if(b[bd]==asd)
    {
        bd--,asd++;
        ans[++cnt]='d';
        if(dfs(at)) return 1;
        b[++bd]=--asd,cnt--;
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    a[0]=b[0]=1e4,asd=1;
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    if(dfs(1)) for(int i=1;i<=cnt;i++) putchar(ans[i]),putchar(' ');
    else putchar('0');
    putchar('\n');
    return 0;
}

