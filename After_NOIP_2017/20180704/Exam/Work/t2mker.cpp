#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1e9) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 1e3 , m = 1e3;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++) printf("%d%c",_(),i!=n?' ':'\n');
    for(int i=1;i<=m;i++) putchar('A');
    return puts("");
}

