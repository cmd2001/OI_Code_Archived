#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e4+1e2,maxe=1e5+1e2;
const int mod=1e9+7;

struct Edge { int to,col,val; };
int u[maxe],v[maxe],c[maxe],in[maxe],deg[maxn],mem[maxn][3];
vector<Edge> es[maxn];
int n,m,ans;

inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int& dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

inline void solve() { // there is no range-based for loop in c++98 .
    for(int i=1;i<=n;i++) {
        for(unsigned J=0;J<es[i].size();J++) adde(mem[es[i][J].to][es[i][J].col],es[i][J].val);
        for(unsigned J=0;J<es[i].size();J++) {
            const int j = es[i][J].to , c = es[i][J].col , v = es[i][J].val;
            for(unsigned K=0;K<es[j].size();K++) if( es[j][K].col != c ) {
                const int ned = 3 - c - es[j][K].col , vv = es[j][K].val;
                adde(ans,mul(mul(v,vv),mem[es[j][K].to][ned]));
            }
        }
        for(unsigned J=0;J<es[i].size();J++) mem[es[i][J].to][es[i][J].col] = 0;
    }
}
inline void build() {
    for(int i=1;i<=m;i++) {
        if( deg[u[i]] < deg[v[i]] || ( deg[u[i]] == deg[v[i]] && u[i] > v[i] ) ) swap(u[i],v[i]);
        es[u[i]].push_back((Edge){v[i],c[i],in[i]});
    }
}

inline int explain(const char c) {
    switch(c) {
        case 'R': return 0;
        case 'G': return 1;
        case 'B': return 2;
        default: return -1;
    }
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch , fix = 1;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}
inline char realchar() {
    char ch;
    while( !isalpha(ch=nextchar()) );
    return ch;
}


int main() {
    n = getint() , m = getint();
    for(int i=1;i<=m;i++) ++deg[u[i]=getint()] , ++deg[v[i]=getint()] , in[i] = getint() , c[i] = explain(realchar());
    build() , solve() , printf("%d\n",ans);
    return 0;
}
