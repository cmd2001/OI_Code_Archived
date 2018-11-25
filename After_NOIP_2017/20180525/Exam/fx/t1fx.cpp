#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
const int maxn=5e3+1e2,maxe=2e4+1e2;
const int inf=0x3f3f3f3f;

struct Query{ int siz,id; };
int s[maxn],t[maxn<<1],nxt[maxn<<1],fa[maxn];
int cst[maxn],val[maxn],f[17][maxe];
int siz[maxn],mxs[maxn],ban[maxn];
int ans[maxn];
std::vector<Query> qs[maxn];

inline void addedge(int from,int to) {
    static int cnt;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void trans(int* dst,const int &cst,const int &val) {
    for(int i=cst;i<maxe;i++) dst[i] = std::max( dst[i] , dst[i-cst] + val );
}

inline void getrt(int pos,int fa,const int &fs,int &rt) {
    siz[pos] = 1 , mxs[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) getrt(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = std::max( mxs[pos] , siz[t[at]] );
    if( ( mxs[pos] = std::max( mxs[pos] , fs - siz[pos]) ) < mxs[rt] ) rt = pos;
}
inline void solve(int pos,int fs,int dep) { // pos is the highest point in this block , assert we know dp[pos] in f[dep].
    if( fs == 1 ) {
        for(unsigned i=0;i<qs[pos].size();i++) ans[qs[pos][i].id] = f[dep][qs[pos][i].siz];
        return void(ban[pos]=1);
    }
    int rt = 0;
    *mxs = inf , getrt(pos,-1,fs,rt) , ban[rt] = 1;
    if( rt != pos ) memcpy(f[dep+1],f[dep],sizeof(f[0])) , solve(pos,fs-siz[rt],dep+1);
    for(int i=rt;i!=pos;i=fa[i]) trans(f[dep],cst[i],val[i]);
    for(unsigned i=0;i<qs[rt].size();i++) ans[qs[rt][i].id] = f[dep][qs[rt][i].siz];
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) memcpy(f[dep+1],f[dep],sizeof(f[0])) , trans(f[dep+1],cst[t[at]],val[t[at]]) , solve(t[at],siz[t[at]],dep+1);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d%d",cst+i,val+i);
    for(int i=2;i<=n;i++) scanf("%d",fa+i) , addedge(fa[i],i) , addedge(i,fa[i]);
    for(int i=1;i<=m;i++) scanf("%d",ans+i);
    for(int i=1,pos;i<=m;i++) scanf("%d",&pos) , qs[pos].push_back((Query){ans[i],i}) , ans[i] = 0;
    trans(f[1],cst[1],val[1]) , solve(1,n,1);
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
