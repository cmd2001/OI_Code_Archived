#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],prmu[maxn],n,m,lst,cur;
lli ans;

struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= n + m + 1 ) dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bit;

inline int segment() { // cur is target , lst is included .
    if( cur < lst ) return bit.query(lst) - bit.query(cur);
    else return bit.query(cur-1) - bit.query(lst-1);
}
inline bool cmp(int x,int y) {
    return in[x] > in[y];
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d",in+i+n+1);
    reverse(in+1,in+1+n);
    for(int i=1;i<=n;i++) prmu[i] = i , bit.update(i,1);
    for(int i=1;i<=m;i++) prmu[i+n] = i + n + 1 , bit.update(i+n+1,1);
    sort(prmu+1,prmu+1+n+m,cmp) , lst = n + 1;
    for(int i=1;i<=n+m;i++) cur = prmu[i] , ans += segment() , bit.update(lst=cur,-1);
    printf("%lld\n",ans);
    return 0;
}

