#include<cstdio>
#include<algorithm>
#include<vector>
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int in[maxn],lim[maxn],f[maxn],uni[maxn];

inline bool cmp(const int &x,const int &y) {
    return f[x] > f[y];
}
inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    uni[pos] = 1 , f[pos] = in[pos];
    std::vector<int> sons;
    int zro = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa ) {
        dfs(t[at],pos);
        if( f[t[at]] > 0 ) sons.push_back(t[at]);
        else if( !f[t[at]] ) ++zro;
    }
    int sel = std::min( lim[pos] - 1 , (signed) sons.size() );
    if( sons.size() ) {
        std::sort(sons.begin(),sons.end(),cmp);
        for(int i=0;i<sel;i++) f[pos] += f[sons[i]] , uni[pos] &= uni[sons[i]];
        if( sel != (signed) sons.size() && f[sons[sel-1]] == f[sons[sel]] ) uni[pos] = 0;
    }
    if( sel != lim[pos] - 1 && zro ) uni[pos] = 0;
}

int main() {
    static int n;
    scanf("%d",&n) , lim[1] = inf;
    for(int i=2;i<=n;i++) scanf("%d",in+i);
    for(int i=2;i<=n;i++) scanf("%d",lim+i);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , addedge(a,b) , addedge(b,a);
    dfs(1,-1);
    if( f[1] >= 0 ) {
        printf("%d\n",f[1]);
        puts(uni[1]?"solution is unique":"solution is not unique");
    } else puts("0\nsolution is unique");
    return 0;
}
