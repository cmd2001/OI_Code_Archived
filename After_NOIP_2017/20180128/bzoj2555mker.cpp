#include<bits/stdc++.h>
using namespace std;
const int maxl=500,maxll=2;

inline int _rand() {
    return rand()%5;
}
inline void randstr(int len) {
    while( len-- )
        putchar('A'+_rand());
    puts("");
}

int main() {
    srand((unsigned long long)new char);
    int m = 1000;
    printf("%d\n",m);
    randstr(maxl);
    while( m-- ) {
        if( rand()&1 ) printf("Q ") , randstr(maxll);
        else printf("A ") , randstr(maxl);
    }
    return 0;
}
