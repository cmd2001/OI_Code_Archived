#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<iostream>
#define debug cerr
using namespace std;
typedef unsigned long long int ulli;
using std::max;using std::reverse;
const int maxn=1e6+1e2;
const ulli base = 31;
const int inf=0x3f3f3f3f;

char in[maxn],tar[maxn]; // input string and target string .
ulli pows[maxn],hpr[maxn],hsu[maxn]; // hash prefix and hash suffix .
int s[maxn],t[maxn<<1],nxt[maxn<<1],ban[maxn],cnt;
int dep[maxn],siz[maxn],mxs[maxn],prf[maxn],suf[maxn],sprf[maxn],ssuf[maxn]; // mxs[0] = inf  , paired prf[length] .
int n,m;
ulli ans;

bool vis[maxn];

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] ,s[from] = cnt;
}
inline void findroot(int pos,const int &fa,const int &fs,int &rt) {
    siz[pos] = 1 , mxs[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) {
        findroot(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = max( mxs[pos] , siz[t[at]] );
    }
    if( ( mxs[pos] = max( mxs[pos] , fs - siz[pos] ) ) <= mxs[rt] ) rt = pos;
}
inline void dfs(int pos,int fa,int dep,int &mxd,const char &mid,ulli h) {
    mxd = max( mxd , dep ) , h += in[pos] * pows[dep-1]; // add in[pos] to first char .
    if( h == hpr[dep] ) {
        ++prf[dep%m];
        if( mid == tar[dep%m+1] ) ans += ssuf[m-dep%m-1];
    }
    if( h == hsu[dep] ) {
        ++suf[dep%m];
        if( mid == tar[m-dep%m] ) ans += sprf[m-dep%m-1];
    }
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) dfs(t[at],pos,dep+1,mxd,mid,h);
}
inline void solve(int pos,int fs) {
    if( fs < m ) return;
    int rt = 0 , full = 0;
    *mxs = inf , findroot(pos,-1,fs,rt) , ban[rt] = 1;
    if( in[rt] == tar[1] ) ++sprf[0];
    if( in[rt] == tar[m] ) ++ssuf[0];
    for(int at=s[rt],mxd;at;at=nxt[at]) if( !ban[t[at]] ) {
        mxd = 0 , dfs(t[at],rt,1,mxd,in[rt],0) , full = max( full , mxd );
        for(int i=0;i<=mxd;i++) sprf[i] += prf[i] , ssuf[i] += suf[i] , prf[i] = suf[i] = 0;
    }
    for(int i=0;i<=full;i++) sprf[i] = ssuf[i] = 0;
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline void getstr(char* s) {
    char ch;
    while( !isalpha(ch=nextchar()) );
    do *s++ = ch; while( isalpha(ch=nextchar()) );
}
inline void gethsh(ulli* dst) {
    for(int i=m+1;i<=n;i++) tar[i] = tar[i-m];
    for(int i=1;i<=n;i++) dst[i] = dst[i-1] * base + tar[i];
}
inline void fix(char* s,int len) {
    for(int i=1;i<=len;i++) s[i] -= 'A' - 1;
}
inline void solve_case() {
    n = getint() , m = getint() , getstr(in+1) , fix(in,n) , memset(s,0,sizeof(s)) , memset(ban,0,sizeof(ban)) , cnt = ans = 0 , *pows = 1;
    for(int i=1;i<=n;i++) pows[i] = pows[i-1] * base;
    for(int i=1,a,b;i<n;i++) a = getint() , b = getint() , addedge(a,b) , addedge(b,a);
    getstr(tar+1) , fix(tar,m) , gethsh(hpr) , reverse(tar+1,tar+1+m) , gethsh(hsu) , reverse(tar+1,tar+1+m);
    solve(1,n) , printf("%llu\n",ans);
}

int main() {
    static int T;
    T = getint();
    while(T--) solve_case();
    return 0;
}

