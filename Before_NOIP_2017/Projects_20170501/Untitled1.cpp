#include<bits/stdc++.h>
using namespace std;
const int maxn=3e2+1e1;
int in[maxn][maxn],ans[maxn][maxn],n;
int getint()
{
    int ret=0,fix=1;
    char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-') fix=-1;  ch=getchar();}
    while(ch>='0'&&ch<='9')
    {
        ret=ret*10+ch-'0';
        ch=getchar();
    }
    return ret*fix;
}
int main()
{
    n=getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) in[i][j]=getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) ans[i][j]+=in[i][k]*in[j][k];
    for(int i=1;i<=n;i++) { for(int j=1;j<=n;j++) printf("%d ",ans[i][j]); putchar('\n');}
    return 0;
}
