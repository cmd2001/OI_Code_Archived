#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int sum[20],len[20],eles[20][20];
int lim[maxn],num[maxn];
int n,m,t,ans;

inline bool judge() {
    for(int i=1;i<=m;i++) {
        int ss = 0;
        for(int j=1;j<=len[i];j++)
            ss += num[eles[i][j]];
        if( ss != sum[i] )
            return 0;
    }
    return 1;
}

inline void dfs(int pos) {
    //debug<<"pos = "<<pos<<endl;
    if( pos > n ) {
        ans += judge();
        return;
    }
    for(int i=0;i<=lim[pos];i++) {
        num[pos] = i;
        dfs(pos+1);
    }
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) {
        scanf("%d",len+i);
        for(int j=1;j<=len[i];j++)
            scanf("%d",eles[i]+j);
        scanf("%d",sum+i);
        for(int j=1;j<=len[i];j++)
            lim[eles[i][j]] = sum[i];
    }
    scanf("%d",&t);
    for(int i=1,r,L;i<=t;i++) {
        scanf("%d%d",&r,&L);
        lim[r] = L;
    }
    
    dfs(1);
    
    printf("%d\n",ans);
    
    return 0;
}
