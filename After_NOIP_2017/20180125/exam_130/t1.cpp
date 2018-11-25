#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

struct Node {
    int mx,mi;
    friend bool operator < (const Node &a,const Node &b) {
        return a.mx + a.mi < b.mx + b.mi;
    }
}ns[maxn];

multiset<Node> heap;

int main() {
    static int n,lim,ans;
    scanf("%d",&n) , lim = n >> 1;
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&ns[i].mx,&ns[i].mi);
        if( ns[i].mx < ns[i].mi )
            swap(ns[i].mx,ns[i].mi);
    }
    for(int i=1;i<=n;i++) {
        if( heap.size() < lim ) {
            heap.insert(ns[i]);
            ans -= ns[i].mx;
        } else if( *heap.begin() < ns[i] ) {
            Node b = *heap.begin();
            heap.erase(heap.begin());
            ans += b.mx , ans += b.mi;
            heap.insert(ns[i]);
            ans -= ns[i].mx;
        } else ans += ns[i].mi;
    }
    
    printf("%d\n",ans);
    
    return 0;
}