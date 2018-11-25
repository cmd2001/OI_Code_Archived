#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
const int maxk=16,lim=(1<<16)+5;

struct BinaryIndexTree {
    int dat[lim];
    #define lowbit(x) (x&-x)
    inline void update(int pos,const int &x) {
        while( pos < lim ) dat[pos] += x , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while(pos) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
}bit[maxk];

int sum;
multiset<int> app;

inline void update(int x,const int &t) {
    for(int i=0;i<16;i++) bit[i].update( ( x & ((1<<(i+1))-1) ) + 1 , t );
}
inline int query(int x) {
    int l = 1 << x , r = ( 1 << ( x + 1 ) ) - 1 , ret = 0;
    ret += bit[x].query( min( lim - 1 , max( 0 , r - ( sum & ((1<<(x+1))-1) ) + 1 ) ) );
    ret -= bit[x].query( min( lim - 1 , max( 0 , l - ( sum & ((1<<(x+1))-1) ) ) ) );
    l |= 1 << ( x + 1 ) , r |= 1 << ( x + 1 );
    ret += bit[x].query( min( lim - 1 , max( 0 , r - ( sum & ((1<<(x+1))-1) ) + 1 ) ) );
    ret -= bit[x].query( min( lim - 1 , max( 0 , l - ( sum & ((1<<(x+1))-1) ) ) ) );
    return ret;
}

int main() {
    static int n;
    static char o[10];
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++) {
        scanf("%s%d",o,&x);
        if( *o == 'A' ) sum += x;
        else if( *o == 'I' ) x -= sum , app.insert(x) , update(x,1);
        else if( *o == 'D' ) x -= sum , update(x,-(signed)app.count(x)) , app.erase(x);
        else printf("%d\n",query(x));
    }
    return 0;
}

