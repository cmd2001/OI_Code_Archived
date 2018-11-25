#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],at[maxn],midis[maxn],son[maxn],f[maxn]; // > 0 means up , < 0 means down .
int n,m,ans;

inline void maintain(int pos) { // only consider in[pos] .
    if( in[pos] ) midis[pos] = 0 , son[pos] = pos;
    else midis[pos] = inf , son[pos] = -1;
}
inline void fix(int pos) { // fix dat of pos using dat of sons of pos .
    #define cst(pos) ( f[pos] > 0 ? -1 : 1 )
    maintain(pos);
    const int ls = pos << 1 , rs = pos << 1 | 1;
    if( ls <= n && midis[ls] != inf && midis[pos] > midis[ls] + cst(ls) ) midis[pos] = midis[ls] + cst(ls) , son[pos] = son[ls];
    if( rs <= n && midis[rs] != inf && midis[pos] > midis[rs] + cst(rs) ) midis[pos] = midis[rs] + cst(rs) , son[pos] = son[rs];
}
inline void add_f(int pos,int lca) {
    while( pos != lca ) ++f[pos] , pos >>= 1;
}
inline void sub_f(int pos,int lca) {
    while( pos != lca ) --f[pos] , pos >>= 1;
}
inline void fix_chain(int pos) {
    fix(pos);
    if( pos != 1 ) fix_chain(pos>>1);
}
inline void findtar(int pos,int &tar,int &dis,int &lca) {
    int cost = 0; tar = -1 , dis = inf;
    while(pos) {
        if( midis[pos] + cost < dis ) dis = midis[pos] + cost , tar = son[pos] , lca = pos;
        cost += f[pos] < 0 ? -1 : 1 , pos >>= 1;
    }
}


int main() {
    scanf("%d%d",&n,&m) , memset(midis,0x3f,sizeof(midis)) , memset(son,-1,sizeof(son));
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int i=1;i<=m;i++) scanf("%d",at+i);
    for(int i=n;i;i--) fix(i);
    for(int i=1,tar,dis,lca;i<=m;i++) {
        tar = -1 , findtar(at[i],tar,dis,lca) , ans += dis;
        assert(~tar);
        --in[tar] , add_f(at[i],lca) , sub_f(tar,lca) , fix_chain(at[i]) , fix_chain(tar);
        printf("%d",ans);
        if( i != m ) putchar(' ');
    }
    return 0; 
}
