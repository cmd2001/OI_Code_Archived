#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e5+2,maxb=318;

int in[maxn],bel[maxn],st[maxb],ed[maxb];
int sum[maxb][maxn],pre[maxb][maxb];
int app[maxn];
int n,c,m,blk,cnt,ans;

inline void gen() {
    blk = sqrt(n);
    //debug<<"blk = "<<blk<<endl;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + blk - 1 , n );
        st[++cnt] = l , ed[cnt] = r;
        for(int i=l;i<=r;i++)
            bel[i] = cnt;
    }
    for(int i=1;i<=cnt;i++) {
        memcpy(sum[i],sum[i-1],sizeof(sum[i]));
        for(int j=st[i];j<=ed[i];j++)
                ++sum[i][in[j]];
    }
    for(int i=1;i<=cnt;i++) {
        memset(app,0,sizeof(app));
        ans = 0;
        for(int j=st[i];j<=n;j++) {
            if( app[in[j]] ) {
                ++app[in[j]];
                if( ! ( app[in[j]] & 1 ) )
                    ++ans;
                else --ans;
            }
            else
                ++app[in[j]];
            if( bel[j+1] != bel[j] )
                pre[i][bel[j]] = ans;
        }
    }
    memset(app,0,sizeof(app));
    ans = 0;
}

inline int f(int in,int as,int ms) {
    return app[in] + sum[as][in] - sum[ms][in];
}

inline void update(int blk,int l,int r,int as,int ms) {
    /*debug<<"as = "<<as<<"ms = "<<ms<<endl;
    debug<<"sum1 = "<<sum[as][1] - sum[ms][1]<<endl;*/
    for(int i=max(st[blk],l);i<=min(ed[blk],r);i++) {
        if( f(in[i],as,ms) ) {
            //debug<<"i = "<<i<<"in = "<<in[i]<<endl;
            ++app[in[i]];
            if( ! ( f(in[i],as,ms) & 1 ) )
                ++ans;
            else --ans;
        }
        else
            ++app[in[i]];
    }
}
inline void reset(int blk,int l,int r) {
    for(int i=max(st[blk],l);i<=min(ed[blk],r);i++)
        app[in[i]] = 0;
}
inline void query(int l,int r) {
    ans = 0;
    if( bel[l] == bel[r] ) {
        update(bel[l],l,r,0,0);
        reset(bel[l],l,r);
    }
    else if( bel[l] + 1 == bel[r] ) {
        update(bel[l],l,r,0,0);
        update(bel[r],l,r,0,0);
        reset(bel[l],l,r);
        reset(bel[r],l,r);
    }
    else {
        ans = pre[bel[l]+1][bel[r]-1];
        update(bel[l],l,r,bel[r]-1,bel[l]);
        update(bel[r],l,r,bel[r]-1,bel[l]);
        reset(bel[l],l,r);
        reset(bel[r],l,r);
    }
}

int main() {
    freopen("dat.txt","r",stdin);
    freopen("my.txt","w",stdout);
    scanf("%d%d%d",&n,&c,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    
    gen();
    
    for(int i=1,l,r;i<=m;i++) {
        scanf("%d%d",&l,&r);
        l = ( l + ans ) % n + 1 , r = ( r + ans ) % n + 1;
        if( l > r )
            swap(l,r);
        //debug<<"l = "<<l<<"r = "<<r<<endl;
        query(l,r);
        printf("%d\n",ans);
        //break;
    }
    
    return 0;
}