#include<bits/stdc++.h>

_(int r) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    static int n = 50 , m = 50 , t = 50;
    printf("%d %d %d\n",n,m,t);
    for(int i=1;i<=m;i++) {
        int s = _(t) , tt = _(t);
        if( s > tt ) std::swap(s,tt);
        printf("%d %d %d %d\n",_(n),_(n),s,tt);
    }
    return 0;
}
