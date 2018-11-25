#include<cstdio>
typedef long long int lli;
const int maxs=1<<10,maxl=13;
const int mod=1e9+7;

char ina[maxl],inb[maxl];
int faila[maxl],failb[maxl],nxta[maxl][3],nxtb[maxl][3];
int f[2][maxs][maxl][maxl];
int n,m,c,q,full,mask,cur;
lli ans;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        ret = ( tim & 1 ) ? ret * base % mod : ret;
        base = ( tim >>= 1 ) ? base * base % mod : base;
    }
    return ret;
}
inline char gid(char c) {
    return c == 'W' ? 0 : c == 'B' ? 1 : 2;
}
inline void kmp(char* s,int* fail,int nxt[maxl][3]) {
    for(int i=1;i<=c;i++) s[i] = gid(s[i]);
    fail[0] = fail[1] = 0;
    for(int i=2,j=0;i<=c;i++) {
        while( j && s[j+1] != s[i] ) j = fail[j];
        fail[i] = ( j += ( s[j+1] == s[i] ) );
    }
    for(int i=0;i<=c;i++) for(int cur=0;cur<3;cur++) {
        int k = i;
        while( k && s[k+1] != cur ) k = fail[k];
        nxt[i][cur] = ( k += ( s[k+1] == cur ) );
    }
}

inline void reset(int f[maxs][maxl][maxl]) {
    for(int i=0;i<full;i++) for(int j=0;j<=c;j++) for(int k=0;k<=c;k++) f[i][j][k] = 0;
}

int main() {
    scanf("%d%d%d%d",&n,&m,&c,&q) , full = 1 << ( m - c + 1 ) , mask = full - 1;
    while(q--) {
        scanf("%s%s",ina+1,inb+1) , kmp(ina,faila,nxta) , kmp(inb,failb,nxtb) , reset(f[cur=0]) , f[cur][0][0][0] = 1;
        for(int i=1;i<=n;i++) {
            reset(f[cur^=1]);
            for(int j=0;j<full;j++) for(int pa=0;pa<c;pa++) for(int pb=0;pb<c;pb++) f[cur][j][0][0] = ( f[cur][j][0][0] + f[cur^1][j][pa][pb] ) % mod;
            for(int j=1;j<=m;j++) {
                reset(f[cur^=1]);
                for(int sta=0;sta<full;sta++) for(int pa=0;pa<c;pa++) for(int pb=0;pb<c;pb++) if( f[cur^1][sta][pa][pb] )for(int sel=0;sel<3;sel++) {
                    int nowa = nxta[pa][sel] , nowb = nxtb[pb][sel] , nowsta = sta;
                    if( j >= c ) nowsta &= ( mask ^ ( 1 << ( j - c ) ) ); // clear bit j - c .
                    if( nowa == c ) nowsta ^= 1 << ( j - c ) , nowa = faila[nowa]; // set bit j - c .
                    if( nowb == c ) {
                        if( sta & ( 1 << ( j - c ) ) ) continue; // paired .
                        else nowb = failb[nowb];
                    }
                    f[cur][nowsta][nowa][nowb] = ( f[cur][nowsta][nowa][nowb] + f[cur^1][sta][pa][pb] ) % mod;
                }
            }
        }
        ans = fastpow(3,n*m);
        for(int sta=0;sta<full;sta++) for(int pa=0;pa<c;pa++) for(int pb=0;pb<c;pb++) ans = ( ans - f[cur][sta][pa][pb] + mod ) % mod;
        printf("%lld\n",ans);
    }
    return 0;
}

