#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxe=30,maxn=1<<14;

bool ans[maxe][maxn];
int in[maxe][maxn],Log[maxn];
int lim[maxn],app[maxn],rapp[maxn];
int n,nod_n,nod_m,data_m;

inline int shl(int x,int l) { // looping bit left move .
    int ret = 0;
    for(int i=0;i<l;i++) if( x & ( 1 << i ) ) ret |= 1 << ( ( i - 1 + l ) % l );
    return ret;
}
inline int shr(int x,int l) { // looping bit right move .
    int ret = 0;
    for(int i=0;i<l;i++) if( x & ( 1 << i ) ) ret |= 1 << ( ( i + 1 ) % l );
    return ret;
}

inline void dfs(int inlev,int outlev,int cur,int pos) { // cur = 0 or 1 means up or down .
    int oth = pos ^ 1;
    if( !cur ) { // solve by inklev .
        if( !~lim[in[inlev][oth]] ) lim[in[inlev][oth]] = lim[in[inlev][pos]] ^ 1 , dfs(inlev,outlev,0,oth);
        int op = app[in[inlev][pos]] , oop = op ^ 1;
        if( !~lim[in[outlev][oop]] ) lim[in[outlev][oop]] = lim[in[outlev][op]] ^ 1 , dfs(inlev,outlev,1,oop);
    } else {
        if( !~lim[in[outlev][oth]] ) lim[in[outlev][oth]] = lim[in[outlev][pos]] ^ 1 , dfs(inlev,outlev,1,oth);
        int op = rapp[in[outlev][pos]] , oop = op ^ 1;
        if( !~lim[in[inlev][oop]] ) lim[in[inlev][oop]] = lim[in[inlev][op]] ^ 1 , dfs(inlev,outlev,0,oop);
    }
}
inline void solve(int sx,int sy,int tx,int inlev,int outlev,int n) { // n is count of points , n >> 1 is count of nodes , sx and sy are position of nodes .
    if( n == 2 ) {
        if( in[inlev][sy<<1] != in[outlev][sy<<1] ) ans[sx][sy] = 1;
        return;
    }
    
    for(int i=0;i<n;i++) lim[in[inlev][(sy<<1)+i]] = -1;
    for(int i=0;i<n;i++) app[in[outlev][(sy<<1)+i]] = (sy<<1)+i , rapp[in[inlev][(sy<<1)+i]] = (sy<<1)+i;
    const int mid = ( sy << 1 ) + ( n >> 1 ) - 1;
    
    for(int i=0;i<n>>1;i++) {
        int l = (sy<<1) + (i<<1) , r = (sy<<1) + (i<<1|1) , tl = (sy<<1) + shl(i<<1,Log[n]) , tr = (sy<<1) + shl(i<<1|1,Log[n]);
        if( !~lim[in[inlev][l]] && !~lim[in[inlev][r]] ) lim[in[inlev][l]] = tl > mid , lim[in[inlev][r]] = tr > mid; // left 0 , right 1 .
        else { // solve limit .
            if( ~lim[in[inlev][l]] ) lim[in[inlev][r]] = lim[in[inlev][l]] ^ 1;
            else lim[in[inlev][l]] = lim[in[inlev][r]] ^ 1;
            ans[sx][sy+i] = ( tl > mid ) ^ lim[in[inlev][l]];
        }
        dfs(inlev,outlev,0,l) , dfs(inlev,outlev,0,r);
        
        int pl = app[in[inlev][l]] , bpl = ( pl - (sy<<1) ) >> 1 , bpl_l = (sy<<1) + (bpl<<1) , bpl_l_tarsou = (sy<<1) + shl(bpl<<1,Log[n]);
        ans[tx][sy+bpl] = ( bpl_l_tarsou > mid ) ^ lim[in[outlev][bpl_l]];
        
        int pr = app[in[inlev][r]] , bpr = ( pr - (sy<<1) ) >> 1 , bpr_l = (sy<<1) + (bpr<<1) , bpr_l_tarsou = (sy<<1) + shl(bpr<<1,Log[n]);
        ans[tx][sy+bpr] = ( bpr_l_tarsou > mid ) ^ lim[in[outlev][bpr_l]];
        
    }
    
    for(int i=0;i<n>>1;i++) { // trans data to next level .
        int l = (sy<<1) + (i<<1) , r = (sy<<1) + (i<<1|1) , tl = (sy<<1) + shl(i<<1,Log[n]) , tr = (sy<<1) + shl(i<<1|1,Log[n]);
        in[inlev+1][tl] = in[inlev][l] , in[inlev+1][tr] = in[inlev][r];
        if(ans[sx][sy+i]) swap(in[inlev+1][tl],in[inlev+1][tr]);
    }
    for(int i=0;i<n>>1;i++) { // trans data to previous level .
        int l = (sy<<1) + (i<<1) , r = (sy<<1) + (i<<1|1) , fl = (sy<<1) + shl(i<<1,Log[n]) , fr = (sy<<1) + shl(i<<1|1,Log[n]);
        in[outlev-1][fl] = in[outlev][l] , in[outlev-1][fr] = in[outlev][r];
        if(ans[tx][sy+i]) swap(in[outlev-1][fl],in[outlev-1][fr]);
    }
    
    solve(sx+1,sy,tx-1,inlev+1,outlev-1,n>>1) , solve(sx+1,sy+(n>>2),tx-1,inlev+1,outlev-1,n>>1);
}

inline void reset() {
    memset(ans,0,sizeof(ans));
}

int main() {
    while( scanf("%d",&n) == 1 && n ) {
        reset() , nod_n = ( n << 1 ) - 1 , nod_m = 1 << ( n - 1 ) , data_m = 1 << n;
        for(int i=0;i<=n;i++) Log[1<<i] = i;
        for(int i=0;i<data_m;i++) in[0][i] = i , scanf("%d",in[nod_n]+i);
        solve(0,0,nod_n-1,0,nod_n,data_m);
        for(int i=0;i<nod_n;i++) {
            for(int j=0;j<nod_m;j++) putchar('0'+ans[i][j]);
            putchar('\n');
        }
        putchar('\n');
    }
    return 0;
}

