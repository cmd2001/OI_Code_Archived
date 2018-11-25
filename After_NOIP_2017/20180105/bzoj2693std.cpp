#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define SF scanf
#define PF printf
#define MAXN 10000010
#define MAXPRIME  10000000
#define MOD 100000009
using namespace std;
int mu[MAXN],isprime[MAXN];
vector<int> primes;
long long sum[MAXN];
void prepare(){
    mu[1]=1;
    sum[1]=1;
    for(long long i=2;i<=MAXPRIME;i++){
        if(isprime[i]==0){
            primes.push_back(i);
            mu[i]=-1;
            sum[i]=-i*i+i;
        }
        sum[i]%=MOD;
        //PF("(%I64d)\n",sum[i]);
        for(int j=0;j<primes.size()&&i*primes[j]<=MAXPRIME;j++){
            isprime[primes[j]*i]=1;
            if(i%primes[j]==0){
                sum[i*primes[j]]=(primes[j]*sum[i])%MOD;
                break;
            }
            mu[i*primes[j]]=-mu[i];
            sum[i*primes[j]]=(sum[i]*sum[primes[j]])%MOD;
        }
    }
    for(int i=1;i<=MAXPRIME;i++){
        sum[i]+=sum[i-1];
        sum[i]%=MOD;   
    }
}
int t;
long long n,m;
long long s(long long x){
    return ((x*(x+1))/2)%MOD;
}
int main(){
    prepare();
    SF("%d",&t);
    while(t--){
        SF("%I64d%I64d",&n,&m);
        long long last=0,res=0;
        for(long long i=1;i<=min(n,m);i=last+1){
            last=min(n/(n/i),m/(m/i));
            res+=((s(n/i)*s(m/i))%MOD*(sum[last]-sum[i-1]+MOD+MOD))%MOD;
            //PF("(%lld %lld)",last,res);
            res%=MOD;
        }
        PF("%lld\n",res);
    }
}