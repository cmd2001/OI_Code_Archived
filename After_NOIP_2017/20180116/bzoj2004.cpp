#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=2e2+1e2;
const int mod = 30031;
 
int len;
struct Matrix {
    int dat[maxn][maxn];
    Matrix(int x = 0) {
        memset(dat,0,sizeof(dat));
        if( x == 1 )
            for(int i=1;i<=len;i++)
                dat[i][i] = 1;
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=len;i++)
            for(int j=1;j<=len;j++)
                for(int k=1;k<=len;k++)
                    ret.dat[i][j] += a.dat[i][k] * b.dat[k][j] % mod ,
                    ret.dat[i][j] %= mod;
        return ret;
    }
    inline Matrix pow(int tme) {
        Matrix ret = Matrix(1) , now = *this;
        while( tme ) {
            if( tme & 1 ) ret = ret * now;
            now = now * now ;
            tme >>= 1;
        }
        return ret;
    }
}ans,trans;
 
 
int sta[maxn],tar;
 
 
inline int count(int x) {
    int ret = 0;
    while( x )
        ++ret , x -= ( x&-x );
    return ret;
}
inline int highbit(int x) {
    int ret = 1 << 10;
    while( ! ( x & ret ) )
        ret >>= 1;
    return ret;
}
inline bool judge(int from,int to) {
    from <<= 1;
    from -= highbit(from);
    return count( to ^ from ) == 1;
}
int main() {
    static int n,p,k,full;
    scanf("%d%d%d",&n,&k,&p);
    full = 1 << p;
    for(int i=0;i<full;i++)
        if( count(i) == k && (  i&(1<<(p-1))  ) ) {
            sta[++len] = i;
            if( i == full - ( 1 << ( p - k ) ) ) tar = len;
        }
    for(int i=1;i<=len;i++)
        for(int j=1;j<=len;j++)
            if( judge(sta[i],sta[j]) ) {
                trans.dat[i][j] = 1;
            }
    ans.dat[1][tar] = 1;
     
    ans = ans * trans.pow(n-k);
     
    printf("%d\n",ans.dat[1][tar]);
     
    return 0;
}