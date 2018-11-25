#include<cstdio>
#define lli long long int
using namespace std;
const int maxn=1e2+1e1;
const int mod = 1e9;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

lli dat[maxn][maxn];
int n;

inline void swp(lli &a,lli &b) {
    a ^= b ^= a ^= b;
}
inline lli calc() {
    lli ret = 1 , mul = 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            dat[i][j] = ( dat[i][j] % mod + mod ) % mod;
    for(int i=1;i<=n;i++) {
        for(int j=i+1;j<=n;j++)
            if( dat[j][i] ) {
                while( dat[j][i] ) {
                    const lli t = dat[i][i] / dat[j][i];
                    for(int k=1;k<=n;k++)
                        dat[i][k] -= dat[j][k] * t % mod ,
                        dat[i][k] = ( dat[i][k] + mod ) % mod;
                    for(int k=1;k<=n;k++)
                        swp(dat[i][k],dat[j][k]);
                    mul = -mul;
                }
            }
        if( !dat[i][i] )
            return 0;
    }
    for(int i=1;i<=n;i++)
        ret = ret * dat[i][i] % mod;
    return ( ret * mul % mod + mod ) % mod;
}


int a,b;
char in[12][12];
int id[12][12],cnt;

inline bool judge(int x,int y) {
    return x > 0 && x <= a && y > 0 && y <= b && in[x][y] == '.';
}

int main() {
    scanf("%d%d",&a,&b);
    for(int i=1;i<=a;i++) {
        scanf("%s",in[i]+1);
        for(int j=1;j<=b;j++)
            if( in[i][j] == '.' )
                id[i][j] = ++n;
    }
    for(int i=1;i<=a;i++)
        for(int j=1;j<=b;j++)
            if( in[i][j] == '.' )
                for(int k=0;k<4;k++) {
                    const int tx = i + dx[k] , ty = j + dy[k];
                    if( judge(tx,ty) ) {
                        ++dat[id[i][j]][id[i][j]];
                        --dat[id[i][j]][id[tx][ty]];
                    }
                }
    
    --n;
    
    printf("%lld\n",calc());
    
    return 0;
}

