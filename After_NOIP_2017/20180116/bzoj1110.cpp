#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],b[maxn],nums[32],ns[32],cnt[32],siz,ans;

inline bool getbit(int x) {
    if( x >= siz ) return 0;
    if( !cnt[x+1] )
        getbit(x+1);
    if( cnt[x+1] ) {
        --cnt[x+1] , cnt[x] += nums[x+1] / nums[x];
        return 1;
    }
    return 0;
}

inline void cut(int x) {
    for(int i=siz;i;i--) {
        cnt[i] += x / nums[i] ,
        x %= nums[i];
    }
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",b+i);
    for(int i=1;i<=m;i++)
        scanf("%d",in+i);
    
    sort(in+1,in+1+m);
    for(int i=1;i<=m;i++) {
        if( in[i] != in[i-1] )
            nums[++siz] = in[i];
        ++ns[siz];
    }
    //for(int i=1;i<=siz;i++) debug<<ns[i]<<" ";debug<<endl;
    for(int i=1;i<=n;i++)
        cut(b[i]);
    //for(int i=1;i<=siz;i++) debug<<cnt[i]<<" ";debug<<endl;
    
    for(int i=1;i<=siz;i++) {
        while( ns[i] ) {
            if( !cnt[i] && !getbit(i) ) break;
            int d = min( cnt[i] , ns[i] );
            //debug<<"i = "<<i<<"d = "<<d<<endl;
            ans += d , ns[i] -= d , cnt[i] -= d;
        }
    }
    
    printf("%d\n",ans);
    
    return 0;
}