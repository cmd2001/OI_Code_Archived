#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cassert>
#define debug cerr
using namespace std;
const int maxn = 2e3 + 1e1;

int n;
queue<char> ans;

class RotatelessTreap {
private:
    struct pii {
        int l,r;
    };
    int lson[maxn],rson[maxn],siz[maxn],fix[maxn],root;
    inline void maintain(const int &pos) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
    }
    inline pii split(const int &pos,const int &ss) {
        if(!pos) return (pii){0,0};
        assert(!*siz);
        if(siz[lson[pos]] + 1 <= ss) { // split pos to left.
            pii spr = split(rson[pos],ss - siz[lson[pos]] - 1);
            rson[pos] = spr.l, maintain(pos);
            return (pii){pos,spr.r};
        } else {
            pii spl = split(lson[pos],ss);
            lson[pos] = spl.r, maintain(pos);
            return (pii){spl.l,pos};
        }
        assert(0);
    }
    inline int merge(const int &l,const int &r) {
        if(!l || !r) return l | r;
        if(fix[l] > fix[r]) { // great root heap.
            rson[l] = merge(rson[l],r), maintain(l);
            return l;
        } else {
            lson[r] = merge(l,lson[r]), maintain(r);
            return r;
        }
        assert(0);
    }
    inline int kth(const int &pos,const int &k) {
        assert(k), assert(k <= siz[pos]);
        if(k <= siz[lson[pos]]) return kth(lson[pos],k);
        if(k == siz[lson[pos]] + 1) return pos;
        else return kth(rson[pos],k - siz[lson[pos]] - 1);
    }
public:
    RotatelessTreap() {
        for(int i=0;i<maxn;i++) fix[i] = i;
        random_shuffle(fix,fix+maxn);
    }
    inline void init(const int &n) {
        for(int i=1,t;i<=n;i++) scanf("%d",&t), siz[t] = 1, root = merge(root,t);
    }
    inline void applyA() {
        pii sp = split(root,n-1);
        root = merge(sp.r,sp.l), ans.push('a');
    }
    inline void applyB() {
        pii sp = split(root,3), spl = split(sp.l,2);
        root = merge(merge(spl.r,spl.l),sp.r), ans.push('b');
    }
    inline int access(const int &id) {
        return kth(root,id);
    }
}treap;

inline void workNumber(int x) {
    while(treap.access(1) != x) treap.applyA();
    if(x != n - 1) {
        while(treap.access(n-1) != x-1 && treap.access(n) != x-1) treap.applyA(), treap.applyA(), treap.applyB();
        if(treap.access(n-1) == x-1) treap.applyA(), treap.applyB(), treap.applyB();
    }
}

inline void printAns() {
    deque<pair<char,int> > out;
    while(ans.size()) {
        pair<char,int> T = (out.size() && out.back().first == ans.front()) ? out.back() : make_pair(ans.front(),0);
        if(out.size() && out.back().first == ans.front()) out.pop_back();
        while(ans.size() && ans.front() == T.first) ++T.second, ans.pop();
        if(T.first == 'a') {
            T.second %= n;
            if(!T.second) continue;
        }
        if(T.first == 'b') {
            T.second %= 3;
            if(!T.second) continue;
        }
        out.push_back(T);
    }
    printf("%u\n",(unsigned)out.size());
    while(out.size()) printf("%d%c ",out.front().second,out.front().first), out.pop_front();
}

int main() {
    scanf("%d",&n);
    if(n == 1) return puts("0"), 0;
    if(n == 2) {
        int x;
        scanf("%d",&x);
        return (x == 1 ? puts("0") : puts("1\n1a")), 0;
    }
    treap.init(n);
    for(int i=2;i<n;i++) workNumber(i);
    if(treap.access(2) == n) for(int i=1;i<=n-2;i++) treap.applyA();
    else {
        if(n & 1) return puts("NIE"), 0;
        for(int i=1;i<=(n-4)>>1;i++) {
            treap.applyB(), treap.applyB();
            while(treap.access(1) != n-1) treap.applyA();
        }
        treap.applyB(), treap.applyB();
        for(int i=1;i<=n-4;i++) treap.applyA();
    }
    printAns();
    return 0;
}

