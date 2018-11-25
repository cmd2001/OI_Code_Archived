#include<cstdio>
#include<utility>
#include<queue>
#include<cctype>
#define bool unsigned char
typedef std::pair<int,int> pii;
using namespace std;
const int maxn=5e2+1e1;

bool in[maxn][maxn];
int n,m,ans;
queue<pii> q;

inline void update(int x,int y) {
    for(int i=1;i<=n;i++) if( in[y][i] && !in[i][x] ) in[i][x] = 1 , q.push(make_pair(i,x));
}

inline char nextchar() {
    static const int BS = 1 << 20;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1,a,b;i<=m;i++) a = getint() , b = getint() , in[a][b] = 1 , q.push(make_pair(a,b));
    while( q.size() ) update(q.front().first,q.front().second) , q.pop();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ans += in[i][j];
    printf("%d\n",ans);
    return 0;
}
