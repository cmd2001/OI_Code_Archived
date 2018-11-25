#include<bits/stdc++.h>
using namespace std;

inline int _(int r=16) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 5 , m = 10;
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d%c",_(),i!=n?' ':'\n');
    printf("%d\n",m);
    for(int i=1;i<=m;i++) {
        int l = _(n) , r = _(n);
        printf("%d %d %d\n",min(l,r),max(l,r),_());
    }
    return 0;
}
