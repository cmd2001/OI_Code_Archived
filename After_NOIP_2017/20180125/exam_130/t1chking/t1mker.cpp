#include<bits/stdc++.h>
using namespace std;

inline int _rand(int x) {
    return ( rand() & 1 ) ? rand()%x+1 : -(rand()%x+1);
}
int main() {
    srand((unsigned long long)new char);
    int n = rand() % 13 +10;
    printf("%d\n",n);
    for(int i=1;i<=n;i++)
        printf("%d %d\n",_rand(2000),_rand(2000));
    return 0;
}