#include<cstdio>

int main() {
    static int T,n,in,so,st,su;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n) , so = st = su = 0;
        for(int i=1;i<=n;i++) {
            scanf("%d",&in) , 
            so += ( in == 1 ) , 
            st += ( in == 2 ) , 
            su += in;
        }
        if( ( so == n-1 && st == 1 ) || so == n ) puts(so%3?"YES":"NO");
        else {
            if( ( so & 1 ) || ( (su+n-1) & 1 ) ) puts("YES");
            else puts("NO");
        }
    }
    return 0;
}
