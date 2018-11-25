#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e5+1e2,maxe=6e6+1e2;

int root[maxn];
int lson[maxe],rson[maxe],dat[maxe],cnt;

inline void insert(int &pos,int pre,int l,int r,const int &tar,const int &val) {
    pos = ++cnt;
    if( l == r ) return void(dat[pos]=val);
    const int mid = ( l + r ) >> 1;
    if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar,val) , rson[pos] = rson[pre];
    else insert(rson[pos],rson[pre],mid+1,r,tar,val) , lson[pos] = lson[pre];
    dat[pos] = min( dat[lson[pos]] , dat[rson[pos]] );
}
inline int query(int pos,int l,int r,const int &lim) {
    if( !pos || l == r ) return l;
    const int mid = ( l + r ) >> 1;
    if( dat[lson[pos]] < lim ) return query(lson[pos],l,mid,lim);
    else return query(rson[pos],mid+1,r,lim);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1,t;i<=n;i++) scanf("%d",&t) , insert(root[i],root[i-1],0,n,min(t,n),i);
    for(int i=1,l,r;i<=m;i++) scanf("%d%d",&l,&r) , printf("%d\n",query(root[r],0,n,l));
    return 0;
}
