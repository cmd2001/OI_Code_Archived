#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxm=maxn*4;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

struct Node {
    int pos;
    double dis;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis != b.dis ? a.dis < b.dis : a.pos < b.pos;
    }
};

multiset<Node> ms;
char in[210][210];
int s[maxn],t[maxm<<1],nxt[maxm<<1];
double l[maxm<<1],dis[maxn],L;
unsigned char vis[maxn];
int n,m,cnt,st,ed;

inline void addedge(int from,int to,double len) {
    t[++cnt] = to , l[cnt] = len,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dji() {
    ms.clear();
    memset(dis,0x42,sizeof(dis));
    memset(vis,0,sizeof(vis));
    dis[st] = 0;
    ms.insert((Node){st,0});
    while( ms.size() ) {
        Node now = *ms.begin(); ms.erase(ms.begin());
        if( vis[now.pos] ) continue;
        for(int at=s[now.pos];at;at=nxt[at]) {
            if( dis[t[at]] > now.dis + l[at] ) {
                dis[t[at]] = now.dis + l[at];
                ms.insert((Node){t[at],dis[t[at]]});
            }
        }
    }
}
inline void reset() {
    memset(s,0,sizeof(s));
    cnt = 0;
}
inline bool judge(int xx,int yy) {
    return xx > 0 && xx <= n && yy > 0 && yy <= m;
}
inline int cov(int xx,int yy) {
    return ( xx - 1 ) * m + yy;
}
inline void buildgraph(double v) {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if( in[i][j] != '#' ) {
                //debug<<"i = "<<i<<"j = "<<j<<endl;
                for(int k=0;k<2;k++) {
                    const int tx = i + dx[k] , ty = j + dy[k];
                    if( judge(tx,ty) ) addedge(cov(i,j),cov(tx,ty),1);
                }
                for(int k=2;k<4;k++) {
                    const int tx = i + dx[k] , ty = j + dy[k];
                    if( judge(tx,ty) ) addedge(cov(i,j),cov(tx,ty),v);
                }
                //debug<<"finished"<<endl;
            }
}

inline double bin() {
    static const double eps=1e-7;
    double ll = 0 , rr = 10 , mid;
    //debug<<"in bin"<<endl;
    //exit(0);
    while( rr - ll > eps ) {
        //debug<<"i = "<<i<<endl;
        mid = ( ll + rr ) / 2.0;
        reset();
        buildgraph(mid);
        //debug<<"graph build"<<endl;
        dji();
        if( dis[ed] > L ) rr = mid;
        else ll = mid;
    }
    return ll;
}
inline void getlin(char* dst) {
    char ch = getchar();
    while( ch != '\r' && ch != '\n' )
        *dst++ = ch , ch = getchar();
}

int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%lf%d%d",&L,&n,&m);
        memset(in,0,sizeof(in));
        for(int i=1;i<=n;i++) {
            while( in[i][1] != '#' && in[i][1] != ' ' && in[i][1] != 'S' && in[i][1] != 'E' )
                getlin(in[i]+1);
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if( in[i][j] == 'S' )
                    st = cov(i,j);
                else if( in[i][j] == 'E' )
                    ed = cov(i,j);
        //debug<<"st = "<<st<<"ed = "<<ed<<endl;
        //for(int i=1;i<=n;i++) puts(in[i]+1);
        printf("%0.5lf\n",bin());
    }
    
    return 0;
}