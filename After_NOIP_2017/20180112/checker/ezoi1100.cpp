#include<bits/stdc++.h>
using namespace std;
const int maxl=1e3+1e2,maxn=255;

struct BigInt {
    int dat[maxl],len;
    BigInt() {
        memset(dat,0,sizeof(dat));
        len = 0;
    }
    BigInt operator = (int x) {
        while(x)
            dat[len++] = x % 10 ,
            x /= 10;
        return *this;
    }
    friend BigInt operator + (const BigInt &a,const BigInt &b) {
        BigInt ret;
        ret.len = max( a.len , b.len );
        for(int i=0;i<ret.len;i++)
            ret.dat[i] = a.dat[i] + b.dat[i];
        for(int i=0;i<ret.len;i++)
            ret.dat[i+1] += ret.dat[i] / 10 ,
            ret.dat[i] %= 10;
        while( ret.dat[ret.len] ) {
            ret.dat[ret.len+1] += ret.dat[ret.len] / 10 ,
            ret.dat[ret.len] %= 10;
            ++ret.len;
        }
        return ret;
    }
    inline void print() {
        if( !len )
            putchar('0');
        for(int i=len-1;~i;i--)
            putchar('0'+dat[i]);
        putchar('\n');
    }
}f[maxn];

int main() {
    static int n;
    f[0] = 1;
    scanf("%d",&n);
    for(int i=0;i<n;i++) {
        f[i+1] = f[i+1] + f[i];
        if( i+2 <= n )
            f[i+2] = f[i+2] + f[i],
            f[i+2] = f[i+2] + f[i];
    }
    f[n].print();
    
    return 0;
}