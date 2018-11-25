#include<bits/stdc++.h>
#define debug cout
using namespace std;
typedef long long int lli;
const int mod=998244353;

inline lli fastpow(lli base,int tim) {
    lli ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

set<unsigned long long int> vis;
set<int> st;

int n,m,k,inv;

inline bool judge(const vector<int> &v) {
    unsigned long long int hsh = 0;
    for(unsigned i=0;i<v.size();i++) hsh = hsh * 27 + ( v[i] + 1 );
    if( vis.find(hsh) != vis.end() ) return 1; // found;
    return vis.insert(hsh),0;
}
inline void dfs(vector<int> v) {
    if( v.size() == 1 ) return void(st.insert(*v.begin()));
    sort(v.begin(),v.end());
    if( judge(v) ) return;
    do {
        lli su = 0;
        for(int i=0;i<k;i++) su += v[i];
        su = su * inv % mod;
        vector<int> nxt;
        for(unsigned i=k;i<v.size();i++) nxt.push_back(v[i]);
        nxt.push_back(su) , dfs(nxt);
    } while( next_permutation(v.begin(),v.end()));
}

int main() {
    scanf("%d%d%d",&n,&m,&k) , inv = fastpow(k,mod-2);
    if( !n || !m ) return puts("1") , fclose(stdout);
    vector<int> v;
    for(int i=1;i<=n;i++) v.push_back(0);
    for(int i=1;i<=m;i++) v.push_back(1);
    dfs(v) , printf("%d\n",(int)st.size());
    return 0;
}
