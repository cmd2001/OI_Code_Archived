#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int in[maxn][maxn];
int dep[maxn][maxn];
int stk[maxn],h[maxn],len[maxn],top;
int n,m,ans;

inline int pop() // returning added length of new stack top.
{
    if( !top )
        return 0;
    int ret = len[top];
    ans = max( ans , h[top] * len[top] );
    h[top] = len[top] = 0;
    --top;
    return ret;
}

inline void push(int height,int length)
{
    if( height == h[top] )
    {
        len[top] += length;
        return;
    }
    ++top;
    h[top] = height;
    len[top] = length;
}

inline void calc(int* in)
{
    for(int i=1;i<=m;i++)
    {
        int nw = 1;
        while( top && h[top] > in[i] )
        {
            int add = pop();
            if( top && h[top] > in[i] )
                len[top] += add;
            else
                nw += add;
        }
        push(in[i],nw);
    }
    while( top )
    {
        int add = pop();
        if( top )
            len[top] += add;
    }
}

inline void pre()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] )
                in[i][j] += in[i-1][j] ;
            else
                in[i][j] = 0;
}

inline char realchar()
{
    char ret = getchar();
    while( ret != 'R' && ret != 'F' )
        ret = getchar();
    return ret;
}

int main()
{
    freopen("_9.in","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            in[i][j] = ( realchar() == 'F' );
    
    pre();
    
    for(int i=1;i<=n;i++)
        calc(in[i]);
    
    printf("%d\n",ans*3);
    
    return 0;
}