#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int maxn=55,maxm=4e3+1e2;

int lp[maxm],rp[maxm],vp[maxm],srt[maxm],len;
int f[maxn][maxn][maxm],fp[maxn][maxn][maxm],g[maxn][maxn][maxm],gv[maxn][maxn][maxm];
int h[maxn][maxm];
int ans[maxn];
int n,m,dep;

inline void dfs(int l,int r,int k) {
    if( l > r ) return;
    int miv = gv[l][r][k];
    if( !miv ) {
        for(int i=l;i<=r;i++)
            ans[i] = srt[len];
        return;
    }
    int mid = fp[l][r][miv];
    ans[mid] = srt[miv];
    dfs(l,mid-1,miv);
    dfs(mid+1,r,miv);
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    n = getint() , m = getint();
    for(int i=1;i<=m;i++)
        lp[i] = getint() , rp[i] = getint() , srt[i] = vp[i] = getint();
    
    sort(srt+1,srt+1+m);
    len = unique(srt+1,srt+1+m) - srt - 1;
    for(int i=1;i<=m;i++)
        vp[i] = lower_bound(srt+1,srt+1+len,vp[i]) - srt;
    
    for(int st=n;st;st--)
        for(int ed=st;ed<=n;ed++) {
            for(int i=st;i<=ed;i++) memset(h[i]+1,0,sizeof(int)*len);
            for(int i=1;i<=m;i++)
                if( st <= lp[i] && rp[i] <= ed )
                    for(int j=lp[i];j<=rp[i];j++)
                        ++h[j][vp[i]];
            for(int i=st;i<=ed;i++)
                for(int j=len;j;j--)
                    h[i][j] += h[i][j+1];
            for(int miv=m;miv;miv--) {
                for(int mid=st;mid<=ed;mid++) {
                    const int t = g[st][mid-1][miv] + g[mid+1][ed][miv] + h[mid][miv] * srt[miv];
                    if( t > f[st][ed][miv] ) {
                        f[st][ed][miv] = t;
                        fp[st][ed][miv] = mid;
                    }
                }
                g[st][ed][miv] = g[st][ed][miv+1] , gv[st][ed][miv] = gv[st][ed][miv+1];
                if( f[st][ed][miv] > g[st][ed][miv] ) {
                    g[st][ed][miv] = f[st][ed][miv] , gv[st][ed][miv] = miv;
                }
            }
        }
    
    dfs(1,n,1);
    printf("%d\n",g[1][n][1]);
    for(int i=1;i<=n;i++)
        printf("%d%c",ans[i],i!=n?' ':'\n');
    return 0;
}