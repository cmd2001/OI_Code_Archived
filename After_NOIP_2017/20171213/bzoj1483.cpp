#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int in[maxn],sou[maxn],siz[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int n,m,ans;

inline void insert(int from,int to)
{
    static int cnt = 0;
    t[++cnt] = to,
    nxt[cnt] = s[from];
    s[from] = cnt;
}

inline void merge(int a,int b) // merge a into b and calc the size.
{
    int fin;
    for(int at=s[a];at;at=nxt[at])
    {
        if( in[t[at]-1] == b ) --ans;
        if( in[t[at]+1] == b ) --ans;
    }
    for(int at=s[a];at;fin=at,at=nxt[at])
        in[t[at]] = b;
    nxt[fin] = s[b] , s[b] = s[a];
    siz[b] += siz[a], siz[a] = 0;
}

inline void work(int a,int b)
{
    if( a == b )
        return;
    if( siz[sou[a]] > siz[sou[b]] )
        swap(sou[a],sou[b]);
    a = sou[a] , b = sou[b];
    if( !siz[a] )
        return;
    merge(a,b);
}

inline int getint()
{
    int ret = 0 , fix = 1;
    char ch = getchar();
    while( ! isdigit(ch) )
        fix = ch == '-' ? -1 : 1,
        ch = getchar();
    while( isdigit(ch) )
        ret = ret * 10 + ( ch - '0' ),
        ch = getchar();
    return ret * fix;
}

int main()
{
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
    {
        in[i] = getint(),
        ans += ( in[i] != in[i-1] );
        insert(in[i],i);
        sou[in[i]] = in[i];
        ++siz[in[i]];
    }
    
    for(int i=1,q,a,b;i<=m;i++)
    {
        q = getint();
        if( q == 2 )
            printf("%d\n",ans);
        else
        {
            a = getint() , b = getint();
            work(a,b);
        }
    }
    return 0;
        
}