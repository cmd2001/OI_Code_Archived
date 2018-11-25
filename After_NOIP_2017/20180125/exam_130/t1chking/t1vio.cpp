#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1e5+1e2;

int mi[maxn],mx[maxn];
int n;

inline int dfs(int pos,int rem) {
    if( pos == n + 1 && rem == 0 ) return 0;
    if( pos == n + 1 && rem ) return inf;
    int ret = mi[pos] + dfs(pos+1,rem);
    if( rem ) ret = min( ret , -mx[pos] + dfs(pos+1,rem-1) );
    return ret;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d%d",mi+i,mx+i);
        if( mi[i] > mx[i] ) swap(mi[i],mx[i]);
    }
    printf("%d\n",dfs(1,n>>1));
    
    return 0;
}