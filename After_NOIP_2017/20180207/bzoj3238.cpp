#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lli long long int
using namespace std;
const int maxn=1e6+1e2;

char in[maxn];
int ch[maxn][26],len[maxn],fa[maxn],root,last,cnt;
lli siz[maxn],ans;
vector<int> son[maxn];

inline int NewNode(int ll) {
    len[++cnt] = ll;
    return cnt;
}
inline void extend(int x) {
    int p = last;
    int np = NewNode(len[p]+1);
    siz[np] = 1;
    while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
    if( !p ) fa[np] = root;
    else {
        int q = ch[p][x];
        if( len[q] == len[p] + 1 ) fa[np] = q;
        else {
            int nq = NewNode(len[p]+1);
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
        }
    }
    last = np;
}
inline void dfs(int pos) {
    for(unsigned i=0;i<son[pos].size();i++) {
        dfs(son[pos][i]);
        ans -= 2 * siz[pos] * siz[son[pos][i]] * len[pos];
        siz[pos] += siz[son[pos][i]];
    }
}

int main() {
    static int li;
    scanf("%s",in+1) , li = strlen(in+1);
    reverse(in+1,in+1+li);
    ans = (lli) li * (li+1) * (li-1) >> 1;
    last = root = NewNode(0);
    for(int i=1;i<=li;i++) extend(in[i]-'a');
    for(int i=2;i<=cnt;i++) son[fa[i]].push_back(i);
    dfs(root);
    printf("%lld\n",ans);
    return 0;
}
