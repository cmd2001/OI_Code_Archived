#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=3e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
int in[maxn],mxtar[maxn],misel[maxn];
int lim,sum,n,m;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dfs(int pos,int fa) {
    mxtar[pos] = -inf , misel[pos] = inf;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa ) {
            dfs(t[at],pos);
            mxtar[pos] = max( mxtar[pos] , mxtar[t[at]] + 1 ) ,
            misel[pos] = min( misel[pos] , misel[t[at]] + 1 );
        }
    if( in[pos] ) mxtar[pos] = max( mxtar[pos] , 0 );
    if( mxtar[pos] + misel[pos] <= lim ) mxtar[pos] = -inf;
    else if( mxtar[pos] == lim ) mxtar[pos] = -inf , misel[pos] = 0 , ++sum;
}

inline bool judge(int x) {
    lim = x , sum = 0;
    dfs(1,-1) , sum += ( mxtar[1] >= 0 );
    return sum <= m;
}
inline int bin() {
    int ll = -1 , rr = n + 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(mid) ) rr = mid;
        else ll = mid;
    }
    return rr;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b) ,
        addedge(a,b) , addedge(b,a);
    }
    printf("%d\n",bin());
    return 0;
}