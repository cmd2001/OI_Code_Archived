#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1000) {
    return rand() % r + 1;
}

int main() {
    static int n = 10;
    printf("%d\n",n);
    while(n--) printf("%d %d\n",_(),_());
    return 0;
}
