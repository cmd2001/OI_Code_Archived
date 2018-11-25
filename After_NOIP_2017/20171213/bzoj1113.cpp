#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=2.5e5+1e2;

int stk[maxn],top;
int n,ans,xx;

inline void pop(int xx)
{
    while( stk[top] > xx )
        --top;
}

inline int getint()
{
    int ret = 0 , fix = 1;
    char ch = getchar();
    if( ! isdigit(ch) )
        fix = ch == '-' ? -1 : fix,
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ),
        ch = getchar();
    return ret * fix;
}

int main()
{
    ans = n = getint();
    stk[0]=-0x3f3f3f3f;
    
    while( n-- )
    {
        getint();
        xx = getint();
        pop(xx);
        if( stk[top] == xx )
            --ans;
        stk[++top] = xx;
    }
    
    printf("%d\n",ans);
    
    return 0;
}

