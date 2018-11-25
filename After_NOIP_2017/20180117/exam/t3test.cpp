#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<map>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=3e2+1e1,maxm=2e3+1e2,lim=2e3;
const int mod = 1e9+7;

struct Pool {
    unsigned long long dat[5];
    const unsigned long long full = 0xffffffffffffffffull;
    
    inline int getbit(int pos) {
        int x = pos / 64 , y = pos % 64;
        return ( dat[x] >> y ) & 1;
    }
    inline void revbit(int pos) {
        int x = pos / 64 , y = pos % 64;
        dat[x] ^= ( 1ull << y );
    }
    friend Pool operator ^ (const Pool &a,const Pool &b) {
        Pool ret;
        for(int i=0;i<5;i++)
            ret.dat[i] = a.dat[i] ^ b.dat[i];
        return ret;
    }
    friend bool operator < (const Pool &a,const Pool &b) {
        for(int i=0;i<5;i++)
            if( a.dat[i] != b.dat[i] ) return a.dat[i] < b.dat[i];
        return 0;
    }
    inline void clear() {
        memset(dat,0,sizeof(dat));
    }
}dv[maxn];

map<Pool,int> mp[2];
lli in[maxn],cpm[maxn];
int prime[maxm],cnt;
unsigned char vis[maxm];
int n,cur;

inline void sieve() {
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( !( i % prime[j] ) ) break;
        }
    }
}

inline void cut(int p,lli x) {
    for(int i=1;i<=cnt;i++)
        while( ! ( x % prime[i] ) ) {
            dv[p].revbit(i) , x /= prime[i];
        }
}

inline void getans() {
    cur = 0;
    mp[cur][dv[0]] = 0;
    for(int i=1;i<=n;i++) {
        mp[cur^1] = mp[cur];
        for(map<Pool,int>::iterator it=mp[cur].begin();it!=mp[cur].end();++it) {
            Pool tar = it->first ^ dv[i];
            mp[cur^1][tar] += it->second , mp[cur^1][tar] %= mod;
        }
        mp[cur^1][dv[i]]++ , mp[cur^1][dv[i]] %= mod;
        cur ^= 1;
    }
}

inline void clear() {
    mp[0].clear() , mp[1].clear();
    for(int i=0;i<maxn;i++) dv[i].clear();
    memset(cpm,0,sizeof(cpm));
}


int main() {
    sieve();
    static int T;
    //freopen("dat.txt","r",stdin);
    scanf("%d",&T);
    for(int t=1;t<=T;t++) {
        clear();
        scanf("%d",&n);
        if( n <= 20 ) {
            for(int i=1;i<=n;i++) {
                lli x;
                scanf("%lld",&x);
                cut(i,x);
            }
            getans();
            printf("Case #%d:\n",t);
            printf("%d\n",mp[cur][dv[0]]);
        }
        
    }
    return 0;
}