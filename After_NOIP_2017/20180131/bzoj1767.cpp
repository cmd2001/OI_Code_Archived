#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
lli d[maxn],f[maxn],v[maxn],w[maxn];
int mt[maxn],uni[maxn],stk[maxn],top;
vector<int> mv[maxn];
int ss = 0,cnt=0;
bool vis[maxn];

inline long double slope(int i,int j) { // assert i < j
    return ( (long double) f[j] - f[i] ) / ( (long double) d[j] - d[i] );
}
inline int bin(int v) { // returning the point.
    int ll = 1 , rr = top , mid;
    double sl,sr;
    if( top == 1 ) return 1;
    if( v < slope(stk[1],stk[2]) ) return 1;
    if( v > slope(stk[top-1],stk[top]) ) return top;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        sl = slope(stk[mid-1],stk[mid]) , sr = slope(stk[mid],stk[mid+1]);
        if( sl <= v && v <= sr ) return mid;
        if( sr > v ) rr = mid;
        else ll = mid;
    }
    mid = ( ll + rr ) >> 1;
    return mid;
}
inline int brute(int pos) {
    int ret = top;
    while( slope(stk[ret-1],stk[ret]) > slope(stk[ret],pos) ) --ret;
    return ret;
}
inline int bintop(int pos) {
    int ll = 1 , rr = top + 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( slope(stk[mid-1],pos) > slope(stk[mid-1],stk[mid]) ) ll = mid;
        else rr = mid;
    }
    /*debug<<"rr = "<<rr<<endl;
    debug<<"brute = "<<brute(pos)<<endl;*/
    return rr;
}
inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void pre(int pos,int fa) {
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa ) {
            d[t[at]] = d[pos] + l[at];
            pre(t[at],pos);
        }
}
inline void dfs(int pos,int fa) {
    vis[pos] = 1;
    if( pos != 1 ) {
        int fm = stk[bin(v[pos])];
        f[pos] = f[fm] + v[pos] * ( d[pos] - d[fm] ) + w[pos];
        mt[pos] = top , top = bintop(pos);
        uni[pos] = stk[top] , stk[top] = pos;
    }
    
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa )
            dfs(t[at],pos);
    
    if( pos != 1 ) {
        stk[top] = uni[pos] , top = mt[pos];
    }
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b,l;i<n;i++) {
        scanf("%d%d%d",&a,&b,&l);
        addedge(a,b,l) , addedge(b,a,l);
    }
    for(int i=2;i<=n;i++)
        scanf("%lld%lld",w+i,v+i);
    
    pre(1,-1);
    stk[top=1] = 1;
    dfs(1,-1);
    for(int i=2;i<=n;i++)
        printf("%lld%c",f[i],i!=n?' ':'\n');
    
    return 0;
}
