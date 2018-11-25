#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;

int main() {
    srand(time(0));
    freopen("dat.txt","w",stdout);
    for(int i=1;i<=10;i++) {
        for(int j=1;j<=maxn;j++)
            putchar('a'+rand()%2);
        puts("");
    }
}