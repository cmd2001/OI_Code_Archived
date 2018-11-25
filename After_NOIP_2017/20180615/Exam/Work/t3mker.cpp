#include<bits/stdc++.h>
using namespace std;

inline int _(int r=1e5) {
    return rand() % r;
}

inline void make_case(int n,int m) {
    printf("%d %d %d\n",n,m,5);
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) printf("%d%c",_(9)-1,j!=m?' ':'\n');
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) printf("%d%c",_(),j!=m?' ':'\n');
}
int main() {
    freopen("tle.txt","w",stdout);
    srand((unsigned long long)new char);
    static int T = 20 , n = 25 , m = 25;
    printf("%d\n",T);
    while(T--) make_case(n,m);
    return 0;
}