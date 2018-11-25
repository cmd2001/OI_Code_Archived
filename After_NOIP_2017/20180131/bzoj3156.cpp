#include<cstdio>
#define lli long long int
using namespace std;
const int maxn=1e6+1e2;

lli f[maxn],in[maxn];
int que[maxn],st,ed;

inline double g(lli j) {
    return 2 * f[j] + j * j + j;
}
inline double slop(int k,int j) { // assert k < j 
    return ( g(j) - g(k) ) / ( j - k );
}
inline lli calcf(lli i,lli j) {
    return in[i] + f[j] + ( ( i - j ) * ( i - j - 1 ) >> 1 );
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    que[st=ed] = 0;
    for(int i=1;i<=n;i++) {
        while( st < ed && slop(que[st],que[st+1]) < 2 * i )++st;
        f[i] = calcf(i,que[st]);
        while( st < ed && slop(que[ed-1],que[ed]) > slop(que[ed],i) ) --ed;
        que[++ed] = i;
    }
    
    printf("%lld\n",f[n]);
    
    return 0;
}
