#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int val[maxn],dis[maxn];
int ans;

inline int gcd(int a,int b) {
    if( ! ( a && b ) ) return a | b;
    register int t;
    while( t = a % b )
        a = b , b = t;
    return b;
}

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    ans = max( ans , dis[pos] );
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa ) {
            int g = gcd(val[pos],in[t[at]]);
            if( g != 1 ) {
                dis[t[at]] = dis[pos] + 1 , val[t[at]] = g;
                dfs(t[at],pos);
            }
        }
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        addedge(a,b) , addedge(b,a);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1;i<=n;i++) {
        val[i] = in[i] , dis[i] = 1;
        dfs(i,-1);
    }
    
    printf("%d\n",ans);
    
    return 0;
}