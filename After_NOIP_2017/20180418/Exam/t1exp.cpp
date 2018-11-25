#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxe=2e7+1e2;
const int mod=1e9+7;

struct PersistentSegmentTree {
    int lson[maxe],rson[maxe],dat[maxe],cnt;
    inline void insert(int &pos,int pre,int l,int r,const int &tar) {
        dat[pos=++cnt] = dat[pre] + 1;
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],lson[pre],l,mid,tar) , rson[pos] = rson[pre];
        else insert(rson[pos],rson[pre],mid+1,r,tar) , lson[pos] = lson[pre];
    }
    inline int query(int pos,int pre,int l,int r,const int &ll,const int &rr) {
        if( !pos || dat[pos] == dat[pre] ) return 0;
        if( ll <= l && r <= rr ) return dat[pos] - dat[pre];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],lson[pre],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],rson[pre],mid+1,r,ll,rr);
        return query(lson[pos],lson[pre],l,mid,ll,rr) + query(rson[pos],rson[pre],mid+1,r,ll,rr);
    }
    inline void reset() {
        memset(dat+1,0,sizeof(int)*cnt) , memset(lson+1,0,sizeof(int)*cnt) , memset(rson+1,0,sizeof(int)*cnt) , cnt = 0;
    }
}pst;

int in[maxn],root[maxn],n,cnt,ans,sub;
vector<int> pos[maxn];
map<int,int> id;

inline int getint() {
    int ret = 0 , fix = 1 , ch;
    while( !isdigit(ch=getchar()) ) fix = ch == '-' ? -fix : fix;
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret * fix;
}

int main() {
    freopen("dat.in","r",stdin);
    freopen("dat.out","w",stdout);
    n = getint();
    for(int i=1;i<=n;i++) {
        in[i] = getint();
        if( id.find(in[i]) == id.end() ) id[in[i]] = ++cnt;
        pos[id[in[i]]].push_back(i);
    }
    for(int i=n,iid;i;i--) {
        root[i] = root[i+1] , iid = id[in[i]];
        for(unsigned j=0;j<pos[iid].size();j++) if( pos[iid][j] > i ) {
            pst.insert(root[i],root[i],1,n,pos[iid][j]);
            ans += pst.query(root[i+1],root[pos[iid][j]],1,n,pos[iid][j]+1,n);
        }
        ans %= mod;
    }
    /*for(int i=1;i<=cnt;i++) {
        for(unsigned j=0;j<pos[i].size();j++) // j is left point a .
            for(unsigned k=j+1;k<pos[i].size();k++) // k is left point b .
                for(unsigned l=k+1;l<pos[i].size();l++) // l is right point a .
                    sub += pst.query(root[pos[i][k]],root[pos[i][k]+1],1,n,pos[i][l]+1,n);
        sub %= mod;
    }*/
    for(int i=1;i<=cnt;i++) {
        pst.reset() , memset(root,0,sizeof(int)*(pos[i].size()+2));
        for(int j=(signed)pos[i].size()-1;j>=0;j--) { // j is left point of now .
            root[j] = root[j+1];
            for(unsigned k=j+1;k<pos[i].size();k++) { // k is right point of now .
                pst.insert(root[j],root[j],1,n,pos[i][k]);
                sub += pst.query(root[j+1],root[k],1,n,pos[i][k]+1,n);
            }
            sub %= mod;
        }
    }
    ans = ( ans - sub + mod ) % mod;
    printf("%d\n",ans);
    return 0;
}

