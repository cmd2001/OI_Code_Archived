#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxb=320;
typedef pair<lli,int> pir;

int in[maxn];
int sumgcd[maxn];
lli sumxor[maxn];
int st[maxb],ed[maxb],bel[maxn],cnt;
pir xors[maxn];
int n;

inline int gcd(int x,int y) {
    if( !x || !y ) return x | y;
    int t;
    while( ( t = x % y ) )
        x = y , y = t;
    return y;
}
inline void rebuild(int id) {
    sumgcd[st[id]] = sumxor[st[id]] = in[st[id]];
    for(int i=st[id]+1;i<=ed[id];i++)
        sumgcd[i] = gcd(sumgcd[i-1],in[i]) ,
        sumxor[i] = sumxor[i-1] ^ in[i];
    for(int i=st[id];i<=ed[id];i++)
        xors[i] = make_pair((lli)sumxor[i],i);
    sort(xors+st[id],xors+ed[id]+1);
}
inline int queryxor(int id,lli tar) {
    int pos = lower_bound(xors+st[id],xors+ed[id]+1,make_pair(tar,0)) - xors;
    if( xors[pos].first == tar ) return xors[pos].second;
    return -1;
}
inline int query(lli tar) {
    int lastgcd = sumgcd[1];
    lli lastxor = 0;
    for(int i=1;i<=cnt;i++) {
        if( gcd(lastgcd,sumgcd[ed[i]]) == lastgcd ) {
            if( ! ( tar % lastgcd)  ) {
                int qx = queryxor(i,(tar/lastgcd)^lastxor);
                if( ~qx ) return qx;
            }
            lastxor ^= sumxor[ed[i]];
        } else {
            for(int j=st[i];j<=ed[i];j++) {
                lastgcd = gcd(lastgcd,in[j]) , lastxor ^= in[j];
                if( lastgcd * lastxor == tar ) return j;
            }
        }
    }
    return -1;
}
inline void initblk() {
    int bs = sqrt(n);
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + bs - 1 , n ) , ++cnt;
        st[cnt] = l , ed[cnt] = r;
        for(int i=l;i<=r;i++) bel[i] = cnt;
    }
}
inline void init() {
    initblk();
    for(int i=1;i<=cnt;i++) rebuild(i);
}

int main() {
    static int m;
    static char o[10];
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    init();
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        scanf("%s",o);
        if( *o == 'M' ) {
            int x;
            scanf("%d",&x) , ++x , scanf("%d",in+x);
            rebuild(bel[x]);
        } else {
            lli tar;
            scanf("%lld",&tar);
            int ans = query(tar);
            if( !~ans ) puts("no");
            else printf("%d\n",ans-1);
        }
    }
    return 0;
}
