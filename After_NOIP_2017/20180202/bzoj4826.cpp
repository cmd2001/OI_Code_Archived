#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lli long long int
using namespace std;
const int maxn=2e5+1e2;

struct Query {
    int l,r,id;
}qs[maxn];
vector<Query> v[maxn];
int in[maxn],r[maxn];
lli ans[maxn],p1,p2;
int stk[maxn],top;
int n,m;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
    lli sum[maxn<<3],lazy[maxn<<3];
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void add(int pos,lli x) {
        if( !pos ) return;
        sum[pos] += ( r[pos] - l[pos] + 1 ) * x ,
        lazy[pos] += x;
    }
    inline void push(int pos) {
        if( lazy[pos] ) {
            add(lson[pos],lazy[pos]);
            add(rson[pos],lazy[pos]);
            lazy[pos] = 0;
        }
    }
    inline void update(int pos,int ll,int rr,lli x) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) {
            add(pos,x);
            return;
        }
        push(pos);
        update(lson[pos],ll,rr,x);
        update(rson[pos],ll,rr,x);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline lli query(int pos,int ll,int rr) {
        if( rr < l[pos] || r[pos] < ll ) return 0;
        if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
        push(pos);
        return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
    }
    inline void clear() {
        memset(sum,0,sizeof(lli)*(cnt+1));
        memset(lazy,0,sizeof(lli)*(cnt+1));
    }
}st;

inline void getr() {
    in[n+1] = n+1 , stk[top=1] = n+1;
    for(int i=n;i;i--) {
        while( top && in[stk[top]] < in[i] ) --top;
        r[i] = stk[top];
        stk[++top] = i;
    }
}
inline void cutq() {
    for(int i=1;i<=m;i++)
        v[qs[i].l].push_back(qs[i]);
}
inline void calc() {
    getr() , cutq();
    for(int i=n;i;i--) {
        st.update(1,i+1,r[i],p2);
        st.update(1,r[i],r[i],p1-p2*2);
        for(unsigned j=0;j<v[i].size();j++) {
            ans[v[i][j].id] += st.query(1,1,v[i][j].r);
        }
    }
}
inline void rev() {
    reverse(in+1,in+n+1);
    for(int i=1;i<=m;i++) {
        qs[i].l = n - qs[i].l + 1 ,
        qs[i].r = n - qs[i].r + 1 ;
        swap( qs[i].l , qs[i].r );
    }
    for(int i=1;i<=n;i++)
        v[i].clear();
    st.clear();
}

int main() {
    scanf("%d%d%lld%lld",&n,&m,&p1,&p2);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&qs[i].l,&qs[i].r) , qs[i].id = i;
    st.build(st.cnt=1,1,n+1);
    calc();
    rev();calc();
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}

