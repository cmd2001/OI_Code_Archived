#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+1e2;
const int mod=998244353;

int in[maxn],lst[5],f[maxn];
int n,k,m;

inline void adde(int &dst,int x) {
    dst += x;
    if( dst >= mod ) dst -= mod;
}
inline int getf(int st,int ed) {
    memset(lst,0,sizeof(lst));
    for(int i=ed;i>=st;i--) {
        f[i] = 1;
        for(int j=0;j<k;j++) adde(f[i],f[lst[j]]);
        lst[in[i]] = i;
    }
    int ret = 0;
    for(int j=0;j<k;j++) adde(ret,f[lst[j]]);
    return ret;
}
inline void addall(int st,int ed,int x) {
    for(int i=st;i<=ed;i++) in[i] = ( in[i] + x ) % k;
}
inline void mulall(int st,int ed,int x) {
    for(int i=st;i<=ed;i++) in[i] = in[i] * x% k;
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d",&n,&k,&m);
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        for(int i=1,o,l,r,x;i<=m;i++) {
            scanf("%d%d%d",&o,&l,&r);
            if( o == 1 ) scanf("%d",&x) , addall(l,r,x);
            else if( o == 2 ) scanf("%d",&x) , mulall(l,r,x);
            else if( o == 3 ) printf("%d\n",getf(l,r));
        }
    }
    return 0;
}
