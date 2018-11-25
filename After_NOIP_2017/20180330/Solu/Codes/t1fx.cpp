#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxe=1e7+1e2;

int n,sizt;
struct Node {
    int val,id;
    vector<char*> ss;
    friend bool operator < (const Node &a,const Node &b) {
        return a.val > b.val;
    }
}ns[maxn];

struct SegmentTree {
    int lson[maxe],rson[maxe],siz[maxe],cnt;
    inline void insert(int &pos,int l,int r,int tar) {
        if( !pos ) pos = ++cnt; ++siz[pos];
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos],l,mid,tar);
        else insert(rson[pos],mid+1,r,tar);
    }
    inline int find(int pos,int l,int r,int tar) {
        if( !pos ) return 0;
        if( l == r)  return 1;
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) return find(lson[pos],l,mid,tar);
        return find(rson[pos],mid+1,r,tar);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos ) return 0;
        if( ll <= l && r <= rr ) return siz[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
    inline int kth(int pos,int l,int r,int k) { // assert it have kth .
        if( l == r ) return l;
        const int mid = ( l + r ) >> 1;
        if( k <= siz[lson[pos]] ) return kth(lson[pos],l,mid,k);
        else return kth(rson[pos],mid+1,r,k-siz[lson[pos]]);
    }
    inline void dfs(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos ) return;
        if( l == r ) return void(printf("%d%c",ns[l].id,--sizt?' ':'\n'));
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) dfs(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) dfs(rson[pos],mid+1,r,ll,rr);
        else dfs(lson[pos],l,mid,ll,rr) , dfs(rson[pos],mid+1,r,ll,rr);
    }
}cmt;

struct Trie {
    int ch[maxn][26],roots[maxn],fa[maxn],root,cnt;
    Trie() { root = cnt = 1; }
    inline void insert(char* s,int li,int id) {
        int now = root;
        //cerr<<"s = "<<s<<endl;
        for(int i=0;i<li;i++) { // starts from 0 !
            const int t = s[i] - 'a';
            if( !ch[now][t] ) ch[now][t] = ++cnt;
            now = ch[now][t];
            if( !cmt.find(roots[now],1,n,id) )
                cmt.insert(roots[now],1,n,id);
        }
    }
    inline void query(char* s,int li,int t) {
        int now = root;
        for(int i=1;i<=li;i++) { // starts from 1 !
            const int t = s[i] - 'a';
            now = ch[now][t];
        }
        if( !now ) return void(puts("0"));
        int tot = cmt.query(roots[now],1,n,1,n);
        printf("%d ",tot);
        if( tot <= t ) sizt = tot , cmt.dfs(roots[now],1,n,1,n);
        else {
            int kth = cmt.kth(roots[now],1,n,t);
            sizt = t , cmt.dfs(roots[now],1,n,1,kth);
        }
    }
}trie;

inline void pushstr(int id) {
    static char s[maxn];
    scanf("%s",s);
    int len = strlen(s);
    char* t = new char[len+1];
    memcpy(t,s,sizeof(char)*(len+1));
    ns[id].ss.push_back(t);
}

int main() {
    static int m;
    static char in[maxn];
    scanf("%d%d",&n,&m);
    for(int i=1,t;i<=n;i++) {
        scanf("%d%d",&ns[i].val,&t) , ns[i].id = i - 1;
        while(t--) pushstr(i);
    }
    sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++)
        for(unsigned j=0;j<ns[i].ss.size();j++) {
            trie.insert(ns[i].ss[j],strlen(ns[i].ss[j]),i);
        }
    for(int i=1,t,li;i<=m;i++) {
        scanf("%d%s",&t,in+1) , li = strlen(in+1);
        trie.query(in,li,t);
    }
    return 0;
}

