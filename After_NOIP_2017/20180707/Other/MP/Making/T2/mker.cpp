#include<bits/stdc++.h>
using namespace std;

inline int _(int r=26) {
    return rand() % r;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 100 , m = 99 , k = 20 , q = 100; // ?
    printf("%d %d %d\n",n,m,k);
    for(int i=1;i<=k;i++) {
        int len = _(3) + 3;
        for(int j=1;j<=len;j++) putchar('a'+_());
        puts("");
    }
    printf("%d\n",q);
    while(q--) {
        int row = _(n) + 1;
        printf("%d ",row);
        for(int j=1;j<=m;j++) putchar('a'+_());
        puts("");
    }
    return 0;
}
