#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=3e3+1e2;

struct SuffixAutomatic {
    int ch[maxn<<1][2],fa[maxn<<1],len[maxn<<1],siz[maxn<<1],deg[maxn<<1],cnt,root,last;
    inline int newNode(int l) {
        return len[++cnt] = l , cnt;
    }
    SuffixAutomatic() { last = root = newNode(0); }
    inline void extend(int x) {
        int p = last , np = newNode(len[p]+1); siz[np] = 1;
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = newNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void topo() {
        for(int i=1;i<=cnt;i++) if(fa[i]) ++deg[fa[i]];
        queue<int> q;
        for(int i=1;i<=cnt;i++) if( !deg[i] ) q.push(i);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            siz[fa[pos]] += siz[pos];
            if( !--deg[fa[pos]] ) q.push(fa[pos]);
        }
    }
    inline void dfs(int pos) {
        if( len[pos] && siz[pos] > 1 ) printf("%d\n",siz[pos]);
        for(int i=0;i<2;i++) if( ch[pos][i] ) dfs(ch[pos][i]);
    }
}sam;

char in[maxn];
int li;

int main() {
    scanf("%d%s",&li,in+1);
    for(int i=1;i<=li;i++) sam.extend(in[i]-'0');
    sam.topo() , sam.dfs(sam.root);
    return 0;
}
