#include<cstdio>
#include<algorithm>
#include<set>
#define ulli unsigned long long int
using namespace std;
const int maxn=1e5+1e2;

ulli h[maxn],rms[maxn];
int bel[maxn],siz[maxn];
set<ulli> app;
set<int> at;

inline ulli _rand() {
    return ( (ulli) rand() << 32 ) + ( (ulli) rand() << 16 ) + (ulli) rand();
}
inline void pre(int n) {
    for(int i=1;i<=n;i++) rms[bel[i]=1] ^= ( h[i] = _rand() ), ++siz[1];
    at.insert(1);
}
int main() {
    static int n,m,q;
    static char o[10];
    scanf("%d%d%d",&n,&m,&q) , pre(n);
    for(int i=1,x,y;i<=q;i++) {
        scanf("%s%d%d",o,&x,&y);
        if( *o == 'C' ) {
            --siz[bel[x]] , ++siz[y];
            rms[bel[x]] ^= h[x] , rms[y] ^= h[x];
            at.erase(bel[x]) , at.erase(y);
            if( app.find(rms[bel[x]]) == app.end() ) at.insert(bel[x]);
            if( app.find(y) == app.end() ) at.insert(y);
            bel[x]  = y; 
        } else {
            int ans = 0;
            for(set<int>::iterator it=at.lower_bound(x);it!=at.end()&&*it<=y;) {
                const int r = *it;
                if( app.find(rms[r]) == app.end() ) app.insert(rms[r]) , ans += siz[r];
                at.erase(it),it=at.lower_bound(x);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
