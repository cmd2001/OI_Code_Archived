#include<bits/stdc++.h>
using namespace std;

inline int _(int r) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 500 , m = 500;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++) {
        int t = _(n);
        while(t==i) t = _(n);
        printf("%d %d\n",t,i);
    }
    for(int i=n+1;i<=m;i++) {
        int a = _(n) , b = _(n);
        while(a==b) a = _(n) , b = _(n);
        printf("%d %d\n",a,b);
    }
    return 0;
}