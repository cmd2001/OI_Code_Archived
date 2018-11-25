#include<cstdio>
#include<algorithm>
const int maxn=4e6+1e2,maxe=8e6+1e2;

int s[maxn],t[maxe],nxt[maxe];
int dfn[maxn],low[maxn],bel[maxn],stk[maxn],top,iid,dd;
bool vis[maxn],ins[maxn];
int n,m,k;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos) {
    low[pos] = dfn[pos] = ++dd , vis[pos] = ins[stk[++top]=pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( !vis[t[at]] ) dfs(t[at]) , low[pos] = std::min( low[pos] , low[t[at]] );
        else if( ins[t[at]] ) low[pos] = std::min( low[pos] , dfn[t[at]] );
    if( low[pos] == dfn[pos] ) {
        ++iid;
        do {
            const int x = stk[top--];
            ins[x] = 0 , bel[x] = iid;
        }while( ins[pos] );
    }
}
inline int cov(int x,int tpe) { // tpe = 1 means sel , 0 means not sel .
    return x * 2 - 1 + tpe;
}
inline bool judge() {
    for(int i=1;i<=n<<2;i++) if( !vis[i] ) dfs(i);
    for(int i=1;i<=n<<1;i++) if( bel[cov(i,0)] == bel[cov(i,1)] ) return 0;
    return 1;
}

int main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , addedge(cov(a,0),cov(b,1)) , addedge(cov(b,0),cov(a,1));
    for(int i=1;i<=n;i++) addedge(cov(i,1),cov(i+n,1)) , addedge(cov(i+n,0),cov(i,0));
    for(int i=1,siz,t,last;i<=k;i++) {
        scanf("%d",&siz) , last = 0;
        for(int j=1;j<=siz;j++) {
            scanf("%d",&t);
            if( last ) {
                addedge(cov(last,1),cov(t,0)) , addedge(cov(t,1),cov(last,0)) ,
                addedge(cov(last,1),cov(t+n,1)) , addedge(cov(t+n,0),cov(last,0));
            } last = t + n;
        }
    }
    puts(judge()?"TAK":"NIE");
    return 0;
}
