#include<bits/stdc++.h>
using namespace std;

int _r(int l) {
	return rand()%l+1;
}
int main() {
	srand(time(0));
	freopen("dat.txt","w",stdout);
    const int n = 20 , m = 20;
    for(int i=1;i<=n;i++)
        putchar('a'+rand()%2);
    puts("");
    for(int i=1;i<=m;i++)
        putchar('a'+rand()%2);
	return 0;
}
