#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=2e4+1e2,maxm=2e6+1e2;

struct QNode {
    int sum,mx;
};
int l[maxm],r[maxm],lson[maxm],rson[maxm],sum[maxm],mxl[maxm],mxr[maxm],cnt;
int in[maxn],srt[maxn],len,root[maxn];
vector<int> at[maxn];
int n;

inline void prebuild(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr ,
    sum[pos] = mxl[pos] = mxr[pos] = ( rr - ll + 1 );
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    prebuild(lson[pos]=++cnt,ll,mid) , prebuild(rson[pos]=++cnt,mid+1,rr);
}
inline void update(int pos,int pre,int tar) {
    l[pos] = l[pre] , r[pos] = r[pre] ,
    lson[pos] = lson[pre] , rson[pos] = rson[pre];
    if( l[pos] == r[pos] ) {
        sum[pos] = mxl[pos] = mxr[pos] = -1;
        return;
    }
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( tar <= mid ) update(lson[pos]=++cnt,lson[pre],tar);
    else update(rson[pos]=++cnt,rson[pre],tar);
    sum[pos] = sum[lson[pos]] + sum[rson[pos]] ,
    mxl[pos] = max( mxl[lson[pos]] , sum[lson[pos]] + mxl[rson[pos]] ) ,
    mxr[pos] = max( mxr[rson[pos]] , sum[rson[pos]] + mxr[lson[pos]] ) ;
}
inline int querysum(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return 0;
    if( ll <= l[pos] && r[pos] <= rr ) return sum[pos];
    return querysum(lson[pos],ll,rr) + querysum(rson[pos],ll,rr);
}
inline QNode queryr(int pos,int ll,int rr) { // ret.sum includes sum from ll to rr in range of pos.
    if( ll <= l[pos] && r[pos] <= rr ) return (QNode){sum[pos],max(mxr[pos],0)};
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) return queryr(lson[pos],ll,rr);
    else if( ll > mid ) return queryr(rson[pos],ll,rr);
    QNode ql = queryr(lson[pos],ll,rr) , qr = queryr(rson[pos],ll,rr) , ret;
    ret.mx = max( qr.mx , qr.sum + ql.mx ) , ret.mx = max( ret.mx , 0 );
    ret.sum = ql.sum + qr.sum;
    return ret;
}
inline QNode queryl(int pos,int ll,int rr) { // same meaning as queryr
    if( ll <= l[pos] && r[pos] <= rr ) return (QNode){sum[pos],max(mxl[pos],0)};
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mid ) return queryl(lson[pos],ll,rr);
    else if( ll > mid ) return queryl(rson[pos],ll,rr);
    QNode ql = queryl(lson[pos],ll,rr) , qr = queryl(rson[pos],ll,rr) , ret;
    ret.mx = max( ql.mx , ql.sum + qr.mx ) , ret.mx = max( ret.mx , 0 );
    ret.sum = ql.sum + qr.sum;
    return ret;
}
inline bool judge(int root,int stl,int edl,int str,int edr) {
    int sum = querysum(root,edl,str);
    if( stl < edl ) {
        QNode ql = queryr(root,stl,edl-1);
        sum += ql.mx;
    }
    if( str < edr ) {
        QNode qr = queryl(root,str+1,edr);
        sum += qr.mx;
    }
    return sum >= 0;
}
inline int bin(int stl,int edl,int str,int edr) {
    int ll = 1 , rr = len + 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( judge(root[mid-1],stl,edl,str,edr) ) ll = mid;
        else rr = mid;
    }
    return ll;
}
inline void pre() {
    memcpy(srt+1,in+1,sizeof(int)*n);
    sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) {
        in[i] = lower_bound(srt+1,srt+1+len,in[i]) - srt;
        at[in[i]].push_back(i);
    }
    prebuild(root[0]=++cnt,1,n);
    for(int i=0;i<len;i++) {
        root[i+1] = root[i];
        for(unsigned j=0;j<at[i+1].size();j++) {
            int m = root[i+1];
            update(root[i+1]=++cnt,m,at[i+1][j]);
        }
    }
}

int main() {
    static int m,q[10],last;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    pre();
    scanf("%d",&m);
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=4;j++) scanf("%d",q+j) , q[j] = ( q[j] + last ) % n + 1;
        sort(q+1,q+5);
        last = bin(q[1],q[2],q[3],q[4]);
        last = srt[last];
        printf("%d\n",last);
    }
    return 0;    
}
