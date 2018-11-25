#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<tr1/unordered_set>
#define debug cout
typedef long long int lli;
typedef unsigned long long int ulli;
using namespace std;
using namespace tr1;
const int maxn=5e4+1e2,maxl=20;
const ulli base = 29;

char a[maxn],b[maxn];
int la,lb;
int rec[maxn];
lli ans;

struct ExtendedSuffixAutomatic {
    int ch[maxn<<2][26],len[maxn<<2],fa[maxn<<2],anc[maxn<<2][maxl];
    int siz[maxn<<2][2],deg[maxn<<2],root,cnt;
    inline int NewNode(int ll) {
        return len[++cnt] = ll , cnt;
    }
    ExtendedSuffixAutomatic() { root = NewNode(0); }
    inline void extend(int x,int p) {
        int np = NewNode(len[p]+1);
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
    }
    inline void Ex_extend(char* s,int li,int bel) {
        int cur = root;
        for(int i=1;i<=li;i++) {
            extend(s[i]-'A',cur) , cur = ch[cur][(int)s[i]-'A']; // a's A is different with b's A .
            ++siz[cur][bel];
            if( !bel ) rec[i] = cur;
        }
    }
    inline void topo() {
        for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
        queue<int> q;
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            if( pos == root ) break;
            anc[pos][0] = fa[pos];
            for(int i=0;i<2;i++) siz[fa[pos]][i] += siz[pos][i];
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
        for(int j=1;j<20;j++) for(int i=1;i<=cnt;i++) anc[i][j] = anc[anc[i][j-1]][j-1];
    }
    inline lli query(int pos,int lim) {
        for(int j=19;~j;j--) if( len[anc[pos][j]] >= lim ) pos = anc[pos][j];
        return (lli) siz[pos][0] * siz[pos][1];
    }
}esam;

struct Hash {
    ulli pows[maxn],h[maxn];
    inline void build(char* s,int li) {
        *pows = 1;
        for(int i=1;i<=li;i++) pows[i] = pows[i-1] * base , h[i] = h[i-1] * base + s[i] - 'A' + 1;
    }
    inline ulli query(int l,int r) {
        return h[r] - h[l-1] * pows[r-l+1];
    }
}hsh;

unordered_set<ulli> vis;

inline void calc(int al,int ar) {
    ulli h = hsh.query(al,ar);
    if( vis.find(h) != vis.end() ) return;
    vis.insert(h) , ans += esam.query(rec[ar],ar-al+1);
}

inline void manacher(char* s,int li) {
    static char in[maxn<<1];
    static int f[maxn<<1],app[maxn<<1],len,pos,mxr;
    #define getpos_l(i) (app[i]|app[i+1])
    #define getpos_r(i) (app[i]|app[i-1])
    *in = '$';
    for(int i=1;i<=li;i++) in[++len] = s[i] , app[len] = i , in[++len] = '#';
    for(int i=1;i<=len;i++) {
        if( i < mxr ) f[i] = min( f[pos*2-i] , mxr - i );
        else f[i] = 1;
        if( i & 1 ) calc(getpos_l(i-f[i]+1),getpos_r(i+f[i]-1));
        while( in[i-f[i]] == in[i+f[i]] ) {
            ++f[i];
            calc(getpos_l(i-f[i]+1),getpos_r(i+f[i]-1));
        }
        if( i + f[i] > mxr ) mxr = i + f[i] , pos = i;
    }
    #undef getpos_l
    #undef getpos_r
}

int main() {
    scanf("%s%s",a+1,b+1) , la = strlen(a+1) , lb = strlen(b+1);
    esam.Ex_extend(a,la,0) , esam.Ex_extend(b,lb,1) , esam.topo() , hsh.build(a,la);
    manacher(a,la) , printf("%lld\n",ans);
    return 0;
}
