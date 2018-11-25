#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1e9) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 1e5 , m = 1e5;
    printf("%d %d\n",n,m);
    for(int i=2;i<=n;i++) printf("%d %d\n",i,i-1);
    for(int i=1;i<=m;i++) {
        int o;
        if( i <= 2 ) o = 1;
        else if( i <= 4 ) o = 2;
        else o = min( 3 , _(5) );
        if( o == 1 ) printf("ChangeW %d %d\n",1,_());
        else if( o == 2 ) printf("ChangeB %d %d\n",1,_());
        else {
            int l = _(5) , r = _();
            printf("Query %d %d %d %d\n",1,n,min(l,r),max(l,r));
        }
    }
    return 0;
}
