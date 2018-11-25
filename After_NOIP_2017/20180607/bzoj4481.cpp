#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
typedef long double ldb;
const int maxn=5e5+1e2;

int n;
ldb ans;

struct BinaryIndexTree {
    ldb dat[maxn];
    #define lowbit(x) (x&-x)
    inline void update(int pos,const ldb &x) {
        while(pos) dat[pos] += x , pos -= lowbit(pos);
    }
    inline ldb query(int pos) {
        ldb ret = 0;
        while( pos <= n ) ret += dat[pos] , pos += lowbit(pos);
        return ret;
    }
}bit;

vector<int> in[maxn];
ldb pows[maxn],p,rev;

inline void apply(const vector<int> &v) {
    const ldb su = 1 / ( 1 - pows[v.size()] );
    for(unsigned i=0;i<v.size();i++) bit.update(v[i],pows[i]*su*p);
}
inline void query(const vector<int> &v) {
    const ldb su = 1 / ( 1 - pows[v.size()] );
    for(unsigned i=0;i<v.size();i++) ans += pows[i] * su * p * bit.query(v[i]+1);
}

int main() {
    static int m;
    scanf("%d%d%Lf",&n,&m,&p) , rev = 1 - p , *pows = 1;
    for(int i=1;i<=n;i++) pows[i] = pows[i-1] * rev;
    for(int i=1,a,b;i<=m;i++) scanf("%d%d",&a,&b) , in[a].push_back(b);
    for(int i=1;i<=n;i++) if( in[i].size() ) sort(in[i].begin(),in[i].end()) , query(in[i]) , apply(in[i]);
    printf("%0.2Lf\n",ans);
    return 0;
}
