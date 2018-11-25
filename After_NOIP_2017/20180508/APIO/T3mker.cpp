#include<bits/stdc++.h>
using namespace std;

inline int _(int r=999) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = _(10000)+1;
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d%c",_(n-1),i!=n?' ':'\n');
    return 0;
}