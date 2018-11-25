#include<bits/stdc++.h>
using namespace std;

int main() {
    const int maxn=90000;
    freopen("dat.txt","w",stdout);
    for(int i=1;i<=maxn;i++)
        putchar('a'+rand()%26);
        //putchar('a');
    puts("");
    int m = 500;
    printf("%d\n",m);
    for(int i=1;i<=m;i++)
    	printf("%d\n",rand()%(maxn/2)+1);
    return 0;
}
