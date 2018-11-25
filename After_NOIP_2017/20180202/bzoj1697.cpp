#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define lli long long int
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
const int inf=0x3f3f3f3f;

map<lli,int> mp;
lli in[maxn],srt[maxn],sum,len,mi,omi,ans;
int tim[maxn];
int n;

inline void gen() {
    memcpy(srt,in,sizeof(lli)*(n+1));
    sort(srt+1,srt+1+n);
    for(int i=1;i<=n;i++)
        mp[srt[i]] = i;
}
inline void dfs(int pos,const int &t,lli& sum,lli& len,lli& mi) {
    if( tim[pos] ) return;
    tim[pos] = t;
    sum += in[pos] , ++len , mi = min( mi , in[pos] );
    dfs(mp[in[pos]],t,sum,len,mi);
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",in+i);
    gen() , omi = srt[1];
    for(int i=1;i<=n;i++)
        if( !tim[i] && mp[in[i]] != i ) {
            sum = len = 0 , mi = inf;
            dfs(i,i,sum,len,mi);
            ans += min( sum + mi * ( len - 2 ) , sum + mi + omi * ( len + 1 ) );
        }
    printf("%lld\n",ans);
    return 0;
}

