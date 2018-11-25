#include<bits/stdc++.h>
using namespace std;
const int maxn=10;

inline int _rand(int l) {
    return rand()%l+1;
}

int main() {
    srand(time(0));
    const int maxn=50000;
    printf("%d\n",maxn);
    for(int i=1;i<=200000;i++) {
        int ope = i <= 0 ? 1 : _rand(2);
        if( ope == 1 ) {
            printf("%d %d %d %d\n",ope,i,i,_rand(400));
        } else {
            int tx = _rand(maxn) , ty = _rand(maxn);
            printf("%d %d %d %d %d\n",ope,_rand(tx),_rand(ty),tx,ty);
        }
    }
    puts("3");
    return 0;
}