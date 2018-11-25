#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
typedef long long int lli;
const int maxn=1e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll/3;

int a[maxn],b[maxn],n;
lli f[maxn];

inline int calc(int i,int j) {
    return a[i] == b[j] ? inf : std::abs(a[i]-b[j]);
}
inline void chk(lli &dst,const lli &val) {
    dst = std::min(dst,val);
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",a+i,b+i);
    if( n == 1 && a[1] == b[1] ) return puts("-1"),0;
    std::sort(a+1,a+1+n) , std::sort(b+1,b+1+n) , memset(f,0x3f,sizeof(f)) , *f = 0;
    for(int i=1;i<=n;i++) {
        if( i >= 1 ) chk(f[i],f[i-1]+calc(i,i));
        if( i >= 2 ) chk(f[i],f[i-2]+calc(i,i-1)+calc(i-1,i));
        if( i >= 3 ) chk(f[i],f[i-3]+calc(i,i-1)+calc(i-1,i-2)+calc(i-2,i)) , chk(f[i],f[i-3]+calc(i,i-2)+calc(i-1,i)+calc(i-2,i-1));
    }
    printf("%lld\n",f[n]);
    return 0;
}
