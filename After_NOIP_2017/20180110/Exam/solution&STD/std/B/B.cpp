#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;

struct Matrix
{
    long long a[9][9];
}ma;
Matrix mull(Matrix a,Matrix b)
{
    Matrix ans;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            ans.a[i][j]=0;
            for(int k=0;k<9;k++)
                ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
        }
    }
    return ans;
}
Matrix fast(long long ci,Matrix num)
{
    Matrix ans;
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        ans.a[i][j]=(i==j);
    while(ci){
        if(ci&1) ans=mull(ans,num);
        num=mull(num,num);ci=ci>>1;
    }
    return ans;
}
int a[10];
int main()
{
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            ma.a[i][j]=((abs(i%3-j%3)+abs(i/3-j/3))==1);
    for(int i=0;i<9;i++)
        ma.a[i][i]=1;
    long long n;
    scanf("%lld",&n);
    ma=fast(n,ma);
    for(int i=0;i<9;i++)
        a[i]=i;
    long long ans=0;
    for(int i=0;i<362880;i++)
    {
        long long tmp=1;
        for(int j=0;j<9;j++)
        {
            tmp=tmp*ma.a[j][a[j]]%mod;
        }
        ans=(ans+tmp)%mod;
        next_permutation(a,a+9);
    }
    printf("%lld\n",ans);
    return 0;
}
