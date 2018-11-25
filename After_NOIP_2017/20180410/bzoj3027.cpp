#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long int lli;
const int maxn=20,mod=2004;

lli mul,cmod;
int in[maxn],n,a,b,ans;

inline int c(int n,int m) {
    if( n < m ) return 0;
    lli ret = 1;
    for(int i=n-m+1;i<=n;i++) ret = ret * ( i % cmod ) % cmod;
    return ( ret / mul ) % mod;
}
inline int dfs(int pos,int tim,int val,const int &lim) {
    if( pos > n ) return val * c(n+lim-tim,n) % mod;
    int ret = 0;
    ret += dfs(pos+1,tim,val,lim) ;
    ret += dfs(pos+1,tim+in[pos]+1,-val,lim) ;
    return ( ret % mod + mod ) % mod;
}

int main() {
    scanf("%d%d%d",&n,&a,&b) , mul = 1;
    for(int i=1;i<=n;i++) scanf("%d",in+i) , mul *= i;
    cmod = mod * mul , ans = ( dfs(1,0,1,b) - dfs(1,0,1,a-1) + mod ) % mod;
    printf("%d\n",ans);
    return 0;
}
