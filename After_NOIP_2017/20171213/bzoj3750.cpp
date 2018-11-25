#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int in[maxn][maxn];
int mrk[maxn][maxn];
int sdx,sdy;
int sx,sy,tx,ty;
vector<int> xx,yy;
int n,m,a,b,siz;
char buf[maxn];

inline bool prejudge(int xx,int yy)
{
    if( xx - ( sdx - sx ) < 1 || yy - ( sdy - sy ) < 1 )
        return 0;
    if( xx + ( tx - sdx ) > n || yy + ( ty - sdy ) > m )
        return 0;
    return 1;
}

inline bool fil(int sx,int sy)
{
    if( !prejudge(sx,sy) )
        return 0;
    for(int i=0;i<siz;i++)
        if( !in[sx+xx[i]][sy+yy[i]] )
            return 0;
        else
            in[sx+xx[i]][sy+yy[i]] = 0;
    return 1;
}

inline bool work()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] )
                if( !fil(i,j) )
                    return 0;
    return 1;
}


inline void build()
{
    for(int i=0;i<a;i++)
        for(int j=0;j<b;j++)
            if( mrk[i][j] )
                sx = min( sx , i ),
                sy = min( sy , j ),
                tx = max( tx , i ),
                ty = max( ty , j );
    
    for(int i=0;i<a&&sdx==-1&&sdy==-1;i++)
        for(int j=0;j<b&&sdx==-1&&sdy==-1;j++)
            if( mrk[i][j] )
            {
                sdx = i,
                sdy = j;
            }
    
    for(int i=0;i<a;i++)
        for(int j=0;j<b;j++)
            if( mrk[i][j] )
                xx.push_back( i - sdx ),
                yy.push_back( j - sdy ),
                ++siz;
    /*debug<<"sx = "<<sx<<"sy = "<<sy<<"tx = "<<tx<<"ty = "<<ty<<endl;
    debug<<"sdx = "<<sdx<<"sdy = "<<sdy<<endl;*/
}

inline void init()
{
    n = m = a = b = siz = 0;
    sx=maxn,sy=maxn,tx=-1,ty=-1;
    sdx = sdy = -1;
    memset(in,0,sizeof(in));
    memset(mrk,0,sizeof(mrk));
    xx.clear(),yy.clear();
}

int main()
{
    static int T;
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d%d%d%d",&n,&m,&a,&b);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",buf+1);
            for(int j=1;j<=m;j++)
                in[i][j] = buf[j] == 'x';
        }
        for(int i=0;i<a;i++)
        {
            scanf("%s",buf);
            for(int j=0;j<b;j++)
                mrk[i][j] = buf[j] == 'x';
        }
        build();
        puts(work()?"TAK":"NIE");
    }
    return 0;
}
