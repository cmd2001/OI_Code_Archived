#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<map>
#include<set>
#include<algorithm>
#include<queue>
#include<time.h>
#include<iostream>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define fe(x) for(int ii=be[x];ii;ii=e[ii].ne)
#define debug cout
using namespace std;
const int mn=200000;
int p,pri[mn/10],pt,mm;
long long n,p2,p6,ans,g[mn+20],mg[100000];
bool vis[100000],isp[mn+20];
inline long long qpow(int a,int n){
    long long x=a,ans=1;
    while (n){
        if (n&1) ans=ans*x%p;
        x=x*x%p;
        n>>=1;
    }
    return ans;
}
inline long long sum2(long long n){
    n%=p;
    return (n+n+1)%p*(n+1)%p*n%p*p6%p;
}
inline long long sum3(long long n){
    n%=p;
    n=n*(n+1)%p*p2%p;
    return n*n%p;
}
inline long long G(long long x){
    if (x<=mm) return g[x];
    int ms=n/x;
    if (vis[ms]) return mg[ms];
   // debug<<"x = "<<x<<"ms = "<<ms<<endl;
    vis[ms]=1;
    long long i=2,j,te;
    long long &ans=mg[ms];
    ans=sum3(x);
    //debug<<"inital ans = "<<ans<<endl;
    while (i<=x){
        te=x/i;
        j=x/te;
        ans-=(sum2(j)-sum2(i-1))*G(te)%p;
        i=j+1;
    }
    return ans%=p;
}
int main(){
    scanf("%d%lld",&p,&n);
    mm=mn;if (n<mm) mm=n;
    g[1]=1;
    fo(i,2,mm){
        if (!isp[i]){
            g[i]=i-1;
            pri[++pt]=i;
        }
        fo(j,1,pt){
            long long te=i*(long long)pri[j];
            if (te>mn) break;
            isp[te]=1;
            if (i%pri[j]==0){
                g[te]=g[i]*pri[j];
                break;
            }
            g[te]=g[i]*(pri[j]-1);
        }
    }
    fo(i,2,mm) g[i]=(g[i-1]+g[i]*i%p*i)%p;
    p2=qpow(2,p-2);p6=qpow(6,p-2);
    long long i=1,j,te;
    while (i<=n){
        te=n/i;
        j=n/te;
        ans+=(sum3(j)-sum3(i-1))*G(te)%p;
        i=j+1;
    }
    ans=(ans%p+p)%p;
    printf("%lld\n",ans);
    return 0;
}
