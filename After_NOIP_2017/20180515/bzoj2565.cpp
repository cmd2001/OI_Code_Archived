#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=2e5+1e2;

struct SegmentTree_mx {
    int dat[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    SegmentTree_mx() { memset(dat,0xef,sizeof(dat)); }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return void( dat[pos] = std::max( dat[pos] , x ) );
        const int mid = ( l + r ) >> 1;
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,x);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,x);
    }
    inline int query(int pos,int l,int r,const int &tar) {
        if( l == r ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) return std::max( dat[pos] , query(lson(pos),l,mid,tar) );
        else return std::max( dat[pos] , query(rson(pos),mid+1,r,tar) );
    }
}smx;

struct SegmentTree_mi {
    int dat[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    SegmentTree_mi() { memset(dat,0x3f,sizeof(dat)); }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &x) {
        if( ll <= l && r <= rr ) return void( dat[pos] = std::min( dat[pos] , x ) );
        const int mid = ( l + r ) >> 1;
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,x);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,x);
    }
    inline int query(int pos,int l,int r,const int &tar) {
        if( l == r ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) return std::min( dat[pos] , query(lson(pos),l,mid,tar) );
        else return std::min( dat[pos] , query(rson(pos),mid+1,r,tar) );
    }
}smi;

char in[maxn>>1],s[maxn];
int f[maxn],pos,mxr;
int li,len,ans;

inline void manacher() {
    *s = '$';
    for(int i=1;i<=li;i++) s[++len] = in[i] , s[++len] = '#';
    for(int i=1;i<=len;i++) {
        if( i <= mxr ) f[i] = std::min( f[2*pos-i] , mxr - i );
        while( s[i+f[i]] == s[i-f[i]] ) ++f[i];
        if( i + f[i] > mxr ) mxr = i + f[i] , pos = i;
        smx.update(1,1,len,i-f[i]+1,i,i) , smi.update(1,1,len,i,i+f[i]-1,i);
    }
}
inline int query_l(int pos) {
    int cent = smi.query(1,1,len,pos);
    return pos - cent + 1;
}
inline int query_r(int pos) {
    int cent = smx.query(1,1,len,pos);
    return cent - pos + 1;
}
inline void getans() {
    for(int i=2;i<len;i+=2) ans = std::max( ans , query_l(i-1) + query_r(i+1) );
}

int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    manacher() , getans() , printf("%d\n",ans);
    return 0;
}
