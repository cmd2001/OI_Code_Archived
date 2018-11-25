#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e4+1e2,maxm=5e3+1e2;

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
    int dat[maxn<<3],sum[maxn<<3],cnt;
    
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr )
            return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    inline void upgrade(int pos) {
        if( dat[pos] )
            sum[pos] = r[pos] - l[pos] + 1;
        else if( l[pos] == r[pos] )
            sum[pos] = 0;
        else
            sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline void update(int pos,int ll,int rr,int delta) {
        if( rr < l[pos] || r[pos] < ll )
            return;
        if( ll <= l[pos] && r[pos] <= rr ) {
            dat[pos] += delta;
            upgrade(pos);
            return;
        }
        update(lson[pos],ll,rr,delta);
        update(rson[pos],ll,rr,delta);
        upgrade(pos);
    }
    inline int query() {
        return sum[1];
    }
    
    inline void res() {
        cnt = 0;
        memset(sum,0,sizeof(sum));
        memset(dat,0,sizeof(dat));
        memset(lson,0,sizeof(lson));
        memset(rson,0,sizeof(rson));
    }
}st;

struct Node {
    int l,r,up,sta; // 1 means in , -1 means out
    void in(int ll=0,int rr=0,int uu=0,int ss=0) {
        l = ll , r = rr , up = uu , sta = ss;
    }
    friend bool operator < (const Node &a,const Node &b) {
        return a.up != b.up ? a.up < b.up : a.sta > b.sta;
    }
}hor[maxm<<1],ver[maxm<<1];

int n,ans,last,ch,cv;

inline void work(Node* ns,int len) {
    last = 0;
    st.res();
    st.build(st.cnt=1,1,2e4+1);
    for(int i=1;i<=len;i++) {
        st.update(1,ns[i].l+1,ns[i].r,ns[i].sta);
        /*debug<<"i = "<<i<<endl;
        debug<<"l = "<<ns[i].l<<"r = "<<ns[i].r<<"sta = "<<ns[i].sta<<endl;
        debug<<"up = "<<ns[i].up<<endl;*/
        if( ns[i].sta == 1 ) {
            int q = st.query();
            ans += q - last,
            //debug<<"last = "<<last<<"q = "<<q<<endl;
            last = q;
        }
        else
            last = st.query();
    }
}

inline void init() {
    ans = last = ch = cv = 0;
}
int main() {
    static int sx,sy,tx,ty;
    while( scanf("%d",&n) == 1 ) {
        init();
        for(int i=1;i<=n;i++) {
            scanf("%d%d%d%d",&sx,&sy,&tx,&ty);
            sx += 1e4 + 1 , sy += 1e4 + 1 , tx += 1e4 + 1 , ty += 1e4 + 1;
            //sx += 20 , sy += 20 , tx += 20 , ty += 20;
            hor[++ch].in(sx,tx,ty,-1);
            hor[++ch].in(sx,tx,sy,1);
            ver[++cv].in(sy,ty,tx,-1);
            ver[++cv].in(sy,ty,sx,1);
        }
        
        sort(hor+1,hor+1+ch);
        sort(ver+1,ver+1+cv);
        
        work(hor,ch);
        
        //debug<<"now working ver"<<endl;
        work(ver,cv);
        
        ans <<= 1;
        
        printf("%d\n",ans);
    }
    
    return 0;
}