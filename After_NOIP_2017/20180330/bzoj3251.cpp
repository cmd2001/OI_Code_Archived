#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],in[maxn],fa[maxn],dep[maxn];
int seq[maxn],len;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            dep[t[at]] = dep[pos] + 1 , fa[t[at]] = pos;
            dfs(t[at]);
        }
}
inline bool query(int x,int y) {
    len = 0;
    while( len <= 50 && x != y ) {
        if( dep[x] < dep[y] ) swap(x,y);
        seq[++len] = in[x] , x = fa[x];
    }
    seq[++len] = in[x];
    if( len > 50 ) return 1;
    sort(seq+1,seq+1+len);
    for(int i=2;i<len;i++)
        if( (long long) seq[i-1] + seq[i] > seq[i+1] ) return 1;
    return 0;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b) ,
        addedge(a,b) , addedge(b,a);
    }
    dfs(1);
    for(int i=1,o,x,y;i<=m;i++) {
        scanf("%d%d%d",&o,&x,&y);
        if( !o ) puts( query(x,y) ? "Y" : "N" );
        else in[x] = y;
    }
    return 0;
}
