#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=1e6+1e2;

int in[maxn],w[maxn],tp[maxn],n,len,ans;
int que[maxn],st=1,ed;

int main() {
    scanf("%d",&n) , len = ( n + 1 ) >> 1 , memset(tp,0x3f,sizeof(tp));
    for(int i=1;i<=n;i++) scanf("%d",in+i) , in[i+n] = in[i];
    for(int i=1;i<=n<<1;i++) in[i] += in[i-1];
    for(int i=1;i<=(n<<1)-len+1;i++) w[i] = in[i-1+len] - in[i-1];
    for(int i=1;i<=n<<1;i++) {
        if( i <= (n<<1)-len+1 ) {
            while( st <= ed &&  w[i] <= w[que[ed]] ) --ed;
            que[++ed] = i;
        }
        while( st < ed && que[st] <= i - len ) ++st;
        if( st <= ed ) tp[i<=n?i:i-n] = std::min( tp[i<=n?i:i-n] , w[que[st]] );
    }
    for(int i=1;i<=n;i++) ans = std::max( ans , tp[i] );
    printf("%d\n",ans);
    return 0;
}