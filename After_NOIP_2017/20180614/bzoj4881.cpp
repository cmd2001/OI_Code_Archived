#include<cstdio>
#include<algorithm>
#include<set>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;
const int mod=998244353;

int in[maxn],n,ans;

struct ReversedBinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while(pos) dat[pos] = max( dat[pos] , x ) , pos -= lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos <= n ) ret = max( ret ,dat[pos] ) , pos += lowbit(pos);
        return ret;
    }
}bit;

set<int> st;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

int main() {
    scanf("%d",&n);
    for(int i=1,f;i<=n;i++) scanf("%d",in+i) , ans = max( ans , f = bit.query(in[i]) + 1 ) , bit.update(in[i],f);
    if( ans > 2 ) return puts("0") , 0;
    for(int i=1,tp,mx=in[i];i<=n;mx=in[++i]) {
        for(set<int>::iterator it=st.lower_bound(in[i]);it!=st.end();mx=max(mx,tp=*it),it++,st.erase(tp)) ;
        st.insert(mx);
    }
    printf("%lld\n",fastpow(2,st.size()));
    return 0;
}
