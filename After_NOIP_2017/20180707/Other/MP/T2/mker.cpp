#include<bits/stdc++.h>
using namespace std;

inline int _(int r=2) {
    return rand() % r;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 3 , m = 2 , k = 10 , q = 2; // ?
    printf("%d %d %d\n",n,m,k);
    for(int i=1;i<=k;i++) {
        int len = _(n*m)+ 3; // ?
        for(int j=1;j<=len;j++) putchar('a'+_());
        puts("");
    }
    printf("%d\n",q);
    while(q--) {
        int row = 1; // ?
        printf("%d ",row);
        for(int j=1;j<=m;j++) putchar('a'+_());
        puts("");
    }
}