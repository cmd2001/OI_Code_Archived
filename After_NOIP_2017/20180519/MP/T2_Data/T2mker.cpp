#include<bits/stdc++.h>
using namespace std;
const int lim=1e9+8;

inline int _(int r=lim) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n,m,tpe;
    scanf("%d%d%d",&n,&m,&tpe); // tpe == 1 means include modify .
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++) printf("%d%c",_(),i!=n?' ':'\n');
    for(int i=1,o;i<=m;i++) {
        if( tpe ) o = 1 + ( _(3) == 1 ); // 1/3 is modify .
        else o = 1;
        printf("%d %d",o,_(n));
        if( o == 1 ) putchar('\n');
        else printf(" %d\n",_());
    }
    return 0;
}
