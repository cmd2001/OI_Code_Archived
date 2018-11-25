#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define debug cout
using namespace std;
typedef long long LL;
const int N = 1e6+5;
const int Max = 1e6;
const int inv2 = 500000004;
const int inv6 = 166666668;
const int mod = 1e9+7;
const int mod1 = 5e6+5;
const int M = 5 * mod1;
int prime[N], cnt, phi[N], head[mod1+3];
bool F[N];
map <int,int> mp;

struct graph {
    int next, to, val;
    graph () {}
    graph (int _next,int _to,int _val)
    :next(_next),to(_to), val(_val){}
}edge[M];

inline void add(int x,int y) {
    int temp = x % mod1;
    edge[++cnt] = graph(head[temp], x, y);
    head[temp] = cnt;
}

inline int find(int x) {
    int temp = x % mod1;
    for(int i=head[temp];i;i=edge[i].next) 
        if(edge[i].to == x) return edge[i].val;
    return -1;
}

inline void init() {
    phi[1] = 1;
    register int i, j;
    for(i=2;i<=Max;++i) {
        if(!F[i]) {
            prime[++cnt] = i;
            phi[i] = i-1;
        }
        for(j=1;prime[j]*i<=Max;++j) {
            F[i*prime[j]] = 1;
            if(i%prime[j]==0) {
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i*prime[j]] = phi[i] * (prime[j]-1);
        }
    }
    for(i=1;i<=Max;++i) phi[i] = (long long) i*phi[i]%mod;
    for(i=1;i<=Max;++i) (phi[i] += phi[i-1]) %= mod;
}

inline int calc_3(int x) {
    return (long long)x * (x+1) % mod * (2*x+1) % mod * inv6 % mod;
}

inline int calc_2(int x,int y) {
    return (LL)(x+y)%mod*(y-x+1)%mod*inv2%mod;
}

inline int calc(int x) {
    if(x <= Max) return phi[x];
    int tt = find(x);
    if(tt != -1) return tt;
    int last = 0;
    long long ans = 0;
    (ans += calc_3(x)) %= mod;
    debug<<"inital ans = "<<ans<<endl;
    for(int i=2;i<=x;i=last+1) {
        last = x/(x/i);
        (ans += mod-(LL)calc(x/i)*calc_2(i,last)%mod) %= mod;
    }
    add(x, ans);
    return ans;
}

int main() {
    init();
    int n;
    cin >> n;
    puts("1");
    cout << calc(n) << endl;
}
