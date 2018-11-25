#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

int in[maxn],sum[maxn];
int Log[maxn],st[maxn][20]; // st saves pos of minunum sum .
int n,k,L,R,l;
lli ans;

inline void gen() {
    for(int i=1;i<=n;i++)
        sum[i] = sum[i-1] + in[i];
    for(int i=2;i<=n;i++)
        Log[i] = Log[i>>1] + 1;
    l = Log[n];
    for(int i=0;i<=n;i++)
        st[i][0] = i;
    for(int j=1;j<=l;j++) {
        const int d = 1 << ( j - 1 );
        for(int i=0;i<=n;i++)
            if( i + ( 1 << j ) - 1 <= n )
                st[i][j] = sum[st[i][j-1]] < sum[st[i+d][j-1]] ? st[i][j-1] : st[i+d][j-1];
    }
}
inline int query(int l,int r) {
    int g = Log[r-l+1] , d = 1 << g;
    return sum[st[l][g]] < sum[st[r-d+1][g]] ? st[l][g] : st[r-d+1][g];
}
struct Node {
    int p,l,r;
    friend bool operator < (const Node &a,const Node &b) {
        return sum[a.p] - sum[query(a.l,a.r)] < sum[b.p] - sum[query(b.l,b.r)];
    }
};
priority_queue<Node> q;

inline void pop() {
    Node pos = q.top(); q.pop();
    int m = query(pos.l,pos.r);
    ans += sum[pos.p] - sum[m];
    if( pos.l < m ) q.push((Node){pos.p,pos.l,m-1});
    if( m < pos.r ) q.push((Node){pos.p,m+1,pos.r});
}
int main() {
    scanf("%d%d%d%d",&n,&k,&L,&R);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    gen();
    for(int i=L;i<=n;i++) {
        q.push((Node){i,max(i-R,0),i-L});
    }
    while(k--)
        pop();
    printf("%lld\n",ans);
    return 0;
}

