#include<cstdio>
typedef long long lli;
const int maxb=70,lim=60;
const int mod=10000007;

lli f[maxb][maxb][2]; // f[count][length][firstbit] .
int bin[maxb],len;

inline lli fastpow(lli base,lli tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

inline void pre() {
    f[0][1][0] = 1 , f[1][1][1] = 1;
    for(int length=2;length<=lim;length++)
        for(int count=0;count<=lim;count++) {
            f[count][length][0] = f[count][length-1][0] + f[count][length-1][1];
            if( count ) f[count][length][1] = f[count-1][length-1][0] + f[count-1][length-1][1];
        }
}

inline lli count(int bit) {
    lli ret = 0;
    for(int i=1;i<len;i++) ret += f[bit][i][1];
    for(int i=len;i&&bit>=0;i--) { // this is same bit .
        if( bin[i] && i != len ) ret += f[bit][i][0];
        if( bin[i] ) --bit;
    }
    return ret;
}

inline void getbin(lli t) {
    while(t) bin[++len] = t & 1 ,t >>= 1;
}

signed main() {
    static lli n,ans=1;
    pre() , scanf("%lld",&n);
    getbin(++n);
    for(int i=1;i<=len;i++) ans = ans * fastpow(i,count(i)) % mod;
    printf("%lld\n",ans);
    return 0;
}
