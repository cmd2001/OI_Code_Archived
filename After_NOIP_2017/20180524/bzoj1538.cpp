#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int lim=1e2;

lli ans;
__inline lli calc(const lli &a,const lli &b,const lli &c) {
    return a * a + b * b + c * c + 7 * std::min(a,std::min(b,c));
}
__inline void chk(const lli &a,const lli &b,const lli &c) {
    ans = std::max( ans , calc(a,b,c) );
}

int main() {
    static int T,a,b,c,d;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d%d",&a,&b,&c,&d) , ans = 0;
        for(int i=0;i<=d&&i<=lim;i++) for(int j=0;j<=d-i&&j<=lim;j++) {
            const int k = d - i - j;
            chk(a+i,b+j,c+k) , chk(a+i,b+k,c+j) , chk(a+k,b+i,c+j);
        }
        chk(a+d,b,c) , chk(a,b+d,c) , chk(a,b,c+d) , printf("%lld\n",ans);
    }
    return 0;
}
