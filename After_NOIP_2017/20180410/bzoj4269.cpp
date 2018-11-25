#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=32;


struct LinearBase {
    int dat[maxn],sel[maxn];
    inline void insert(int x) {
        for(int i=30;~i;i--)
            if( x & ( 1 << i ) ) {
                if( dat[i] ) x ^= dat[i];
                else return void( dat[i] = x );
            }
    }
    inline int build() {
        int ret = 0;
        for(int i=30;~i;i--) if( ! ( ret & ( 1 << i ) ) ) ret ^= dat[i] , sel[i] = 1;
        return ret;
    }
    inline int sec(int mx) {
        int ret;
        for(int dif=0;dif<=30;dif++) {
            ret = 0;
            for(int i=30;i>dif;i--) if( sel[i] ) ret ^= dat[i];
            if( !sel[dif] ) ret ^= dat[dif];
            for(int i=dif-1;~i;i--) ret = max( ret , ret ^ dat[i] );
            if( ret < mx ) break;
        }
        return ret;
    }
}lb;

int main() {
    static int n,ans,sec,t;
    scanf("%d",&n);
    while(n--) scanf("%d",&t) , lb.insert(t);
    ans = lb.build() , sec = lb.sec(ans);
    printf("%d %d\n",ans,sec);
    return 0;
}
