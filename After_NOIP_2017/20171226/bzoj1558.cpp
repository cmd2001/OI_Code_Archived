#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

inline void up(int &dst,int sou1,int sou2) {
    dst = min( dst , min( sou1 , sou2 ) );
}
struct Node {
    int f[4];
    lli l,r;
    Node() {
        memset(f,0,sizeof(f));
        l = r = 0;
    }
    bool illeagle() {
        for(int i=0;i<4;i++)
            if( ( f[i] < 0 )  || ( i!=0 && f[i]==0 ) )
                return 1;
        return 0;
    }
    friend Node operator + (const Node &a,const Node &b) {
        Node ret;
        ret.l = a.l , ret.r = b.r;
        const int lam = a.r == b.l;
        ret.f[0] = a.f[2] + b.f[1] - lam; // 0 means don't select left and right
        up( ret.f[0] , a.f[0] + b.f[1] , a.f[2] + b.f[0] );
        ret.f[1] = a.f[3] + b.f[1] - lam; // 1 means select left and don't select right
        up( ret.f[1] , a.f[1] + b.f[1] , a.f[3] + b.f[0] );
        ret.f[2] = a.f[2] + b.f[3] - lam; // 2 means don't select left and select right
        up( ret.f[2] , a.f[0] + b.f[3] , a.f[2] + b.f[2] );
        ret.f[3] = a.f[3] + b.f[3] - lam; // 3 means select left and right
        up( ret.f[3] , a.f[3] + b.f[2] , a.f[1] + b.f[3] );
        /*if( ret.illeagle() ) {
            debug<<"Fuck you!"<<endl;
            a.print();
            b.print();
            ret.print();
            debug<<"ended"<<endl;
        }*/
        /*debug<<"a = "<<endl;a.print();
        debug<<"b = "<<endl;b.print();
        debug<<"ret = "<<endl;ret.print();*/
        return ret;
    }
    inline void print() const {
        for(int i=0;i<4;i++)
            debug<<f[i]<<" ";debug<<endl;
        debug<<l<<" "<<r<<endl;
    }
}ns[maxn<<3];

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],in[maxn];
lli lazy[maxn<<3];
int n,m,cnt;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) {
        ns[pos].l = ns[pos].r = in[ll];
        ns[pos].f[1] = ns[pos].f[2] = ns[pos].f[3] = 1;
        return;
    }
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
    if( ns[pos].illeagle() )
        ns[pos].print();
}

inline void push(int pos) {
    if( lazy[pos] ) {
        if( lson[pos] ) {
            lazy[lson[pos]] += lazy[pos],
            ns[lson[pos]].l += lazy[pos],
            ns[lson[pos]].r += lazy[pos];
        }
        if( rson[pos] ) {
            lazy[rson[pos]] += lazy[pos],
            ns[rson[pos]].l += lazy[pos],
            ns[rson[pos]].r += lazy[pos];
        }
        lazy[pos] = 0;
    }
}
inline void update(int pos,int ll,int rr,lli x) {
    if( rr < l[pos] || r[pos] < ll )
        return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        lazy[pos] += x,
        ns[pos].l += x , ns[pos].r += x;
        return;
    }
    push(pos);
    update(lson[pos],ll,rr,x);
    update(rson[pos],ll,rr,x);
    //debug<<"merging"<<lson[pos]<<" "<<rson[pos]<<"into"<<pos<<endl;
    ns[pos] = ns[lson[pos]] + ns[rson[pos]];
}
inline Node query(int pos,int ll,int rr) {
    if( ll <= l[pos] && r[pos] <= rr )
        return ns[pos];
    push(pos);
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid )
        return query(lson[pos],ll,rr);
    if( ll > mid )
        return query(rson[pos],ll,rr);
    return query(lson[pos],ll,rr) + query(rson[pos],ll,rr);
}

int main() {
    static char com[10];
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    n--;
    for(int i=1;i<=n;i++)
        in[i] = in[i+1] - in[i];
    
    build(cnt=1,1,n);
    
    
    scanf("%d",&m);
    for(int i=1,l,r;i<=m;i++) {
        scanf("%s%d%d",com,&l,&r);
        if( *com == 'B' ) {
            if( l != r ) {
                Node ans = query(1,l,r-1);
                printf("%d\n",ans.f[3]);
            }
            else puts("1");
        }
        else {
            lli a,b;
            scanf("%lld%lld",&a,&b);
            if( l != 1 )
                update(1,l-1,l-1,a);
            if( l != r )
                update(1,l,r-1,b);
            if( r != n + 1 ) {
                //debug<<"This is the last operation"<<endl;
                update(1,r,r, -( a + b * ( r - l  ) ) );
            }
        }
    }
    
    /*for(int i=1;i<=n;i++)
        printf("%lld ",query(1,i,i).l);
    puts("");*/
    
    return 0;
}


