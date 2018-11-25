#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const int int_inf=0x3f3f3f3f;
const lli inf = 0x3f3f3f3f3f3f3f3fll;

struct Matrix {
    lli dat[4][4];
    Matrix() { memset(dat,0x3f,sizeof(dat)); }
    lli* operator [] (const int &x) { return dat[x]; }
    const lli* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<4;i++) for(int j=0;j<4;j++) for(int k=0;k<4;k++) ret[i][j] = min( ret[i][j] , a[i][k] + b[k][j] );
        return ret;
    }
}trans;

struct SuffixAutomatic {
    int ch[maxn<<1][4],fa[maxn<<1],len[maxn<<1],f[maxn<<1][4],cnt,root,last;
    bool vis[maxn<<1];
    inline int NewNode(int ll) {
        return len[++cnt] = ll , cnt;
    }
    SuffixAutomatic() { last = root = NewNode(0); }
    inline void extend(int x) {
        int p = last , np = NewNode(len[p]+1);
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            const int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                const int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void dfs(int pos) {
        if( vis[pos] ) return;
        vis[pos] = 1 , memset(f[pos],0x3f,sizeof(f[pos]));
        for(int i=0;i<4;i++) {
            if( ch[pos][i] ) dfs(ch[pos][i]);
            else f[pos][i] = 1;
        }
        for(int i=0;i<4;i++) if( ch[pos][i] ) for(int j=0;j<4;j++) f[pos][j] = min( f[pos][j] , f[ch[pos][i]][j] + 1 ); // don't update it by NULL node .
    }
}sam;

lli n;

inline Matrix fastpow(Matrix base,lli tim) {
    Matrix ret = base; --tim;
    while( tim ) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
inline lli judge(lli t) {
    if( !t ) return 1; // or you may get wa if n == 0 .
    lli mi = inf;
    Matrix f = fastpow(trans,t);
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) mi = min( mi , f[i][j] );
    return mi;
}
inline lli bin() {
    lli ll = 0 , rr = inf , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) <= n ) ll = mid;
        else rr = mid;
    }
    if( judge(ll) < n ) ++ll;
    return ll;
}

int main() {
    static char s[maxn];
    static int li;
    scanf("%lld%s",&n,s+1) , li = strlen(s+1);
    for(int i=1;i<=li;i++) sam.extend(s[i]-'A');
    sam.dfs(sam.root);
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) trans[i][j] = sam.f[sam.ch[sam.root][i]][j];
    printf("%lld\n",bin());
    return 0;
}

