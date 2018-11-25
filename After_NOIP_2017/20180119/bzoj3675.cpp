#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
 
int que[maxn],st,ed;
lli in[maxn],f[2][maxn];
int n,k,cur;
 
inline long double slop(int k,int j) {// assert k <= j .
    return (long double)(f[cur^1][j]-f[cur^1][k]) / (long double)(in[j]-in[k]);
}
inline void init(int x) {
    memset(que,0,sizeof(que));
    memset(f[cur],0,sizeof(f[1]));
    que[ st = ed = 1 ] = x;
}
int main() {
    scanf("%d%d",&n,&k); k++;
    for(int i=1;i<=n;i++) {
        scanf("%lld",in+i);
        if( !in[i] ) --i,--n;
        else in[i] += in[i-1];
    }
    k = min( k , n );
    for(int i=1;i<=n;i++)
        f[cur][i] = ( in[n] - in[i] ) * in[i];
    for(int T=2;T<=k;T++) {
        cur ^= 1 , init(T-1);
        for(int i=T;i<=n;i++) {
            while( st < ed && slop(que[st],que[st+1]) > in[n] - in[i] ) ++st;
            f[cur][i] = f[cur^1][que[st]] + ( in[n] - in[i] ) * ( in[i] - in[que[st]] );
            while( st < ed && slop(que[ed-1],que[ed]) < slop(que[ed],i) ) --ed;
            que[++ed] = i;
        }
    }
     
    printf("%lld\n",f[cur][n]);
     
    return 0;
}