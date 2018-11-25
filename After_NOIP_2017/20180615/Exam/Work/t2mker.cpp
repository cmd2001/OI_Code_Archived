#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1e8) {
    return ( r == 100000000 ? 8e8 : 0 ) +  rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 5000 , m = 5000;
    printf("%d %d\n",n,m);
    for(int i=2;i<=n;i++) printf("%d %d\n",i,i-1);
    for(int i=1;i<=m;i++) {
        int o;
        if( i <= 2 ) o = 1;
        else if( i <= 4 ) o = 2;
        else o = min( 3 , _(4) );
        if( o == 1 ) printf("ChangeW %d %d\n",_(n),_());
        else if( o == 2 ) printf("ChangeB %d %d\n",_(n),_());
        else {
            int l = _(1e3) , r = _();
            printf("Query %d %d %d %d\n",_(n),_(n),min(l,r),max(l,r));
        }
    }
    return 0;
}
