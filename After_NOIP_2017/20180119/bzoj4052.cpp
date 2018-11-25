#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;

inline lli gcd(lli a,lli b) {
    if( ! ( a && b ) ) return a | b;
    register lli t;
    while( t = a % b )
        a = b , b = t;
    return b;
}

struct Node {
    int pos;
    lli g;
    Node() {}
    Node(const int &pp,const lli &gg) {
        pos = pp , g = gg;
    }
}stk[50],tp[50];

int top,tptop;

inline void init() {
    top = tptop = 0;
}

int main() {
    static int T,n;
    static lli x,ans;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%d",&n);
        init() , ans = -1;
        for(int i=1;i<=n;i++) {
            scanf("%lld",&x);
            stk[++top] = Node(i,x);
            for(int i=1;i<=top;i++)
                stk[i].g = gcd( stk[i].g , x );
            tptop = 0;
            for(int j=1;j<=top;j++)
                if( j == 1 || stk[j].g != stk[j-1].g )
                    tp[++tptop] = stk[j] , ans = max( ans , stk[j].g * ( i - stk[j].pos + 1 ) );
            memcpy(stk+1,tp+1,sizeof(Node)*tptop);
            top = tptop;
        }
        printf("%lld\n",ans);
    }
    
    return 0;
}
