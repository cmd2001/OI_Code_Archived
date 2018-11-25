#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;
const int maxn=1e3+1e2,maxe=1e4+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;
const double eps=1e-5,mul=0.9999,lambda=0.1,ini=1e8;

int n,m;

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline bool merge(int x,int y) {
        x = findfa(x) , y = findfa(y);
        return x == y ? 0 : fa[x] = y;
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

struct Edge {
    int u,v,val,col,id;
}es[maxe];

int cur[maxe],now[maxe],ans[maxe];
lli calc_cur,calc_now,calc_ans;
double temp;

inline lli calc() {
    set<int> cs; lli su = 0; ufs.init();
    for(int t=1;t<=m;t++) {
        const int i = cur[t];
        if( ufs.merge(es[i].u,es[i].v) ) su += es[i].val , cs.insert(es[i].col);
    }
    return su * cs.size();
}
inline void printans() {
    ufs.init();
    for(int t=1;t<=m;t++) {
        const int i = ans[t];
        if( ufs.merge(es[i].u,es[i].v) ) printf("%d\n",es[i].id);
    }
}
inline void solve() {
    memcpy(cur+1,now+1,sizeof(int)*m) , random_shuffle(cur+1,cur+1+m) , calc_cur = calc();
    if( calc_cur < calc_ans ) memcpy(ans+1,cur+1,sizeof(int)*m) , calc_ans = calc_cur;
    if( calc_cur < calc_now || ( temp > lambda && (double) rand() / ( rand() + 1 ) > temp ) ) memcpy(now+1,cur+1,sizeof(int)*m) , calc_now = calc_cur;
}
inline void random_seq() {
    int l = rand() % m + 1 , r = rand() % m + 1;
    if( l > r ) swap(l,r);
    random_shuffle(cur+l,cur+r+1);
}
inline void solve2() {
    memcpy(cur+1,now+1,sizeof(int)*m) , random_seq() , calc_cur = calc();
    if( calc_cur < calc_ans ) memcpy(ans+1,cur+1,sizeof(int)*m) , calc_ans = calc_cur;
    if( calc_cur < calc_now || ( temp > lambda && (double) rand() / ( rand() + 1 ) > temp ) ) memcpy(now+1,cur+1,sizeof(int)*m) , calc_now = calc_cur;

}
inline void getans() {
    calc_now = calc_ans = inf;
    for(int i=1;i<=m;i++) now[i] = i;
    for(temp=ini;temp>eps;temp*=mul) solve();
    for(int i=1;i<=m;i++) now[i] = i;
    calc_now = inf;
    for(temp=ini;temp>eps;temp*=mul) solve2();
}


inline void init() { // it can work 
    static const char seed[] = "KurenaiKisaragi";
    uint su = 0 , li = strlen(seed);
    for(uint i=0;i<li;i++) su += seed[i];
    srand(su);
}

int main() {
    scanf("%d%d",&n,&m) , init();
    for(int i=1;i<=m;i++) scanf("%d%d%d%d",&es[i].u,&es[i].v,&es[i].val,&es[i].col) , es[i].id = i;
    getans() , printans();
    return 0;
}

