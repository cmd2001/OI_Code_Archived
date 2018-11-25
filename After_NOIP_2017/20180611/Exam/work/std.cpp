#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
#define lli long long int
using namespace std;
const int maxn=1e6+1e4;
const int mod=1e9+7;

lli c[maxn][4];
lli ans;
int n,m;

int gcd(int x,int y)
{
    register int t;
    while(t=x%y)
        x=y,y=t;
    return y;
}
inline void genc()
{
    c[0][0]=1;
    for(int i=1;i<=n*m;i++)
    {
        c[i][0]=1;
        if(i<=3) c[i][i]=1;
        for(int j=1;j<=3&&j<i;j++)
            c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
}
inline void getans()
{
    ans = c[n*m][3];
    ans -= m*c[n][3] + n*c[m][3];
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++)
        {
            int g = gcd(i,j);
            ans += ( n - i ) * ( m - j ) * 2;
            ans -= g * ( n - i ) * ( m - j ) * 2;
        }
}

int main()
{
    scanf("%d%d",&n,&m);
    n++ , m++;
      
    genc();
    getans();
      
    printf("%lld\n",ans%mod);
      
    return 0;
}