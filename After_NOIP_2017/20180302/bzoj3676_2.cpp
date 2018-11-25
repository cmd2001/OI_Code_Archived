#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
using namespace std;
const int maxn=6e5+1e2;

char in[maxn>>1];
lli ans;

namespace SAM {
    int ch[maxn][26],fa[maxn],len[maxn],siz[maxn],deg[maxn],anc[maxn][21],root,last,cnt;
    int cov[maxn>>1];
    inline int NewNode(int ll) {
        len[++cnt] = ll;
        return cnt;
    }
    inline void extend(int x,int at) {
        int p = last;
        int np = NewNode(len[p]+1);
        siz[np] = 1 , cov[at] = np;
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q] ,
                fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void topo() {
        queue<int> q;
        for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            if( pos == root ) continue;
            siz[fa[pos]] += siz[pos];
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
    }
    inline void pre() {
        for(int i=1;i<=cnt;i++) *anc[i] = fa[i];
        for(int i=1;i<21;i++)
            for(int j=1;j<=cnt;j++)
                anc[j][i] = anc[anc[j][i-1]][i-1];
    }
    inline void query(int l,int r) { // returning appeared time of substring [l,r] .
        l += ( l & 1 ) , r -= ( r & 1 );
        if( l > r ) return;
        l >>= 1 , r >>= 1;
        const int t = r - l + 1;
        int p = cov[r];
        for(int i=20;~i;i--)
            if( len[anc[p][i]] >= t )
                p = anc[p][i];
        ans = max( ans , (lli) t * siz[p] );
    }
}

char str[maxn];
int pir[maxn],li,len,mx,pos;

inline void manacher() {
    str[++len] = '$';
    for(int i=1;i<=li;i++) {
        str[++len] = in[i];
        if( i != li ) str[++len] = '#';
    }
    for(int i=1;i<=len;i++) {
        if( i < mx ) pir[i] = min(mx-i,pir[pos*2-i]);
        else {
            pir[i] = 1;
            if( ! ( i & 1 ) ) SAM::query(i,i);
        }
        while( str[i+pir[i]] == str[i-pir[i]] ) {
            ++pir[i];
            SAM::query(i-pir[i]+1,i+pir[i]-1);
        }
        if( mx < i + pir[i] ) mx = i + pir[i] , pos = i;
    }
}

int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    SAM::last = SAM::root = SAM::NewNode(0);
    for(int i=1;i<=li;i++) SAM::extend(in[i]-'a',i);
    SAM::topo() , SAM::pre();
    manacher();
    printf("%lld\n",ans);
    return 0;
}