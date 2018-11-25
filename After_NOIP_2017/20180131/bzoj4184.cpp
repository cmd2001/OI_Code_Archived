#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
#include<vector>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

struct Node {
    int dat[32];
    inline void insert(int x) {
        for(int i=30;~i;i--)
            if( x & ( 1 << i ) ) {
                if( !dat[i] ) {
                    dat[i] = x;
                    break;
                } else x ^= dat[i];
            }
    }
    inline int query() {
        int ret = 0;
        for(int i=30;~i;i--)
            ret = max( ret , ret ^ dat[i] );
        return ret;
    }
}ept;

int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],root,cnt;
vector<int> dat[maxn<<3];
set<pair<int,int> > st;

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
}
inline void insert(int pos,int ll,int rr,int x) {
    if( rr < l[pos] || r[pos] < ll ) return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        dat[pos].push_back(x);
        return;
    }
    insert(lson[pos],ll,rr,x);
    insert(rson[pos],ll,rr,x);
}
inline void dfs(int pos,Node sta) {
    for(unsigned i=0;i<dat[pos].size();i++)
        sta.insert(dat[pos][i]);
    if( l[pos] == r[pos] ) {
        printf("%d\n",sta.query());
        return;
    }
    dfs(lson[pos],sta);
    dfs(rson[pos],sta);
}

int main() {
    static int n;
    scanf("%d",&n);
    build(root=++cnt,1,n);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x);
        if( x > 0 ) st.insert(make_pair(x,i));
        else {
            set<pair<int,int> >::iterator it = st.lower_bound(make_pair(-x,0));
            insert(root,it->second,i-1,-x);
            st.erase(it);
        }
    }
    for(set<pair<int,int> >::iterator it=st.begin();it!=st.end();++it)
        insert(root,it->second,n,it->first);
    dfs(root,ept);
    return 0;
}

