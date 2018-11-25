#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxk=17,maxs=1<<15;
const int mod=1e9+7;

const char c[4]="NOI";
const int nxt[3][3]={{1,0,0},{1,2,0},{1,0,3}};

char in[maxk];
int g[maxk],h[maxk],f[2][3][maxs],trans[maxs][3],bit[maxs],ans[maxk];
int n,k,fs,cur;

inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

inline void decode(int ss) {
    for(int i=1;i<=k;i++) g[i] = g[i-1] + ( ( ss >> ( i - 1 ) ) & 1 );
}
inline int encode() {
    int ret = 0;
    for(int i=1;i<=k;i++) ret |= ( h[i] - h[i-1] ) << ( i - 1 );
    return ret;
}

inline void getrans() {
    for(int i=0;i<fs;i++) {
        decode(i);
        for(int j=0;j<3;j++) {
            for(int t=1;t<=k;t++) h[t] = max( g[t] , in[t] == c[j] ? g[t-1] + 1 : h[t-1] );
            trans[i][j] = encode();
        }
    }
}

int main() {
    scanf("%d%d%s",&n,&k,in+1) , fs = 1 << k , cur = 0;
    for(int i=1;i<fs;i++) bit[i] = bit[i>>1] + ( i & 1 );
    getrans() , f[cur][0][0] = 1;
    for(int i=1;i<=n;i++) {
        cur ^= 1 , memset(f[cur],0,sizeof(f[1]));
        for(int sta=0;sta<fs;sta++) for(int bit=0;bit<3;bit++) for(int ch=0;ch<3;ch++)
        if( nxt[bit][ch] < 3 ) adde(f[cur][nxt[bit][ch]][trans[sta][ch]],f[cur^1][bit][sta]);
    }
    for(int pir=0;pir<3;pir++) for(int sta=0;sta<fs;sta++) adde(ans[bit[sta]],f[cur][pir][sta]);
    for(int i=0;i<=k;i++) printf("%d\n",ans[i]);
    return 0;
}
