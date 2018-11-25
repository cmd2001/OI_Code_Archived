#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],v[maxn<<1];
int siz[maxn],mxs[maxn],ban[maxn];
lli ans;

struct Array {
    int dat[maxn<<1];
    int& operator [] (const int &x) { return dat[x+maxn]; }
}hve;
struct DualArray {
    int dat[maxn<<1][2];
    int* operator [] (const int &x) { return dat[x+maxn]; }
}f,g;


inline void addedge(int from,int to,int val) {
    static int cnt;
    t[++cnt] = to , v[cnt] = val , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void getroot(int pos,int fa,const int &fs,int &rt) {
    siz[pos] = 1 , mxs[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) getroot(t[at],pos,fs,rt) , mxs[pos] = max( mxs[pos] , siz[t[at]] ) , siz[pos] += siz[t[at]];
    if( ( mxs[pos] = max( mxs[pos] , fs - siz[pos] ) ) <= mxs[rt] ) rt = pos;
}
inline int dfs(int pos,int fa,int val) {
    int ret = 0;
    ++g[val][(bool)hve[val]] , ++hve[val];
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) ret = max( ret , dfs(t[at],pos,val+v[at]) + 1 );
    --hve[val];
    return ret;
}
inline void solve(int pos,int fs) {
    if( fs == 1 ) return;
    int rt = 0 , mxd = 0 , dep = 0;
    *mxs = inf , getroot(pos,-1,fs,rt) , ban[rt] = 1;
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
        mxd = max( mxd , dep = ( dfs(t[at],rt,v[at]) + 1 ) ) , ans += (lli) f[0][0] * g[0][0] + g[0][1];
        for(int i=-dep;i<=dep;i++) ans += (lli) f[-i][0] * g[i][1] + (lli) f[-i][1] * g[i][0] + (lli) f[-i][1] * g[i][1];
        for(int i=-dep;i<=dep;i++) f[i][0] += g[i][0] , f[i][1] += g[i][1] , g[i][0] = g[i][1] = 0;
    }
    for(int i=-mxd;i<=mxd;i++) f[i][0] = f[i][1] = 0;
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b,v;i<n;i++) scanf("%d%d%d",&a,&b,&v) , v = v ? 1 : -1 , addedge(a,b,v) , addedge(b,a,v);
    solve(1,n) , printf("%lld\n",ans);
    return 0;
}
