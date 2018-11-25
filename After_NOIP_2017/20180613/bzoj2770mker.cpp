#include<bits/stdc++.h>
#define debug cout
using namespace std;

set<int> mk,mp;
map<int,int> occ;
int a[111111];

inline int _(int r=2147483647) {
    return rand() % r + 1;
}
inline int getanode() {
    int step = _(mk.size());
    step = 1;
    auto t=mk.begin();
    for(--step;step;++t,--step) ;
    return *t;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 1e5 , m = 3e5;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++) {
        int t = _() - _();
        while( mk.find(t) != mk.end() ) t = _() - _();
        printf("%d%c",t,i!=n?' ':'\n') , mk.insert(t) , a[i] = t;
    }
    for(int i=1;i<=n;i++) {
        int t = _();
        while( mp.find(t) != mp.end() ) t = _();
        printf("%d%c",t,i!=n?' ':'\n') , mp.insert(t) , occ[a[i]] = t;
    }
    for(int i=1;i<=m;i++) {
        int o = min( _(5) , 3 );
        if( o == 1 ) {
            int t = _() - _();
            while( mk.find(t) != mk.end() ) t = _() - _();
            int r = _();
            while( mp.find(r) != mp.end() ) r = _();
            printf("I %d %d\n",t,r) , mk.insert(t) , mp.insert(r) , occ[t] = r;
        } /*else if( o == 2 ) {
            if( !mk.size() ) { --i; continue; }
            int t = getanode();
            printf("D %d\n",t) , mk.erase(t) , mp.erase(occ[t]) , occ.erase(t);
        } */else {
            if( !mk.size() ) { --i; continue; }
            printf("Q %d %d\n",getanode(),getanode());
        }
    }
    return 0;
}
