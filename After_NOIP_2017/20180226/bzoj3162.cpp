#include<cstdio>
#include<algorithm>
#define lli long long int
#define ulli unsigned long long int
const int maxn=5e5+1e2;
const int mod=1e9+7,base=233;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
ulli hsh[maxn];
lli f[maxn][2],ans;
int siz[maxn],mx[maxn],root[2],stk[maxn],top,n;

inline lli fastpow(lli base,int tim,int mod) {
    lli ret = 1 , now = base % mod;
    while( tim ) {
        if( tim & 1 ) ret = ret * now % mod;
        if( tim >>= 1 ) now = now * now % mod;
    }
    return ret % mod;
}
inline lli C(int n,int m) {
    m = std::min( m , n - m );
    lli ret = 1 , inv = 1;
    for(lli i=n;i>n-m;i--) ret = ret * i % mod;
    for(lli i=1;i<=m;i++) inv = inv * i % mod;
    return ret * fastpow(inv,mod-2,mod) % mod;
}
inline lli calc(int n,int m) {
    return C(n+m-1,m);
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void findrt(int pos,int fa) {
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa ) {
            findrt(t[at],pos) , siz[pos] += siz[t[at]] ,
            mx[pos] = std::max( mx[pos] , siz[t[at]] );
        }
    mx[pos] = std::max( mx[pos] , n - siz[pos] );
    if( !root[0] ) root[0] = pos;
    else if( mx[pos] < mx[root[0]] ) root[0] = pos , root[1] = 0;
    else if( mx[pos] == mx[root[0]] ) root[1] = pos;
}
inline bool cmp(int x,int y) {
    return hsh[x] > hsh[y];
}
inline ulli calchsh() {
    ulli ret = 17;
    std::sort(stk+1,stk+1+top,cmp);
    for(int i=1;i<=top;i++) ret = ret * base + 17 * hsh[stk[i]] ;
    return ret;
}
inline void dfs(int pos,int fa) {
    f[pos][0] = f[pos][1] = 1;
    for(int at=s[pos];at;at=nxt[at]) {
        if( ( pos == root[0] && t[at] == root[1] ) || ( pos == root[1] && t[at] == root[0] ) ) continue;
        if( t[at] != fa ) dfs(t[at],pos);
    }
    top = 0;
    for(int at=s[pos];at;at=nxt[at]) {
        if( ( pos == root[0] && t[at] == root[1] ) || ( pos == root[1] && t[at] == root[0] ) ) continue;
        if( t[at] != fa ) stk[++top] = t[at];
    }
    hsh[pos] = calchsh();
    for(int i=1,j;i<=top;i=j+1) {
        for(j=i;j<top&&hsh[stk[i]]==hsh[stk[j+1]];j++) ;
        f[pos][0] = f[pos][0] * calc(f[stk[i]][0]+f[stk[i]][1],j-i+1) % mod ,
        f[pos][1] = f[pos][1] * calc(f[stk[i]][0],j-i+1) % mod;
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b) , addedge(b,a);
    }
    findrt(1,-1);
    if( !root[1] ) {
        dfs(root[0],-1);
        ans = ( f[root[0]][0] + f[root[0]][1] ) % mod;
    } else {
        ++n , addedge(n,root[0]) , addedge(n,root[1]);
        dfs(n,-1);
        if( hsh[root[0]] == hsh[root[1]] ) ans = ( f[root[0]][0] * f[root[1]][1] % mod + calc(f[root[0]][0],2) ) % mod;
        else {
            for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                    if( ! ( i & j ) ) ans = ( ans + f[root[0]][i] * f[root[1]][j] % mod ) % mod;
        }
    }
    printf("%lld\n",ans%mod);
    return 0;
}

