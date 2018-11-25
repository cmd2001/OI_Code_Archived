#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<functional>
#define lli long long int
using namespace std;
const int maxn=1.5e5+1e2;

struct Node {
    int used,died;
    friend bool operator < (const Node &a,const Node &b) {
        return a.died < b.died;
    }
}ns[maxn];

multiset<int,greater<int> > ms;

int main() {
    static int n,ans;
    static lli sum;
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&ns[i].used,&ns[i].died);
    
    sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++)
        if( sum + ns[i].used <= ns[i].died ) {
            ms.insert(ns[i].used);
            sum += ns[i].used , ++ans;
        } else if( ms.size() && ns[i].used < *ms.begin() ) {
            sum -= *ms.begin() - ns[i].used;
            ms.erase(ms.begin()) , ms.insert(ns[i].used);
        }
    
    printf("%d\n",ans);
    
    return 0;
}