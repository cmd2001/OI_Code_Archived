#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int h[maxn];
char o[maxn];

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",h+i);
    scanf("%s",o+1);
    for(int i=1;i<=m;i++) {
        if( o[i] == 'A' ) {
            for(int j=1;j<=n;j++) if( h[j-1] > h[j] ) ++h[j];
        } else {
            for(int j=n;j;j--) if( h[j+1] > h[j] ) ++h[j];
        }
    }
    for(int i=1;i<=n;i++) printf("%d%c",h[i],i!=n?' ':'\n');
    return 0;
}

