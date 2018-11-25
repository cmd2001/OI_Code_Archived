#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
using namespace std;
const int maxn=5e2+1e1,maxe=maxn*maxn,maxq=6e4+1e2;

int n;
struct BinaryIndexTree {
    int dat[maxn][maxn];
    #define lowbit(x) (x&-x)
    inline void update(int x,int y,int v) {
        for(int i=x;i<=n;i+=lowbit(i)) for(int j=y;j<=n;j+=lowbit(j)) dat[i][j] += v;
    }
    inline int query(int x,int y) {
        int ret = 0;
        for(int i=x;i;i-=lowbit(i)) for(int j=y;j;j-=lowbit(j)) ret += dat[i][j];
        return ret;
    }
    inline void res() {
        memset(dat,0,sizeof(dat));
    }
}bit;

struct Query {
    int sx,tx,sy,ty,k,id;
}qs[maxq],tp[2][maxq];

vector<pair<int,int> > v[maxe];
int in[maxn][maxn],srt[maxe],len;
int ans[maxq];

inline int sum(int sx,int tx,int sy,int ty) {
    --sx , --sy;
    return bit.query(tx,ty) - bit.query(tx,sy) - bit.query(sx,ty) + bit.query(sx,sy);
}
inline void solve(int ql,int qr,int nl,int nr) {
    if( qr < ql ) return;
    if( nl == nr ) {
        for(int i=ql;i<=qr;i++) ans[qs[i].id] = nl;
        return;
    }
    int qmid , nmid = ( nl + nr ) >> 1 , llen = 0 , rlen = 0;
    for(int i=nl;i<=nmid;i++) for(unsigned j=0;j<v[i].size();j++) bit.update(v[i][j].first,v[i][j].second,1);
    for(int i=ql,su;i<=qr;i++) {
        if( ( su = sum(qs[i].sx,qs[i].tx,qs[i].sy,qs[i].ty) ) >= qs[i].k ) tp[0][++llen] = qs[i];
        else qs[i].k -= su , tp[1][++rlen] = qs[i];
    }
    for(int i=nl;i<=nmid;i++) for(unsigned j=0;j<v[i].size();j++) bit.update(v[i][j].first,v[i][j].second,-1);
    qmid = ql + llen - 1;
    memcpy(qs+ql,tp[0]+1,sizeof(Query)*llen) , memcpy(qs+qmid+1,tp[1]+1,sizeof(Query)*rlen);
    solve(ql,qmid,nl,nmid) , solve(qmid+1,qr,nmid+1,nr);
}

int main() {
    static int q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) scanf("%d",in[i]+j) , srt[++len] = in[i][j];
    for(int i=1;i<=q;i++) scanf("%d%d%d%d%d",&qs[i].sx,&qs[i].sy,&qs[i].tx,&qs[i].ty,&qs[i].k) , qs[i].id = i;
    sort(srt+1,srt+1+len) , len = unique(srt+1,srt+1+len) - srt - 1;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) v[lower_bound(srt+1,srt+1+len,in[i][j])-srt].push_back(make_pair(i,j));
    solve(1,q,1,len);
    for(int i=1;i<=q;i++) printf("%d\n",srt[ans[i]]);
    return 0;
}

