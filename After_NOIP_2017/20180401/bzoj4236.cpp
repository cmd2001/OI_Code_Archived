#include<cstdio>
#include<algorithm>
const int maxn=2e5+1e2;

struct Node {
    int x,y,id;
    friend bool operator < (const Node &a,const Node &b) {
        if( a.x != b.x ) return a.x < b.x;
        if( a.y != b.y ) return a.y < b.y;
        return a.id < b.id;
    }
    friend bool operator == (const Node &a,const Node &b) {
        return a.x == b.x && a.y == b.y;
    }
}ns[maxn];

char in[maxn];

int main() {
    static int n,ans;
    scanf("%d%s",&n,in+1);
    for(int i=1;i<=n;i++) {
        ns[i] = ns[i-1] , ns[i].id = i;
        switch ( in[i] ) {
            case 'J': --ns[i].x , --ns[i].y; break;
            case 'O': ++ns[i].x; break;
            case 'I': ++ns[i].y; break;
        }
    }
    std::sort(ns,ns+1+n);
    for(int l=0,r;l<=n;l=r+1) {
        for(r=l;r<n&&ns[r+1]==ns[l];r++) ;
        ans = std::max( ans , ns[r].id - ns[l].id );
    }
    printf("%d\n",ans);
    return 0;
}