#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;

lli f[20][2][171][171],pows[21];
bool vis[20][2][171][171];
int bits[21],top,mod;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const lli &y) {
    return x * y % mod;
}

// if not same length , we have to find first bit before using dfs .
inline lli dfs(int pos,bool fre,int su,int rem) { // su is sum we made and rem is remaining number we need to build .
    if( vis[pos][fre][su][rem] ) return f[pos][fre][su][rem];
    lli &ret = f[pos][fre][su][rem]; ret = 0 , vis[pos][fre][su][rem] = 1;
    if( !pos ) return ret = ( su == mod && !rem );
    if( fre ) for(int i=0;i<10;i++) ret += dfs(pos-1,1,su+i,sub(rem,mul(i,pows[pos])));
    else {
        for(int i=pos==top;i<bits[pos];i++) ret += dfs(pos-1,1,su+i,sub(rem,mul(i,pows[pos])));
        ret += dfs(pos-1,0,su+bits[pos],sub(rem,mul(bits[pos],pows[pos])));
    }
    return ret;
}
inline lli calc(lli x) {
    for(top=0;x;bits[++top]=x%10,x/=10) ;
    const int lim = min( 9*top , 9*18 );
    lli ret = 0;
    for(mod=1;mod<=lim;mod++) {
        memset(vis,0,sizeof(vis)) , ret += dfs(top,0,0,0);
        for(int len=1;len<top;len++) for(int fir=1;fir<10;fir++) ret += dfs(len-1,1,fir,sub(0,mul(fir,pows[len])));
    }
    return ret;
}

int main() {
    static lli l,r;
    scanf("%lld%lld",&l,&r);
    pows[1] = 1; for(int i=2;i<20;i++) pows[i] = pows[i-1] * 10;
    printf("%lld\n",calc(r)-calc(l-1));
    return 0; 
}
