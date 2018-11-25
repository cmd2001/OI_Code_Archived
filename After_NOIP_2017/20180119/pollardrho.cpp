#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<cstdlib>
#define lli long long int
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=5e6+1e2;

int in[maxn],dis[maxn],mxd,root;
int s[maxn],t[maxn<<1],nxt[maxn<<1];
bool can[maxn],vis[maxn];
vector<int> pts[maxn];
map<int,int> mp;
int n,m,cnt,ans;

namespace PollardRho {
    const int lst[15]={0,2,3,5,7,11,13,17,19,23,29,31,61,24251},lstlen=13;
    inline int fastpow(int base,int tme,int mod) {
        int ret = 1 , now = base;
        while( tme ) {
            if( tme & 1 ) ret = (lli) ret * now % mod;
            now = (lli) now * now % mod;
            tme >>= 1;
        }
        return ret % mod;
    }
    inline bool test(int x,int a) {
        int p = x - 1 , t = 0;
        while( ! ( p & 1 ) )
            p >>= 1 , ++t;
        p = fastpow(a,p,x);
        if( p == 1 || p == x - 1 ) return 1;
        while( t-- ) {
            p = (lli) p * p % x;
            if( p == x - 1 ) return 1;
        }
        return 0;
    }
    inline bool miller(int x) {
        for(int i=1;i<=lstlen;i++)
            if( x == lst[i] )return 1;
        for(int i=1;i<=lstlen;i++)
            if( ! ( x % lst[i]) ) return 0;
        for(int i=1;i<=lstlen;i++)
            if( !test(x,lst[i]) ) return 0;
        return 1;
    }
    inline int rnd(int x,int mod) {
        return ( (lli) x * x + 1 ) % mod;
    }
    inline int gcd(int a,int b) {
        if( ! ( a && b ) ) return a | b;
        register int t;
        while( t = a % b )
            a = b , b = t;
        return b;
    }
    inline void pollard(int x,int p) {
        //debug<<"x = "<<x<<"p = "<<p<<endl;
        if( miller(x) ) {
            if( !mp.count(x) ) mp[x] = ++cnt;
            pts[mp[x]].push_back(p);
            return;
        }
        int g , seed = rand() , t1 = rnd(seed,x) , t2 = rnd(t1,x);
        while( 1 ) {
            g = gcd( abs(t1-t2) , x );
            //debug<<"g = "<<g<<endl;
            //debug<<"abs = "<<abs(t1-t2)<<endl;
            //debug<<"t1 = "<<t1<<"t2 = "<<t2<<endl;
            if( g != 1 && g != x ) break;
            t1 = rnd(t1,x) , t2 = rnd(t2,x) , t2 = rnd(t2,x);
            if( t1 == t2 ) {
                //debug<<"re randed"<<endl;
                t1 = rand() % x + 1 , t2 = rand() % x + 1;
            }
        }
        //debug<<"g = "<<g<<endl;
        pollard(g,p);
        pollard(x/g,p);
    }
}
using PollardRho::pollard;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    vis[pos] = 1;
    if( dis[pos] > dis[mxd] ) mxd = pos;
    for(int at=s[pos];at;at=nxt[at])
        if( can[t[at]] && t[at] != fa ) {
            dis[t[at]] = dis[pos] + 1;
            dfs(t[at],pos);
        }
}
inline void solve(const vector<int> &vec) {
    for(unsigned i=0;i<vec.size();i++)
        can[vec[i]] = 1;
    for(unsigned i=0;i<vec.size();i++) {
        if( vis[vec[i]] ) continue;
        dis[vec[i]] = 1 , mxd = 0;
        dfs(vec[i],-1);
        dis[mxd] = 1;
        dfs(mxd,-1);
        ans = max( ans , dis[mxd] );
    }
    for(unsigned i=0;i<vec.size();i++)
        dis[vec[i]] = vis[vec[i]] = can[vec[i]] = 0;
}

int main() {
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b) , addedge(b,a);
    }
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x);
        pollard(x,i);
    }
    
    for(int i=1;i<=cnt;i++)
        solve(pts[i]);
    
    printf("%d\n",ans);
    
    return 0;
}
