#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1.2e6+1e2;

struct Heap {
    int lson[maxn],rson[maxn],mxd[maxn],cnt;
    lli dat[maxn];
    inline int merge(int x,int y) {
        if( !x || !y ) return x | y;
        if( dat[x] < dat[y] ) std::swap(x,y);
        rson[x] = merge(rson[x],y);
        if( mxd[lson[x]] < mxd[rson[x]] ) std::swap(lson[x],rson[x]);
        return mxd[x] = mxd[rson[x]] + 1 , x;
    }
    inline lli top(const int &x) {
        return dat[x];
    }
    inline void pop(int &x) {
        x = merge(lson[x],rson[x]);
    }
    inline void push(int &x,const lli &d) {
        dat[++cnt] = d , x = merge(x,cnt);
    }
}h;

lli in[maxn],su;
int fa[maxn],d[maxn],root[maxn],n,m;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n+m;i++) scanf("%d%lld",fa+i,in+i) , ++d[fa[i]] , su += in[i];
    for(int i=n+m;i>1;i--) {
        lli l = 0 , r = 0;
        if(i <= n) {
            while(--d[i]) h.pop(root[i]);
            r = h.top(root[i]) , h.pop(root[i]) ,
            l = h.top(root[i]) , h.pop(root[i]) ;
        }
        h.push(root[i],l+in[i]) , h.push(root[i],r+in[i]) , root[fa[i]] = h.merge(root[fa[i]],root[i]);
    }
    while(d[1]--) h.pop(root[1]);
    while(root[1]) su -= h.top(root[1]) , h.pop(root[1]);
    return printf("%lld\n",su) , 0;
}
