#include<cstdio>
#include<cstring>
#include<queue>
typedef long long int lli;
const int maxn=2e5+1e2;


char in[maxn>>1];
int li;
lli ans;

inline int gid(char c) {
    switch(c) {
        case 'A' : return 0;
        case 'T' : return 1;
        case 'C' : return 2;
        case 'G' : return 3;
    }
    return -1;
}

struct SuffixAutomatic {
    int ch[maxn][4],fa[maxn],len[maxn],rit[maxn],deg[maxn],root,last,cnt;
    SuffixAutomatic() { root = last = cnt = 1; }
    inline int NewNode(int ll) {
        return len[++cnt] = ll , cnt;
    }
    inline void extend(int x) {
        int p = last , np = NewNode(len[p]+1); rit[np] = 1;
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q] , fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void topo() {
        for(int i=1;i<=cnt;i++) if( fa[i] ) ++deg[fa[i]];
        std::queue<int> q;
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while(q.size()) {
            const int pos = q.front(); q.pop();
            if( pos == root ) break;
            rit[fa[pos]] += rit[pos];
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
    }
    inline void dfs(int pos,int fixed,int curlen) {
        if( curlen > li ) return void(ans+=rit[pos]);
        for(int i=0;i<4;i++) if( ch[pos][i] ) {
            if( gid(in[curlen]) == i ) dfs(ch[pos][i],fixed,curlen+1);
            else if( fixed < 3 ) dfs(ch[pos][i],fixed+1,curlen+1);
        }
    }
    inline void reset() {
        memset(ch,0,sizeof(ch)) , memset(rit,0,sizeof(rit)) , memset(fa,0,sizeof(fa));
        root = last = cnt = 1;
    }
}sam;


int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%s",in+1) , li = strlen(in+1) , sam.reset() , ans = 0;
        for(int i=1;i<=li;i++) sam.extend(gid(in[i]));
        scanf("%s",in+1) , li = strlen(in+1) , sam.topo();
        sam.dfs(1,0,1) , printf("%lld\n",ans);
    }
    return 0;
}
