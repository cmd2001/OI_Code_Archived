#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=(1<<20)+7,maxt=50;
const int mod=998244353;
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

inline int sub(const int &a,const int &b) {
    const int ret = a - b;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &a,const int &b) {
    return (lli) a * b % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int sq(const int &x) {
    return mul(x,x);
}

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}

int vis[maxt][maxt];
int v[maxn],e[maxn],cnt;
int in[4],fs,n;

inline void dfs(int dep,int x,int y,int val,int ex) {
    if( dep > n ) {
        v[++cnt] = val , e[cnt] = ex;
        return;
    }
    ++vis[x][y];
    for(int i=0;i<4;i++) {
        const int tx = x + dx[i] , ty = y + dy[i];
        dfs(dep+1,tx,ty,val+!vis[tx][ty],mul(ex,in[i]));
    }
    --vis[x][y];
}

inline int calc() {
    int avr = 0 , su = 0 , ws = 0;
    for(int i=1;i<=cnt;i++) adde(avr,mul(v[i],e[i])) , adde(ws,e[i]);
    mule(avr,fastpow(ws,mod-2));
    for(int i=1;i<=cnt;i++) adde(su,mul(e[i],sq(sub(avr,v[i]))));
    return mul(su,fastpow(fs,n));
}

int main() {
    freopen("altair.in","r",stdin);
    freopen("altair.out","w",stdout);
    scanf("%d",&n);
    for(int i=0;i<4;i++) scanf("%d",in+i) , adde(fs,in[i]);
    dfs(1,n,n,1,1) , printf("%d\n",calc());
    fclose(stdout);
    return 0;
}
