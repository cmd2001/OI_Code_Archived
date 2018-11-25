#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef unsigned long long int ulli;
typedef long double ldb;
using namespace std;
const int maxn=1e5+1e2,maxl=67;

ulli in[maxn];

struct LinearBase {
    ulli dat[maxn];
    const ulli& operator [] (const int &x) const { return dat[x]; }
    inline void insert(ulli x) {
        for(int i=63;~i;i--) if( x & ( 1ull << i ) ) {
            if( !dat[i] ) dat[i] = x;
            else return void( dat[i] = x );
        }
    }
}lb;

ldb ans;
int n,k,lim;

namespace One {
    inline void getans() {
        ulli t = 0;
        for(int i=1;i<=n;i++) t |= in[i];
        ans = t , ans /= 2.0;
    }
}
namespace Two {
    inline void getans() {
        ldb bit = 0;
        bool flag;
        for(int i=0;i<=lim;i++) for(int j=0;j<=lim;j++) {
            flag = 0; for(int k=1;k<=n;k++) if( in[k] & ( 1ull << i ) ) { flag = 1; break; }
            if( !flag ) continue;
            flag = 0; for(int k=1;k<=n;k++) if( in[k] & ( 1ull << j ) ) { flag = 1; break; }
            if( !flag ) continue;
            flag = 0; for(int k=1;k<=n;k++) if( ( ( in[k] >> i ) & 1 ) != ( ( in[k] >> j ) & 1 ) ) { flag = 1; break; }
            ans += 1ull << ( i + j - flag );
        }
        ans /= 2.0;
    }
}
namespace AboveOrEqualThree {
    ulli tp[maxl],ans,res,mask;
    int len;
    
    inline void fastpow(ulli t) {
        ulli high = t >> len , low = t & mask;
        for(int i=2;i<=k;i++) high *= t , low *= t , high += low >> len , low &= mask;
        ans += high , res += low , ans += res >> len , res &= mask;
    }
    inline void dfs(int pos,ulli cur) {
        if( pos > len ) return fastpow(cur);
        dfs(pos+1,cur) , dfs(pos+1,cur^tp[pos]);
    }
    inline void getans() {
        for(int i=0;i<64;i++) if( lb[i] ) tp[++len] = lb[i];
        mask = ( 1ull << len ) - 1 , dfs(1,0);
        printf("%llu",ans);
        if( ( res >> ( len - 1 ) ) & 1 ) puts(".5");
        else putchar('\n');
    }
}

int main() {
    static char out[1010];
    scanf("%d%d",&n,&k) , lim = 63 / k;
    for(int i=1;i<=n;i++) scanf("%llu",in+i) , lb.insert(in[i]);
    if( k == 1 ) One::getans();
    else if( k == 2 ) Two::getans();
    else AboveOrEqualThree::getans();
    if( k <= 2 ) {
        sprintf(out+1,"%0.1Lf",ans);
        int len = strlen(out+1);
        if(out[len] == '0') out[len--] = '\0' , out[len--] = '\0';
        puts(out+1);
    }
    return 0;
}
