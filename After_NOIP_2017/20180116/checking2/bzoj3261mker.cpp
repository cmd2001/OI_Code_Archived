#include<bits/stdc++.h>
using namespace std;
const int maxn = 300000;

inline int _rand() {
    return rand() % 10000001;
}
inline int _rand(int x) {
    return rand()%x+1;
}

int main() {
    //freopen("dat.txt","w",stdout);
    srand((unsigned long long)new char);
    printf("%d %d\n",maxn,maxn);
    for(int i=1;i<=maxn;i++)
        printf("%d%c",_rand(),i!=maxn?' ':'\n');
    int x = maxn;
    for(int i=1;i<=maxn;i++) {
        if( rand() & 1 ) {
            ++x;
            printf("A %d\n",_rand());
        }
        else
        {
            int r = _rand(x);
            int l = _rand(r);
            printf("Q %d %d %d\n",l,r,_rand());
        }
    }
}