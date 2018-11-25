#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

struct PreNode {
    int x,y,z;
    friend bool operator < (const PreNode &a,const PreNode &b) {
        return a.x != b.x ? a.x < b.x : a.y != b.y ? a.y < b.y : a.z < b.z;
    }
    friend bool operator != (const PreNode &a,const PreNode &b) {
        return a.x != b.x || a.y != b.y || a.z != b.z;
    }
}ps[maxn];
struct Node {
    int x,y,z,siz,ans,bel;
    Node operator = (const PreNode &b) {
        x = b.x , y = b.y , z = b.z;
        return *this;
    }
}ns[maxn];
struct BinaryIndexTree {
    int dat[maxn<<1],len;
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= len )
            dat[pos] += x ,
            pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos )
            ret += dat[pos] ,
            pos -= lowbit(pos);
        return ret;
    }
    inline void resize(int lim) {
        len = lim;
    }
}bit;
bool cmpx(const Node &a,const Node &b) {
    return a.x != b.x ? a.x < b.x : a.y != b.y ? a.y < b.y : a.z < b.z;
}
bool cmpy(const Node &a,const Node &b) {
    return a.y != b.y ? a.y < b.y : a.bel < b.bel;
}

inline void solve(int ll,int rr) {
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    solve(ll,mid) , solve(mid+1,rr);
    for(int i=ll;i<=mid;i++) ns[i].bel = 0;
    for(int i=mid+1;i<=rr;i++) ns[i].bel = 1;
    sort(ns+ll,ns+rr+1,cmpy);
    for(int i=ll;i<=rr;i++)
        if( !ns[i].bel ) bit.update(ns[i].z,ns[i].siz);
        else ns[i].ans += bit.query(ns[i].z);
    for(int i=ll;i<=rr;i++)
        if( !ns[i].bel ) bit.update(ns[i].z,-ns[i].siz);
}

int main() {
    static int ans[maxn],n,lim,cnt;
    scanf("%d%d",&n,&lim);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&ps[i].x,&ps[i].y,&ps[i].z);
    sort(ps+1,ps+1+n);
    for(int i=1;i<=n;i++) {
        if( ps[i] != ps[i-1] ) ns[++cnt] = ps[i];
        ++ns[cnt].siz;
    }
    sort(ns+1,ns+1+cnt,cmpx);
    bit.resize(lim);
    solve(1,cnt);
    for(int i=1;i<=cnt;i++)
        ns[i].ans += ns[i].siz - 1;
    for(int i=1;i<=cnt;i++)
        ans[ns[i].ans] += ns[i].siz;
    for(int i=0;i<n;i++)
        printf("%d\n",ans[i]);
    return 0;
}
