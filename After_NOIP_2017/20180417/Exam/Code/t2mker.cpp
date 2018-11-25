#include<bits/stdc++.h>
using namespace std;

inline int _(int r=10) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 8 , m = 30;
    printf("%d %d\n",n,m);
    for(int i=2;i<=n;i++) printf("%d %d %d\n",_(i-1),i,_());
    for(int i=1;i<=m;i++) printf("%d %d %d %d %d %d\n",_(n),_(n),_(),_(n),_(n),_());
    return 0;
}
