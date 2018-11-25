#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1e8) {
    return rand() % r + 1;
}

int main() {
    freopen("comu.txt","r",stdin);
    srand((unsigned long long)new char);
    static int n = 15000 , m = 14991 , x;
    int base = _(100);
    printf("%d %d\n",n,m);
    while(n--) x = _() , printf("%d %d\n",x,x+base);
    while(m--) x = _() , printf("%d %d %d\n",x,x+base,_(1e6));
    return 0;
}

