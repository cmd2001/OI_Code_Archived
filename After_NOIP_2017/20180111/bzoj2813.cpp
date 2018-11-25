#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=6e3+1e2,lim=1e9;

map<int,int> h;
lli f[maxn][20][10]; // f[multi][len][first]
int nums[maxn],cnt;

inline void init() {
    for(lli i=1;i<=lim;i*=2)
        for(lli j=i;j<=lim;j*=3)
            for(lli k=j;k<=lim;k*=5)
                for(lli l=k;l<=lim;l*=7)
                    nums[++cnt] = l;
    for(int i=1;i<=cnt;i++)
        h[nums[i]] = i,
        nums[i] = nums[i];
}

inline void gen() {
    for(int i=1;i<10;i++)
        f[h[i]][1][i] = 1;
    for(int len=1;len<19;len++)
        for(int mul=1;mul<=cnt;mul++)
            for(int first=1;first<10;first++) {
                if( !f[mul][len][first] ) continue;
                const lli now = nums[mul];
                for(int nxt=1;nxt<10;nxt++) {
                    const lli nm = now * nxt;
                    if( nm > lim ) continue;
                    f[h[nm]][len+1][nxt] += f[mul][len][first];
                }
            }
}

inline lli count(lli x,int mul) {
    static int bits[20],cnt,m;
    
    cnt = 0 , m = (bool) x;
    while( x )
        bits[++cnt] = x % 10 , x /= 10 , m *= bits[cnt];
    reverse(bits+1,bits+1+cnt);
    
    lli ret = 0;
    if( m == nums[mul] )
        ++ret;
    for(int i=1;i<cnt;i++)
        for(int j=1;j<10;j++)
            ret += f[mul][i][j];
    for(int i=1;i<=cnt;i++) {
        for(int j=1;j<bits[i];j++)
            ret += f[mul][cnt-i+1][j];
        if( !bits[i] ) break;
        int now = nums[mul];
        if( now % bits[i] ) break;
        mul = h[now/bits[i]];
    }
    
    return ret;
}

inline lli calc(lli x) {
    lli ret = 0;
    for(lli i=1;i<=cnt;i++)
        ret += count( x / nums[i] , i );
    return ret;
}

int main() {
    static lli a,b;
    init(); gen();
    
    scanf("%lld%lld",&a,&b);
    printf("%lld\n",calc(b)-calc(a-1));
    
    return 0;
}
