#include <cstdio>
#include <algorithm>
#define N 100010
using namespace std;
int fa[N] , c[2][N] , si[N] , sum[N] , rev[N];
char str[5];
void pushup(int x)
{
    sum[x] = sum[c[0][x]] + sum[c[1][x]] + si[x] + 1;
}
void pushdown(int x)
{
    if(rev[x])
    {
        int l = c[0][x] , r = c[1][x];
        swap(c[0][l] , c[1][l]) , swap(c[0][r] , c[1][r]);
        rev[l] ^= 1 , rev[r] ^= 1 , rev[x] = 0;
    }
}
bool isroot(int x)
{
    return c[0][fa[x]] != x && c[1][fa[x]] != x;
}
void update(int x)
{
    if(!isroot(x)) update(fa[x]);
    pushdown(x);
}
void rotate(int x)
{
    int y = fa[x] , z = fa[y] , l = (c[1][y] == x) , r = l ^ 1;
    if(!isroot(y)) c[c[1][z] == y][z] = x;
    fa[x] = z , fa[y] = x , fa[c[r][x]] = y , c[l][y] = c[r][x] , c[r][x] = y;
    pushup(y) , pushup(x);
}
void splay(int x)
{
    update(x);
    while(!isroot(x))
    {
        if(!isroot(fa[x])) rotate(fa[x]);
        rotate(x);
    }
}
void access(int x)
{
    int t = 0;
    while(x) splay(x) , si[x] += sum[c[0][x]] - sum[t] , c[0][x] = t , pushup(x) , t = x , x = fa[x];
}
void makeroot(int x)
{
    access(x) , splay(x) , swap(c[0][x] , c[1][x]) , rev[x] = 1;
}
void split(int x , int y)
{
    makeroot(x) , makeroot(y);
}
void link(int x , int y)
{
    split(x , y) , fa[x] = y , si[y] += sum[x] , pushup(y);
}
int main()
{
    int n , m , i , x , y;
    scanf("%d%d" , &n , &m);
    for(i = 1 ; i <= n ; i ++ ) sum[i] = 1;
    while(m -- )
    {
        scanf("%s%d%d" , str , &x , &y);
        if(str[0] == 'A') link(x , y);
        else split(x , y) , printf("%lld\n" , (long long)sum[x] * (sum[y] - sum[x]));
    }
    return 0;
}
