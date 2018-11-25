#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define bool unsigned char 
const int maxn=64000;

int p[maxn],l[maxn],r[maxn],sg[maxn],f[maxn],cnt,ps,n;
bool vis[maxn];

inline void pre() {
    for(int l=1,r;l<=n;l=r+1) p[++ps] = r = n / ( n / l );
    for(int i=ps,j;i;i--) {
        int t = 0 , mx = 0 , at = cnt;
        for(int rr=2,ll=2;ll<=n/p[i];ll=rr+1) {
            while(at&&ll*p[i]>r[at]) --at;
            if(at) rr = r[at] / p[i];
            vis[t^sg[at]] = 1 , mx = std::max( mx , t^sg[at] );
            if( ( rr - ll + 1 ) & 1 ) t ^= sg[at];
            vis[t] = 1 , mx = std::max( mx , t );
        }
        for(j=1;vis[j];j++) ;
        f[i] = sg[++cnt] = j;
        if( cnt > 1 && j == sg[cnt-1] ) l[--cnt] = p[i-1] + 1;
        else l[cnt] = p[i-1] + 1 , r[cnt] = p[i];
        memset(vis,0,sizeof(bool)*(mx+1));
    }
}

int main() {
    static int T,ans,siz,x;
    scanf("%d%d",&n,&T) , pre();
    while(T--) {
        scanf("%d",&siz) , ans = 0;
        while(siz--) {
            scanf("%d",&x);
            ans ^= f[std::lower_bound(p+1,p+1+ps,n/(n/x))-p];
        }
        puts(ans?"Yes":"No");
    }
    return 0;
}

