#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+1e2;

int x[maxn],y[maxn],xx[maxn],yy[maxn],w[maxn];
bool vl[maxn],vr[maxn];
int n,m,std_ans;

FILE *INP,*OTP;
namespace STD {
    const int maxn=2e4+1e2,maxt=6e5+1e2,maxe=1e7+1e2;
    const int inf=0x3f3f3f3f;
    
    int st,ed,pcnt;
    namespace NetworkFlow {
        int s[maxt<<1],t[maxe<<1],nxt[maxe<<1],f[maxe<<1];
        int dep[maxt<<1];
        inline void coredge(int from,int to,int flow) {
            static int cnt = 1;
            t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
        }
        inline void singledge(int from,int to,int flow) {
            coredge(from,to,flow) , coredge(to,from,0);
        }
        inline bool bfs() {
            memset(dep,-1,sizeof(dep)) , dep[st] = 0;
            queue<int> q; q.push(st);
            while( q.size() ) {
                const int pos = q.front(); q.pop();
                for(int at=s[pos];at;at=nxt[at]) if( f[at] && !~dep[t[at]] ) dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
            }
            return ~dep[ed];
        }
        inline int dfs(int pos,int flow) {
            if( pos == ed ) return flow;
            int ret = 0 , now = 0;
            for(int at=s[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
                now = dfs(t[at],min(flow,f[at])) , ret += now , flow -= now , f[at] -= now , f[at^1] += now;
                if( !flow ) return ret;
            }
            if( !ret ) dep[pos] = -1;
            return ret;
        }
        inline int dinic() {
            int ret = 0;
            while( bfs() ) ret += dfs(st,inf);
            return ret;
        }
    }

    int srt[maxn],len;

    struct Point {
        int x,y,id;
        friend bool operator < (const Point &a,const Point &b) {
            return a.y < b.y;
        }
    }in[maxn];

    inline bool cmp(const Point &x,const Point &y) {
        return x.x < y.x;
    }
    
    struct BinarySearchTree {
        int l[maxt],r[maxt],miy[maxt],miid[maxt],lson[maxt],rson[maxt],rid[maxt],cnt;
        inline void build(int &pos,int ll,int rr) {
            rid[pos=++cnt] = ++pcnt; const int mid = ( ll + rr ) >> 1;
            NetworkFlow::singledge(rid[pos],in[mid].id,1) , miy[pos] = in[mid].y , miid[pos] = in[mid].id;
            l[pos] = in[ll].y , r[pos] = in[rr].y;
            if( ll < mid ) build(lson[pos],ll,mid-1) , NetworkFlow::singledge(rid[pos],rid[lson[pos]],inf);
            if( mid < rr ) build(rson[pos],mid+1,rr) , NetworkFlow::singledge(rid[pos],rid[rson[pos]],inf);
        }
        inline void query(int pos,const int &ll,const int &rr,const int &id) {
            if( !pos || rr < l[pos] || r[pos] < ll ) return;
            if( ll <= l[pos] && r[pos] <= rr ) return NetworkFlow::singledge(id,rid[pos],1);
            if( ll <= miy[pos] && miy[pos] <= rr ) NetworkFlow::singledge(id,miid[pos],1);
            query(lson[pos],ll,rr,id) , query(rson[pos],ll,rr,id);
        }
    }bst;
    struct SegmentTree {
        int vl[maxn<<2],vr[maxn<<2],rid[maxn<<2],roots[maxn<<2];
        #define lson(pos) (pos<<1)
        #define rson(pos) (pos<<1|1)
        inline void build(int pos,int l,int r,int ll,int rr) {
            vl[pos] = ll , vr[pos] = rr , rid[pos] = ++pcnt;
            if( l == r ) return;
            const int mid = ( l + r ) >> 1 , tmid = upper_bound(in+ll,in+rr+1,(Point){mid,-1,-1},cmp) - in - 1;
            build(lson(pos),l,mid,ll,tmid) , build(rson(pos),mid+1,r,tmid+1,rr);
            NetworkFlow::singledge(rid[pos],rid[lson(pos)],inf) , NetworkFlow::singledge(rid[pos],rid[rson(pos)],inf);
        }
        inline void dfs(int pos,int l,int r) {
            if( l == r ) return sort(in+vl[pos],in+vr[pos]+1) , bst.build(roots[pos],vl[pos],vr[pos]);
            const int mid = ( l + r ) >> 1;
            dfs(lson(pos),l,mid) , dfs(rson(pos),mid+1,r);
            sort(in+vl[pos],in+vr[pos]+1) , bst.build(roots[pos],vl[pos],vr[pos]); // maybe we should use merge-sort here .
        }
        inline void query(int pos,int l,int r,const int &ll,const int &rr,const int &yll,const int &yrr,const int &id) {
            if( ll <= l && r <= rr ) return bst.query(roots[pos],yll,yrr,id);
            const int mid = ( l + r ) >> 1;
            if( ll <= mid ) query(lson(pos),l,mid,ll,rr,yll,yrr,id);
            if( mid < rr ) query(rson(pos),mid+1,r,ll,rr,yll,yrr,id);
        }
    }sgt;

    void main() {
        st = n + m + 1 , pcnt = ed = n + m + 2;
        for(int i=1;i<=n;i++) NetworkFlow::singledge(i,ed,1);
        for(int i=1;i<=m;i++) NetworkFlow::singledge(st,n+i,1);
        for(int i=1,x,y;i<=n;i++) {
            fscanf(INP,"%d%d",&x,&y);
            ::x[i] = x , ::y[i] = y;
            in[i].x = x + y , in[i].y = x - y , in[i].id = i; // covert .
        }
        sort(in+1,in+1+n,cmp);
        for(int i=1;i<=n;i++) {
            if( i == 1 || in[i].x != srt[len] ) srt[++len] = in[i].x;
            in[i].x = len;
        }
        sgt.build(1,1,len,1,n) , sgt.dfs(1,1,len);
        for(int i=1,x,y,d,ix,iy,l,r;i<=m;i++) {
            fscanf(INP,"%d%d%d",&ix,&iy,&d);
            ::xx[i] = ix , ::yy[i] = iy , ::w[i] = d;
            x = ix + iy , y = ix - iy;
            l = lower_bound(srt+1,srt+1+len,x-d) - srt , r = upper_bound(srt+1,srt+1+len,x+d) - srt - 1;
            if( l > r ) continue;
            sgt.query(1,1,len,l,r,y-d,y+d,i+n);
        }
        std_ans = NetworkFlow::dinic();
    }
}

inline void AC() { exit(0); }
inline void WA() { exit(1); }

inline int readint() {
    static int ret = 0;
    if( !~fscanf(OTP,"%d",&ret) ) WA();
    return ret;
}

inline int dis(int i,int j) {
    return abs(x[i]-xx[j]) + abs(y[i]-yy[j]);
}
int main(int argc,char** argv) {
    static int usr_ans,i,j;
    INP = fopen(argv[1],"r") , OTP = fopen(argv[2],"r");
    fscanf(INP,"%d%d",&n,&m) , STD::main() , usr_ans = readint();
    if( usr_ans != std_ans ) WA();
    while( usr_ans-- ) {
        i = readint() , j = readint();
        if( i < 0 || j < 0 || i > n || j > m ) WA();
        if( vl[i] || vr[j] ) WA();
        if( dis(i,j) > w[j] ) WA();
        vl[i] = vr[j] = 1;
    }
    AC();
}

