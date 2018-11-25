#include<cstdio>
#include<algorithm>
typedef long long int lli;
using namespace std;
const int maxn=(1<<13)+10,maxl=16;

int in[maxn],bin[maxl];
lli fac[maxl],ans;
int n;

inline void swap(int* a,int* b,int len) {
    for(int i=0;i<len;i++) swap(a[i],b[i]);
}
inline bool judge(int* a,int len) {
    for(int i=1;i<len;i++) if( a[i] != a[i-1] + 1 ) return 0;
    return 1;
}
inline void dfs(int dep,int sel) {
    if( dep == n ) return void(ans+=fac[sel]);
    const int p = dep + 1;
    int *sa=0,*sb=0;
    for(int i=0;i<bin[n]/bin[p];i++) if( !judge(in+i*bin[p],bin[p]) ) {
        if( !sa ) sa = in+i*bin[p];
        else if( !sb ) sb = in+i*bin[p];
        else return; // No solution .
    }
    if( !sa && !sb ) return dfs(dep+1,sel);
    if( !sb ) {
        swap(sa,sa+bin[dep],bin[dep]);
        dfs(dep+1,sel+1);
        swap(sa,sa+bin[dep],bin[dep]);
    } else {
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) {
            swap(sa+i*bin[dep],sb+j*bin[dep],bin[dep]);
            if( judge(sa,bin[p]) && judge(sb,bin[p]) ) dfs(dep+1,sel+1);
            swap(sa+i*bin[dep],sb+j*bin[dep],bin[dep]);
        }
    }
}

int main() {
    scanf("%d",&n) , *fac = *bin = 1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i , bin[i] = bin[i-1] << 1;
    for(int i=0;i<bin[n];i++) scanf("%d",in+i);
    dfs(0,0) , printf("%lld\n",ans);
    return 0;
}