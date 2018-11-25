#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;
int in[maxn],cnt[2][3],sum[3],m[3],state,n,ans,ans2;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&in[i]);
    for(int i=1;i<=n;i++) sum[in[i]]++;
    for(int i=0;i<3;i++) m[i]=sum[i]>>1;
    state=0;
    for(int i=1;i<=n;i++)
    {
        if(cnt[state][in[i]]+1<=m[in[i]]) cnt[state][in[i]]++;
        else state^=1,++ans;
    }
    reverse(in+1,in+1+n);memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++)
    {
        if(cnt[state][in[i]]+1<=m[in[i]]) cnt[state][in[i]]++;
        else state^=1,++ans2;
    }
    printf("%d\n",min(ans,ans2));
    return 0;
}
