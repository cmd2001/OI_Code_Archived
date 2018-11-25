#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;

inline lli __() {
    return rand() ^ ( (lli) rand() << 16 ) ^ ( (lli) rand() << 32 );
}
inline int ___() {
    return __() % (lli) 9e5 + 1e5;
}
inline int _(int r=32768) {
    return rand() % r + 1;
}

int main() {
    srand((unsigned long long)new char);
    int n = _(4000) , m = ___();
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++) printf("%d%c",_(),i!=n?' ':'\n');
    return 0;
}
