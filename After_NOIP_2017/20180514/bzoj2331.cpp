#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<tr1/unordered_map>
using namespace std;
using namespace tr1;
const int maxn=1e2+1e2;
const int mod=20110520;

int sta[maxn],nxt[maxn];
char in[maxn][maxn]; // in == 1 means empty .
int n,m,cur,fx,fy;
unordered_map<int,int> f[2];

inline void unzip(int* sta,int ss) {
    for(int i=m+1;i;i--) sta[i] = ss % 3 , ss /= 3;
}
inline int zip(int* sta) {
    int ret = 0;
    for(int i=1;i<=m+1;i++) ret = ret * 3 + sta[i];
    return ret;
}

inline void core_trans(unordered_map<int,int> &dst,int x,int y,int add) {
    memcpy(nxt,sta,sizeof(int)*(m+2));
    if( !in[x][y] ) { // not empty .
        if( sta[y] == 0 && sta[y+1] == 0 ) ( dst[zip(nxt)] += add ) %= mod;
        return;
    }
    if( sta[y] == 0 ) {
        if( sta[y+1] == 0 ) {
            nxt[y] = 2 , nxt[y+1] = 2 , ( dst[zip(nxt)] += add ) %= mod;
            nxt[y] = 1 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
            nxt[y] = 0 , nxt[y+1] = 1 , ( dst[zip(nxt)] += add ) %= mod;
        } else if( sta[y+1] == 1 ) {
            nxt[y] = 1 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
            nxt[y] = 0 , nxt[y+1] = 2 , ( dst[zip(nxt)] += add ) %= mod;
        } else if( sta[y+1] == 2 ) {
            nxt[y] = 2 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
            nxt[y] = 0 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
        }
    } else if( sta[y] == 1 ) {
        if( sta[y+1] == 0 ) {
            nxt[y] = 0 , nxt[y+1] = 1 , ( dst[zip(nxt)] += add ) %= mod;
            nxt[y] = 2 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
        } else if( sta[y+1] == 1 ) nxt[y] = 0 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
    } else if( sta[y] == 2 ) {
        if( sta[y+1] == 0 ) {
            nxt[y] = 0 , nxt[y+1] = 0 , ( dst[zip(nxt)] += add ) %= mod;
            nxt[y] = 0 , nxt[y+1] = 2 , ( dst[zip(nxt)] += add ) %= mod;
        }
    }
}
inline void trans(const unordered_map<int,int> &sou,unordered_map<int,int> &dst,int x,int y) {
    dst.clear();
    for(unordered_map<int,int>::const_iterator it=sou.begin();it!=sou.end();it++) if( it->second ) {
        unzip(sta,it->first) , core_trans(dst,x,y,it->second);
    }
}
inline void transline(const unordered_map<int,int> &sou,unordered_map<int,int> &dst) {
    dst.clear();
    for(unordered_map<int,int>::const_iterator it=sou.begin();it!=sou.end();it++) if( it->second && ! ( it->first % 3 ) ) {
        dst[it->first/3] = it->second;
    }
}

inline void revert() { // make m <= n .
    static char tp[maxn][maxn];
    memcpy(tp,in,sizeof(in)) , memset(in,0,sizeof(in));
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) in[j][i] = tp[i][j];
    swap(n,m);
}

int main() {
    scanf("%d%d",&n,&m) , fx = -1 , fy = -1;
    for(int i=1;i<=n;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=m;j++) in[i][j] = in[i][j] == '_';
    }
    
    if( n < m ) revert();
    for(int i=1;i<=n&&!~fx;i++) for(int j=1;j<=m&&!~fx;j++) if(in[i][j]) fx = i , fy = j;
    if( !~fx ) return puts("1") , 0; // nothing to do .
    sta[fy] = 0 , sta[fy+1] = 1 , f[cur][zip(sta)] = 1;
    sta[fy] = 1 , sta[fy+1] = 0 , f[cur][zip(sta)] = 1;
    sta[fy] = sta[fy+1] = 2 , f[cur][zip(sta)] = 1;
    for(int j=fy+1;j<=m;j++) trans(f[cur],f[cur^1],fx,j) , cur ^= 1;
    transline(f[cur],f[cur^1]) , cur ^= 1;
    
    for(int i=fx+1;i<=n;i++) {
        for(int j=1;j<=m;j++)
            trans(f[cur],f[cur^1],i,j) , cur ^= 1;
        transline(f[cur],f[cur^1]) , cur ^= 1;
    }
    
    printf("%d\n",f[cur][0]);
    
    return 0;
}
