#include<cstdio>
typedef long long int lli;

lli pows[21]; // pows of 10 .
lli f[21][13][15][2]; // f[length][first][mod 13][have 13]

inline void pre() {
    *pows = 1;
    for(int i=1;i<=17;i++) pows[i] = pows[i-1] * 10;
    f[0][0][0][0] = 1;
    for(int length=1;length<=17;length++) {
        for(int first=0;first<10;first++)
            for(int last=0;last<10;last++)
                for(int mod=0;mod<13;mod++)
                    for(int had=0;had<2;had++) {
                        int nmod = ( first * pows[length-1] + mod ) % 13 , nhad = had | ( first == 1 && last == 3 );
                        f[length][first][nmod][nhad] += f[length-1][last][mod][had];
                    }
    }
}
inline lli count(lli x) {
    static int bit[65],cnt,tarsu,app;
    while(x) bit[++cnt] = x % 10 , x /= 10;
    lli ret = 0;
    for(int length=1;length<cnt;length++) for(int first=1;first<10;first++) ret += f[length][first][0][1];
    for(int sme=cnt;sme;sme--) {
        for(int first=(sme==cnt);first<bit[sme];first++) {
            ret += f[sme][first][tarsu][1];
            if( app || ( sme != cnt && bit[sme+1] == 1 && first == 3 ) ) ret += f[sme][first][tarsu][0];
        }
        tarsu = ( tarsu - bit[sme] * pows[sme-1] % 13 + 13 ) % 13;
        if( sme != cnt && bit[sme+1] == 1 && bit[sme] == 3 ) app = 1;
    }
    return ret;
}

int main() {
    static lli n;
    scanf("%lld",&n) , ++n , pre() , printf("%lld\n",count(n));
    return 0;
}
