#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],n,m;

struct BinaryIndexTree {
    lli dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,const lli &x) {
        while( pos <= n ) dat[pos] += x , pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bit,su;

int main() {
    static char o[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , bit.update(i,(lli)(n-i+1)*in[i]) , su.update(i,in[i]);
    for(int i=1,x;i<=m;i++) {
        scanf("%s%d",o,&x);
        if( *o == 'Q' ) printf("%lld\n",bit.query(x)-(n-x)*su.query(x));
        else bit.update(x,(lli)(n-x+1)*-in[x]) , su.update(x,-in[x]) , scanf("%d",in+x) , bit.update(x,(lli)(n-x+1)*in[x]) , su.update(x,in[x]);
    }
    return 0;
}
