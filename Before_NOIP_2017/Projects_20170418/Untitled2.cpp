#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
int in[maxn],a[maxn],b[maxn],ad,bd,k,n,cnt,asd;
char ans[2*maxn];
bool check(int k)
{
    if(!bd) return 1;
    int i,j;
    for(i=k+1;i<=n;i++) if(in[i]>in[k]&&in[i]>b[bd]) break;
    for(j=i+1;j<=n;j++) if(in[j]<in[k]) return 0;
    return 1;
}
bool dfs(int at)
{
    if(asd>n) return 1;
    if(a[ad]==asd)
    {
        ad--,asd++;
        ans[++cnt]='b';
        return dfs(at);
    }
    if(b[bd]==asd)
    {
        bd--,asd++;
        ans[++cnt]='d';
        return dfs(at);
    }
    if(at<=n&&in[at]<a[ad]&&check(at))
    {
        a[++ad]=in[at];
        ans[++cnt]='a';
        return dfs(at+1);
    }
    if(at<=n&&in[at]<b[bd])
    {
        b[++bd]=in[at];
        ans[++cnt]='c';
        return dfs(at+1);
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
/*
bool check(int k)
{
    if(!bd) return 1;
    int x,j;
    for(x=k+1;x<=n;x++) if(in[x]>in[k]&&in[x]>b[bd]) break;
    for(j=x+1;j<=n;j++) if(in[j]<in[k]) return 0;
    return 1;
}

这是在检查第k个元素能否进入a栈。
我们用反证法，假设他能进入a栈。
现在我们考虑，他进入a栈后，是否会有矛盾。
首先，找到它后面第一个比他大(不能再他后进入a栈)，并且大于b栈栈顶的元素x。如果有这种东西，那么这个x不能在k弹出前进栈。
但是，如果k早就在x尝试进栈前被弹出了的话，x还是可以进栈的。
所以，我们从x+1开始寻找是否有小于k的元素，如果找不到，则k早就在尝试进栈x前被弹出了。
那么x步骤有解。
则k可以进入a栈。

另外，如果k不能进入a栈的话，就必须进入b栈。所以，按照先弹出，进a，进b的顺序进行尝试，是不需要回溯的！
总时间复杂度O(n*n)，过1000的数据量绰绰有余。
*/

