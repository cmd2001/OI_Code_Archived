#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;
const int maxn=2e3+1e2;
const double pi = acos(-1.0);
typedef pair<double,double> pii;

namespace LIS {
    double in[maxn],f[maxn];
    int n,len;
    inline int work() {
        f[len=1] = in[1];
        for(int i=2;i<=n;i++) {
            if( in[i] > f[len] ) f[++len] = in[i];
            else f[upper_bound(f+1,f+1+len,in[i])-f] = in[i]; 
        }
        return len;
    }
}

int x[maxn],y[maxn];
pii seg[maxn];
int n,r,ans;

int main() {
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i);
    for(int i=1;i<=n;i++) {
        double dis = sqrt(x[i]*x[i]+y[i]*y[i]) , cur = atan2(y[i],x[i]) , deg = acos(r/dis);
        double l = cur - deg , r = cur + deg;
        while( l < -pi ) l += 2.0 * pi;
        while( r > pi ) r -= 2.0 * pi;
        if( l > r ) swap(l,r);
        seg[i] = (pii){l,r};
    }
    sort(seg+1,seg+1+n);
    for(int i=1;i<=n;i++) {
        LIS::n = 0;
        for(int j=i+1;j<=n;j++)
            if( seg[j].first < seg[i].second && seg[i].second < seg[j].second )
                LIS::in[++LIS::n] = seg[j].second;
        ans = max( ans , LIS::work() + 1 );
    }
    printf("%d\n",ans);
    return 0;
}
