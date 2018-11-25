#include<bits/stdc++.h>
using namespace std;
int in[100010];

inline int _(int r=10) {
    return rand() % r + 1;
}

int main() {
    freopen("dat.in","w",stdout);
    srand((unsigned long long)new char);
    static int n = 1e5 , len = 0;
    printf("%d\n",n);
    for(int i=1;i<=n/20;i++) for(int j=1;j<=20;j++) in[++len] = i;
    random_shuffle(in+1,in+1+n);
    for(int i=1;i<=n;i++) printf("%d%c",in[i],i!=n?' ':'\n');
    return 0;
}
