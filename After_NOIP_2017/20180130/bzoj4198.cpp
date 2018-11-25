#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
#define debug cout
using namespace std;

struct Node {
    lli height,siz;
    friend bool operator < (const Node &a,const Node &b) {
        return a.siz != b.siz ? a.siz > b.siz : a.height > b.height;
    }
};
priority_queue<Node> heap;

lli sum,height;
int n,k;

int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {
        lli t;
        scanf("%lld",&t);
        heap.push(Node{0,t});
    }
    if( ( n - 1 ) % ( k - 1 ) ) {
        int p = ( k - 1 ) - ( n - 1 ) % ( k - 1 );
        while( p-- )
            heap.push(Node{0,0});
    }
    while( heap.size() != 1 ) {
        lli ss = 0 , hh = 0;
        for(int i=1;i<=k;i++) {
            Node t = heap.top(); heap.pop();
            ss += t.siz;
            hh = max( hh , t.height );
        }
        sum += ss  , height = max( height , hh + 1 );
        heap.push(Node{hh+1,ss});
    }
    printf("%lld\n%lld\n",sum,height);
    return 0;
}
