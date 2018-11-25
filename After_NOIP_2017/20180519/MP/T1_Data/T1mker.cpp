#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;

int seq[maxn];

inline int _(int r=5) {
    return rand() % r + 1;
}

int main() {
    freopen("ddddat.txt","w",stdout);
    srand((unsigned long long)new char);
    static int n = 10 , m = 10;
    printf("%d %d\n",n,m);
    for(int i=1;i<=1e5;i++) seq[i] = rand() % 10;
    for(int i=1;i<=n;i++) printf("%d%c",seq[_()],i!=n?' ':'\n');
    for(int i=1,o,l,r;i<=m;i++) {
        o = _(4) == 1 ? 2 : 1;
        if( o == 1 ) l = _(n) , r = _(n) , printf("1 %d %d %d\n",min(l,r),max(l,r),seq[_()]);
        else printf("2 %d %d\n",_(n),seq[_()]);
    }
    return 0;
}