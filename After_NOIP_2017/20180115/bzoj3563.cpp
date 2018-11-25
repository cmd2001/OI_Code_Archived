#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=5e5+1e2,maxq=5e4+1e2;

struct Edge {
    int a,b;
}es[maxm];
int fa[maxn];
int k[maxq],sum[maxq],cnt,siz;
char buf[maxm],vis[maxm];

inline int findfa(int x) {
    return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}

inline int count(char* sou,int len) {
    int ret = 0;
    for(int i=1;i<=len;i++)
        if( isdigit(sou[i]) && !isdigit(sou[i-1]) )
            ++ret;
    return ret;
}
inline void getlin(char* dst,int &len) {
    len = 0;
    char ch = getchar();
    while( ch != '\n' && ch != '\r' )
        dst[++len] = ch , ch = getchar();
    dst[len+1] = '\0';
}
inline int findint(char* sou) {
    int ret = 0;
    while( !isdigit(*sou) ) ++*sou;
    do ret=ret*10+*sou-'0'; while( isdigit(*++sou) );
    return ret;
}
inline int nextint(char* &sou) {
    int ret = 0;
    while( !isdigit(*sou) ) ++sou;
    do ret=ret*10+*sou-'0'; while( isdigit(*++sou) );
    return ret;
}

int main() {
    static int n,m,q,len;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&es[i].a,&es[i].b);
    scanf("%d",&q);
    for(int i=1;i<=q;i++) {
        getlin(buf,len);
        while( !len ) getlin(buf,len);
        k[i] = findint(buf+1);
        sum[i-1] = k[i] ^ ( count(buf,len) - 1 );
    }
    
    char* now = buf + 1;
    cnt = nextint(now) ^ sum[q-1];
    for(int i=1;i<=cnt;i++)
        vis [ nextint(now) ^ sum[q-1] ] = 1;
    for(int i=1;i<=n;i++) fa[i] = i;
    for(int i=1;i<=m;i++)
        if( ( !vis[i] ) && findfa(es[i].a) != findfa(es[i].b) )
            fa[findfa(es[i].a)] = findfa(es[i].b) , ++siz;
    for(int i=q-1;i;i--)
        sum[i] -= sum[i-1];
    for(int i=1;i<q;i++)
        puts( sum[i] ? "Connected" : "Disconnected");
    puts( siz == n-1 ? "Connected" : "Disconnected" );
    
    return 0;
}