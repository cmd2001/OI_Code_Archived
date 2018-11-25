#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
#include<utility>
using namespace std;
const int maxn=1e5+1e2,maxe=1e6+1e2;
const int inf=0x3f3f3f3f;

struct Node {
    int x,y;
    friend bool operator < (const Node &a,const Node &b) {
        return a.y != b.y ? a.y > b.y : a.x > b.x;
    }
}dis[maxn];
priority_queue<pair<Node,int> > q;

int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1];
bool vis[maxn];

inline void coredge(int from,int to,int len) {
    static int cnt;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void addedge(int a,int b,int l) {
    coredge(a,b,l) , coredge(b,a,l);
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0; char ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int m,k;
    getint() , m = getint() , k = getint() , memset(dis,0x3f,sizeof(dis));
    for(int i=1,a,b,le;i<=m;i++) a = getint() , b = getint() , le = getint()  ,addedge(a,b,le);
    for(int i=1,x;i<=k;i++) x = getint() , dis[x].x = dis[x].y = 0 , q.push(make_pair(dis[x],x));
    while( q.size() ) {
        const int pos = q.top().second; q.pop();
        if( vis[pos] ) continue;
        vis[pos] = 1;
        for(int at=s[pos];at;at=nxt[at]) if( dis[pos].y + l[at] < dis[t[at]].y ) {
            if( dis[pos].y + l[at] < dis[t[at]].x ) dis[t[at]].y = dis[t[at]].x , dis[t[at]].x = dis[pos].y + l[at];
            else dis[t[at]].y = dis[pos].y + l[at];
            q.push(make_pair(dis[t[at]],t[at]));
        }
    }
    printf("%d\n",dis->y);
    return 0;
}

