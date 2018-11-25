#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
typedef long long int lli;
const int maxn=5e2+1e1;

struct Food {
    lli s,p;
    friend bool operator < (const Food &a,const Food &b) {
        return a.s != b.s ? a.s < b.s : a.p > b.p;
    }
}in[maxn],stk[maxn];

lli m,f;
int n,top;

struct Node {
    lli day,rem;
    friend bool operator < (const Node &a,const Node &b) {
        return a.day != b.day ? a.day < b.day : a.rem < b.rem;
    }
};

inline Node calc(lli mid) { // ++s first .
    lli day = 0 , per = 0 , rem = m - f * mid;
    for(int i=1;i<=top;i++) {
        if( stk[i].s >= per ) {
            lli siz = min( rem / stk[i].p / mid , stk[i].s - per + 1 );
            per += siz , day += siz * mid , rem -= stk[i].p * mid * siz;
        }
        if( stk[i].s >= per ) {
            lli siz = min( rem / stk[i].p , mid );
            per++ , day += siz , rem -= siz * stk[i].p;
        }
    }
    return (Node){day,per};
}
inline lli tri() {
    lli l = 1 , r = m / ( f + stk[1].p ) , lmid , rmid;
    Node ret = (Node){0,0} , cl , cr;
    while( r > l + 2 ) {
        lmid = ( (long double) l + l + r ) / 3 , rmid = ( (long double) l + r + r ) / 3;
        cl = calc(lmid) , cr = calc(rmid);
        if( cr < cl ) r = rmid;
        else l = lmid;
    }
    for(lli i=l;i<=r;i++) ret = max( ret , calc(i) );
    return ret.day;
}
inline void fixFood() {
    sort(in+1,in+1+n) , top = 0;
    for(int i=1;i<=n;i++) {
        while( top && in[i].p <= stk[top].p ) --top;
        stk[++top] = in[i];
    }
}

int main() {
    while( scanf("%lld%lld%d",&m,&f,&n) == 3 ) {
        for(int i=1;i<=n;i++) scanf("%lld%lld",&in[i].p,&in[i].s);
        fixFood() , printf("%lld\n",tri());
    }
    return 0;
}

