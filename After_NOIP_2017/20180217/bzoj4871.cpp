#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
using namespace std;
const int maxn=5e5+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],cnt;
int f[maxn][6],d[maxn],p[maxn],pp[maxn],n[maxn],nn[maxn];

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void u(int& x,const int &y) {
    x = max(x,y);
}
inline void pre(int x,int fa) {
    d[x] = -1 ;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) pre(t[at],x) , ++d[x];
}
inline void dfs(int x,int fa) {
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) dfs(t[at],x);
    f[x][0] = d[x];
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) u(f[x][0],f[t[at]][0]+d[x]);
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) u(f[x][1],f[t[at]][2]+1) , u(f[x][1],f[t[at]][1]);
    int mx1 = 0;
    f[x][2] = d[x] + 1;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) u(f[x][2],mx1+f[t[at]][0]+d[x]+1) , u(mx1,f[t[at]][0]);
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) u(f[x][3],f[t[at]][3]+d[x]);
    int mx2 = 0 ; mx1 = -inf;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) {
        u(f[x][3],mx1+f[t[at]][0]+d[x]);
        u(f[x][3],max(f[t[at]][1],f[t[at]][2])-1+mx2+d[x]);
        u(mx1,max(f[t[at]][1],f[t[at]][2])-1);
        u(mx2,f[t[at]][0]);
    }
    int mx3; mx1 = mx2 = mx3 = 0;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) {
        int v = f[t[at]][0];
        if( v > mx1 ) swap( v , mx1 );
        if( v > mx2 ) swap( v , mx2 );
        if( v > mx3 ) swap( v , mx3 );
    }
    u(f[x][3],mx1+mx2+mx3+d[x]);
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) u(f[x][4],max(f[t[at]][4],f[t[at]][5]+1));
    mx1 = mx2 = -inf;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) {
        u(f[x][4],f[t[at]][1]+mx1-1) , u(f[x][4],f[t[at]][1]+mx2) ,
        u(f[x][4],f[t[at]][2]+mx1) , u(f[x][4],f[t[at]][2]+mx2+1) ,
        u(mx1,f[t[at]][1]) , u(mx2,f[t[at]][2]);
    }
    mx1 = -inf , mx2 = 0;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) {
        u(f[x][5],mx1+f[t[at]][0]+d[x]+1) , u(f[x][5],f[t[at]][3]+mx2+d[x]+1) ,
        u(mx1,f[t[at]][3]) , u(mx2,f[t[at]][0]);
    }
    int mx4; mx1 = mx2 = mx3 = mx4 = 0;
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) {
        int v = f[t[at]][0];
        if( v > mx1 ) swap( v , mx1 );
        if( v > mx2 ) swap( v , mx2 );
        if( v > mx3 ) swap( v , mx3 );
        if( v > mx4 ) swap( v , mx4 );
    }
    u(f[x][5],mx1+mx2+mx3+mx4+d[x]+1);
    vector<int> v; v.push_back(0);
    for(int at=s[x];at;at=nxt[at]) if(t[at]!=fa) v.push_back(t[at]);
    const int sz = (signed)v.size() - 1;
    nn[sz+1] = n[sz+1] = 0;
    for(int i=1;i<=sz;i++) pp[i] = max( pp[i-1] , f[v[i]][0] + p[i-1] ) , p[i] = max( p[i-1] , f[v[i]][0] );
    for(int i=sz;i>=1;i--) nn[i] = max( nn[i+1] , f[v[i]][0] + n[i+1] ) , n[i] = max( n[i+1] , f[v[i]][0] );
    for(int i=1;i<=sz;i++) {
        const int vv = max(f[v[i]][1],f[v[i]][2]);
        u(f[x][5],pp[i-1]+vv+d[x]) , u(f[x][5],nn[i+1]+vv+d[x]) ,
        u(f[x][5],p[i-1]+vv+n[i+1]+d[x]);
    }
}

inline void reset(int sz) {
    #define m(x) memset(x,0,sizeof(x[0])*(sz+1))
    m(s),m(d),m(p),m(pp),m(n),m(nn) , cnt = 0;
}
inline void init(int sz) {
    static const int inf = 0x3f3f3f3f;
    for(int i=0;i<=sz;i++)
        for(int j=0;j<6;j++) f[i][j] = -inf;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,T,x;
    T = getint() , x = getint();
    while(T--) {
        n = getint();
        if(x) {
            getint() , getint();
            if(x-1) getint() , getint();
        }
        init(n);
        for(int i=1,a,b;i<n;i++) {
            a = getint() , b = getint();
            addedge(a,b) , addedge(b,a);
        }
        pre(1,-1) , dfs(1,-1);
        printf("%d\n",max(f[1][4],f[1][5]));
        reset(n);
    }
    return 0;
}
