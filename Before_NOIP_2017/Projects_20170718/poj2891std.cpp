#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;
ll a[100005],r[100005];
int n;

ll exgcd(ll a,ll b,ll &x,ll &y){
    if(b==0) return x=1,y=0,a;
    ll tmp=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return tmp;
}

ll solve(){
    ll M=a[1],R=r[1],x,y,d;
    for(int i=2;i<=n;i++){
        d=exgcd(M,a[i],x,y);
        if((R-r[i])%d!=0) return -1;
        x=(R-r[i])/d*x%a[i];
        R-=x*M;
        M=M/d*a[i];
        R%=M;
        #define debug cout
        debug<<"R="<<R<<endl;
    }
    return (R%M+M)%M;
}

int main(){
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&r[i]);
        printf("%lld\n",solve());
    }
    return 0;
}
