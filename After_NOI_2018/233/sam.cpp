#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
using namespace std;
const int maxn = 2e6 + 1e2;

int ch[maxn][26],len[maxn],fa[maxn],siz[maxn],deg[maxn],root,last,cnt;
lli ans;

inline int newNode(int ll) {
    return len[++cnt] = ll, cnt;
}
inline void extend(int x) {
    int p = last, np = newNode(len[p]+1);
    siz[np] = 1;
    while(p && !ch[p][x]) ch[p][x] = np, p = fa[p];
    if(!p) fa[np] = root;
    else {
        int q = ch[p][x];
        if(len[q] == len[p] + 1) fa[np] = q;
        else {
            int nq = newNode(len[p]+1);
            memcpy(ch[nq],ch[q],sizeof(ch[q])), fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while(p && ch[p][x] == q) ch[p][x] = nq, p = fa[p];
        }
    }
    last = np;
}
inline void topo() {
    for(int i=1;i<=cnt;i++) if(fa[i]) ++deg[fa[i]];
    queue<int> q;
    for(int i=1;i<=cnt;i++) if(!deg[i]) q.push(i);
    while(q.size()) {
        const int pos = q.front(); q.pop();
        if(pos == root) break;
        if(siz[pos] != 1) ans = max(ans,(lli)siz[pos]*len[pos]);
        siz[fa[pos]] += siz[pos];
        if(!--deg[fa[pos]]) q.push(fa[pos]);
    }
}

int main() {
    static char in[maxn];
    static int n;
    scanf("%s",in+1), n = strlen(in+1);
    last = root = newNode(0);
    for(int i=1;i<=n;i++) extend(in[i]-'a');
    topo(), printf("%lld\n",ans);
    return 0;
}

