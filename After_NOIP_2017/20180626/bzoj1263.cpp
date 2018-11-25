#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=5e3+1e2;

struct bigInt {
    int dat[maxn],len;
    bigInt(int x=0) {
        while(x) dat[len++] = x % 10 , x /= 10;
    }
    bigInt operator *= (const int &x) {
        for(int i=0;i<len;i++) dat[i] *= x;
        for(int i=0;i<len;i++) dat[i+1] += dat[i] / 10 , dat[i] %= 10;
        while(dat[len]) dat[len+1] += dat[len] / 10 , dat[len++] %= 10;
        return *this;
    }
    inline void print() {
        printf("%d\n",len);
        if( len <= 100 ) for(int i=len-1;~i;i--) putchar('0'+dat[i]);
        else for(int i=len-1;i>=len-100;i--) putchar('0'+dat[i]);
        putchar('\n');
    }
}ans(1);

int main() {
    static int n,ps;
    scanf("%d",&n) , ps = n / 3;
    if( n % 3 == 2 ) ans *= 2;
    else if( n % 3 == 1 ) --ps , ans *= 4;
    while( ps-- ) ans *= 3;
    ans.print();
    return 0;
}
