#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1e3) {
    return rand() % r + 1;
}

int main() {
    freopen("comu.txt","r",stdin);
    srand((unsigned long long)new char);
    static int n = 1000 , m = 991 , x;
    printf("%d %d\n",n,m);
    while(n--) printf("%d %d\n",_(),_());
    while(m--) printf("%d %d %d\n",_(),_(),_(1e2));
    return 0;
}

