#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e5+1e2;
 
int dvs[maxn],mul[maxn][25],n,tar,cnt;
 
inline bool dfs(int pos,int ned,int multi) {
    if( !ned ) return multi == n; --ned;
    while( pos <= cnt - ned ) {
        if( !mul[pos][ned] ) return 0;
        if( (lli)multi * mul[pos][ned] > n ) return 0;
        if( dfs(pos+1,ned,multi*dvs[pos]) ) return 1;
        ++pos;
    }
    return 0;
}
 
inline void getdvs(int x) {
    for(int i=1;(lli)i*i<=x;i++)
        if( ! ( x % i ) ) {
            dvs[++cnt] = i;
            if( i * i != x ) dvs[++cnt] = x / i;
        }
}
inline void getmuls() {
    for(int i=1,j,now;i<=cnt;i++) {
        now = 1 , j = 0;
        while( now <= n && j <= tar && i + j <= cnt ) {
            if( (lli) now * dvs[i+j] > n ) now = 0;
            else now *= dvs[i+j];
            mul[i][j++] = now;
        }
    }
}
 
int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d",&n,&tar) , cnt = 0;
        getdvs(n) , std::sort(dvs+1,dvs+1+cnt) , getmuls();
        puts(dfs(1,tar,1)?"TAK":"NIE");
    }
    return 0;
}
