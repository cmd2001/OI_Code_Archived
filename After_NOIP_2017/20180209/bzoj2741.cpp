#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1.2e4+1e2,maxd=maxn*33,maxb=120;

int in[maxn],pre[maxb][maxn];
int rt[maxn],*root;
int ch[maxd][2],siz[maxd],cnt;
int st[maxb],ed[maxb],bel[maxn],bc;
int n;
int m;

inline void insert(int pos,int pre,int len,int now) {
    memcpy(ch[pos],ch[pre],sizeof(ch[pre])) , siz[pos] = siz[pre] + 1;
    if( !~len ) return;
    int tar = ( now >> len  ) & 1;
    insert(ch[pos][tar]=++cnt,ch[pre][tar],len-1,now);
}
inline int query(int pos,int pre,int len,int now) {
    if( !len ) return 0;
    int tar = ( ( now >> ( len - 1 ) ) & 1 ) ^ 1;
    if( siz[ch[pos][tar]] - siz[ch[pre][tar]] )
        return query(ch[pos][tar],ch[pre][tar],len-1,now) + ( 1 << ( len - 1 ) );
    else return query(ch[pos][tar^1],ch[pre][tar^1],len-1,now);
}

inline int getans(int l,int r) {
    int ret = 0;
    if( bel[l] == bel[r] ) {
        for(int i=l,t;i<=r;i++)
            ret = max( ret , t = query(root[r],root[l-2],32,in[i]) );
    } else {
        int bl = bel[l];
        ret = pre[bl+1][r];
        for(int i=l-1;i<ed[bl];i++)
           ret = max( ret , query(root[r],root[l-2],32,in[i]) ); 
    }
    return ret;
}
inline void gen() {
    for(int i=1;i<=n;i++) in[i] ^= in[i-1];
    root = rt + 2;
    insert(root[-1]=++cnt,0,31,0);
    for(int i=0;i<=n;i++)
        insert(root[i]=++cnt,root[i-1],31,in[i]);
    for(int i=1;i<=bc;i++) {
        for(int j=st[i];j<=n;j++) {
            pre[i][j] = max( pre[i][j-1] , query(root[j],root[st[i]-2],32,in[j]) );
        }
    }
}
inline void init() {
    int bs = sqrt(n);
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + bs - 1 , n ) , ++bc;
        st[bc] = l , ed[bc] = r;
        for(int i=l;i<=r;i++) bel[i] = bc;
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    init() , gen();
    for(int i=1,ans=0,l,r;i<=m;i++) {
        scanf("%d%d",&l,&r) , l = ( (long long)l + ans ) % n + 1 , r = ( (long long)r + ans ) % n + 1;
        if( l > r ) swap(l,r);
        ans = getans(l,r);
        printf("%d\n",ans);
    }
    return 0;
}
