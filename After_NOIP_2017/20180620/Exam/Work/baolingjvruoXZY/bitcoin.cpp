#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<tr1/unordered_set>
#include<cctype>
typedef long long int lli;
using namespace std;
using namespace tr1;
const int maxk=18;
const lli lim=(1<<18)+5;

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

lli sum;
unordered_multiset<lli> app;

inline void update(lli x,const int &t) {
    for(int i=0;i<maxk;i++) bit[i].update( ( x & ((1<<(i+1))-1) ) + 1 , t );
}
inline int query(int x) {
    int l = 1 << x , r = ( 1 << ( x + 1 ) ) - 1 , ret = 0;
    ret += bit[x].query( min( lim - 1 , max( 0ll , r - ( sum & ((1<<(x+1))-1) ) + 1 ) ) );
    ret -= bit[x].query( min( lim - 1 , max( 0ll , l - ( sum & ((1<<(x+1))-1) ) ) ) );
    l |= 1 << ( x + 1 ) , r |= 1 << ( x + 1 );
    ret += bit[x].query( min( lim - 1 , max( 0ll , r - ( sum & ((1<<(x+1))-1) ) + 1 ) ) );
    ret -= bit[x].query( min( lim - 1 , max( 0ll , l - ( sum & ((1<<(x+1))-1) ) ) ) );
    return ret;
}

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch , fix = 1;
    while( !isdigit(ch=nextchar()) ) fix = ch == '-' ? -fix : fix;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret * fix;
}

int main() {
    static int n;
    static lli x;
    freopen("bitcoin.in","r",stdin);
    freopen("bitcoin.out","w",stdout);
    n = getint();
    for(int i=1,o;i<=n;i++) {
        o = getint() , x = getint();
        if( o == 2 ) sum += x;
        else if( o == 0 ) x -= sum , app.insert(x) , update(x,1);
        else if( o == 1 ) x -= sum , update(x,-(signed)app.count(x)) , app.erase(x);
        else printf("%d\n",query(x));
    }
    fclose(stdout);
    return 0;
}

