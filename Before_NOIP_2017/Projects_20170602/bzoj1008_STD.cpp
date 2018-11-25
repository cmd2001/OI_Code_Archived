#include <cstdio>  
#define ll long long  
int const MOD = 100003;  
   
ll qpow(ll x, ll n)  
{  
    ll ans = 1;  
    while(n)  
    {  
        if(n & 1)  
            ans = (ans * x) % MOD;  
        x = (x * x) % MOD;  
        n >>= 1;  
    }  
    return ans;  
}  
   
int main()  
{  
    ll m, n;  
    scanf("%lld %lld", &m, &n);  
    printf("%lld\n", (MOD + qpow(m, n) % MOD - m * qpow(m - 1, n - 1) % MOD) % MOD);  
}  
