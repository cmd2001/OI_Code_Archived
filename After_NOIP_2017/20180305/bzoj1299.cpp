#include<cstdio>
const int maxn=20;

int in[maxn],n,can;

inline void dfs(int pos,int now,int sum) {
    if( pos > n ) {
        if( !now ) can |= sum;
        return;
    }
    dfs(pos+1,now,sum) ,
    dfs(pos+1,now^in[pos],sum+1);
}

int main() {
    static int T=10;
    while(T--) {
        scanf("%d",&n) , can = 0;
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        dfs(1,0,0);
        puts(can?"NO":"YES");
    }
    return 0;
}
