#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<bitset>
#define bool unsigned char
typedef long long int lli;
#define debug cout
using namespace std;
const int maxn=1e7+1e2,lim=1e7;
const int mod=1e9+9;

namespace IO {
    const int BS = 1 << 21;
    char ibuf[BS],obuf[BS],*ist,*ied,*oed=obuf;
    inline char nextchar() {
        if( ist == ied ) ied = ibuf + fread(ist=ibuf,1,BS,stdin);
        return ist == ied ? -1 : *ist++;
    }
    inline int getint() {
        int ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
    inline lli getlli() {
        lli ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
    inline void flsh() {
        fwrite(obuf,1,oed-obuf,stdout) , oed = obuf;
    }
    inline void printchar(const char &x) {
        *oed++ = x;
        if( oed == obuf + BS ) flsh();
    }
    inline void printlli(lli x) {
        static int stk[30],top;
        if( !x ) printchar('0');
        else {
            top = 0;
            while(x) stk[++top] = x % 10 , x /= 10;
            while(top) printchar('0'+stk[top--]);
        }
        printchar('\n');
    }
}
using IO::getint; using IO::getlli;
using IO::printlli;

namespace SubTask1 {
    int phi[maxn];
    inline void sieve() {
        static int prime[maxn/10],cnt;
        static bool vis[maxn];
        phi[1] = 1;
        for(int i=2;i<=lim;i++) {
            if( !vis[i] ) prime[++cnt] = i , phi[i] = i - 1;
            for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
                const int tar = i * prime[j];
                vis[tar] = 1;
                if( i % prime[j] ) phi[tar] = phi[i] * ( prime[j] - 1 );
                else {
                    phi[tar] = phi[i] * prime[j];
                    break;
                }
            }
        }
        for(int i=1;i<=lim;i++) phi[i] = (lli) phi[i] * i % mod;
    }
    inline lli calc(lli n,lli m) {
        return (lli) phi[n] * phi[m] % mod;
    }
}
namespace SubTask2 {
    inline lli force_phi(lli n) {
        lli ret = n;
        for(lli i=2;i*i<=n;i++) {
            if( ! ( n % i ) ) {
                ( ret /= i ) *= i - 1;
                while( ! ( n % i ) ) n /= i;
            }
        }
        if( n != 1 ) ( ret /= n ) *= n - 1;
        return ret % mod;
    }
    inline lli calc(lli n,lli m) {
        return force_phi(n) * force_phi(m) % mod * ( n % mod ) % mod * ( m % mod ) % mod;
    }
}



int main() {
    static int T,n,m;
    static lli n2,m2;
    T = getint();
    if(T==1) {
        n2 = getlli() , m2 = getlli();
        printlli(SubTask2::calc(n2,m2));
    } else {
        SubTask1::sieve();
        while(T--) {
            n = getint() , m = getint();
            printlli(SubTask1::calc(n,m));
        }
    }
    IO::flsh();
    return 0;
}