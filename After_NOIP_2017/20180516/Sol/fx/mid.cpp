/*#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("no-stack-protector")*/
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
typedef unsigned long long int ulli;
const int mod=1e9+7;
const int lim=10;

std::priority_queue<ulli,std::vector<ulli>,std::less<ulli> > lft;
std::priority_queue<ulli,std::vector<ulli>,std::greater<ulli> > rit;
__gnu_pbds::tree<ulli,__gnu_pbds::null_type,std::less<ulli>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> buf;

__inline unsigned gen(const unsigned &t,const unsigned &ans) {
    return ( 714636908ull * t % mod + 681692770u ) * ( 846930886ull * ans % mod + 804289376u ) % mod;
}

int main() {
    static unsigned n,t,ans,out;
    scanf("%u%u",&n,&t);
    for(register unsigned i=1,p;i<=n;i++) {
        p = ( i + 1 ) >> 1;
        register ulli cur = (ulli) t * ( mod + 1 ) + i;
        if( buf.size() && cur < *buf.begin() ) lft.push(cur);
        else if( buf.size() && cur > *buf.rbegin() ) rit.push(cur);
        else buf.insert(cur);
        while( p > lft.size() + buf.size() ) buf.insert(rit.top()) , rit.pop();
        while( p <= lft.size() ) buf.insert(lft.top()) , lft.pop();
        out ^= ans = *buf.find_by_order(p-lft.size()-1) / ( mod + 1 ) ;
        t = gen(t,ans);
        while( buf.size() > lim ) {
            if( lft.size() < rit.size() ) lft.push(*buf.begin()) , buf.erase(buf.begin());
            else rit.push(*buf.rbegin()) , buf.erase(buf.rbegin());
        }
    }
    printf("%u\n",out);
    return 0;
}

