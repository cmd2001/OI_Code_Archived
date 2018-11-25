#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
#pragma GCC optimize("no-stack-protector")
#include<cstdio>
#include<ext/pb_ds/priority_queue.hpp>
#define ull unsigned long long
using namespace std;
using namespace __gnu_pbds;
const unsigned mod=1e9+7;
 
__gnu_pbds::priority_queue<unsigned,less<unsigned>,pairing_heap_tag> exs;
__gnu_pbds::priority_queue<unsigned,greater<unsigned>,pairing_heap_tag> del;

__inline unsigned gen(const unsigned &t,const unsigned &ans) {
    return ( 714636908ull * t % mod + 681692770u ) * ( 846930886ull * ans % mod + 804289376u ) % mod;
}

int main() {
    freopen("mid.in","r",stdin);
    freopen("mid.out","w",stdout);
    static unsigned n,t,ans,out;
    scanf("%u%u",&n,&t);
    for(register unsigned i=1,p=1;i<=n;i++,p=(i+1)>>1) {
        exs.push(t);
        while( exs.size() > p ) del.push(exs.top()) , exs.pop();
        while( del.size() && del.top() < exs.top() ) exs.push(del.top()) , del.pop() , del.push(exs.top()) , exs.pop();
        ans = exs.top() , out ^= ans , t = gen(t,ans);
    }
    printf("%u\n",out);
    fclose(stdout);
    return 0;
}
