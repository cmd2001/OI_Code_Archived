#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],n,k,ans;

inline int calc(int l,int r) {
    static int dat[maxn],len;
    int ret = inf; len = 0;
    for(int i=l;i<=r;i++) dat[++len] = in[i];
    sort(dat+1,dat+1+len);
    for(int i=1;i<len;i++) ret = min( ret , dat[i+1] - dat[i] );
    return ret;
}

int main() {
    scanf("%*d");
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    for(int st=1;st<n;st++) for(int ed=st+1;ed<=n;ed++) if( ed - st + 1 >= k ) ans = max( ans , ( ed - st ) * calc(st,ed) );
    printf("%d\n",ans);
    return 0;
}