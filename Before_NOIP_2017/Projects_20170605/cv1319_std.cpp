#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long LL;

using namespace std;

const int Maxn = 50010;

int q[Maxn],n,l,c;
LL a[Maxn],dp[Maxn],g[Maxn];

double Slope(int k,int j){//斜率公式
    return (  (dp[j] + g[j]*g[j] + 2 * c * g[j])  -  (dp[k] + g[k] * g[k] + 2 * c * g[k] )  ) / (2.0* (g[j] - g[k]) );
}

int main(){
    scanf("%d%d",&n,&l);c = l + 1;
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        g[i] = g[i-1] + a[i];
    }
    for(LL i=1;i<=n;i++)g[i] += i;
    int h = 1,t = 0;q[++t] = 0;
    for(int i=1;i<=n;i++){//维护单调队列
        while(h < t && Slope(q[h],q[h+1]) <= g[i])h++;
        int w = q[h];//从队首取出答案
        dp[i] = dp[w] + (g[i] - g[w] - (LL)c) * (g[i] - g[w] - (LL)c);
        while(h < t && Slope(q[t],i) < Slope(q[t-1],q[t]))t--;
        q[++t] = i;//维护下凸性并加入i点
    }printf("%lld\n",dp[n]);
    // while(1);
    return 0;
}
