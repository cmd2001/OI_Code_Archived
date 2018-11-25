#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;

inline lli gcd(lli a,lli b) {
    if( ! ( a && b ) )
        return a | b;
    register lli g;
    while( g = a % b )
        a = b , b = g;
    return b;
}
struct Node {
    lli up,down;
    inline Node(lli uu=0,lli dd=0) {
        up = uu , down = dd;
    }
    inline bool judge() {
        return up <= down;
    }
    inline Node rev() {
        return Node(down,up);
    }
    inline void sim() {
        lli g = gcd(up,down);
        up /= g , down /= g;
    }
}ans,l,r;

Node solve(Node l,Node r) {
    lli c = l.up / l.down;
    if( ( c + 1 ) * r.down < r.up  )
        return Node(c+1,1);
    if( !l.up )
        return Node(1, r.down / r.up + 1 );
    Node ret;
    if( l.judge() && r.judge() ) {
        ret = solve(r.rev(),l.rev());
        return ret.rev();
    }
    ret = solve( Node( l.up-c*l.down , l.down ) , Node( r.up-c*r.down , r.down ) );
    return Node( ret.up + ret.down * c , ret.down );
}

int main() {
    static lli n,rr,down;
    while( scanf("%lld 0.%lld",&n,&rr) == 2 ) {
        if( !rr ) {
            puts("1");
            continue;
        }
        down = 1;
        while(n--)
            down *= 10;
        l.up = rr * 10 - 5 , r.up = rr * 10 + 5 , l.down = r.down = down * 10;
        l.sim() , r.sim();
        ans = solve(l,r);
        printf("%lld\n",min(ans.down,l.down));
    }
    return 0;
}