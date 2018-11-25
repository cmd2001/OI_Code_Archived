#include<bits/stdc++.h>
using namespace std;
const int maxn=2e7+1e2;
int prime[maxn],cnt;
bool vis[maxn];
void get_prime(int n)
{
    int j;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) prime[++cnt]=i;
        for(j=1;j<=cnt&&i%prime[j]&&i*prime[j]<=n;j++) vis[i*prime[j]]=1;
        if(i*prime[j]<=n) vis[i*prime[j]]=1;
    }
}
void putint(int x)
{
    int num=0;
    char c[15];
    while(x) c[++num]=x%10+48,x/=10;
    while(num) putchar(c[num--]);
    putchar(' ');
}
int main()
{
    freopen("test.txt","w",stdout);
    int n;
    scanf("%d",&n);
    get_prime(n);
    for(int i=1;i<=cnt;i++) putint(prime[i]);
    return 0;
}
