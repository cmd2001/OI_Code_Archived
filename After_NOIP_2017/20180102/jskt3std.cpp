#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <algorithm>  
#include <vector>  
using namespace std;  
#define maxn 240080  
#define inf 0x3f3f3f3f  
#define LL long long int
#define debug cout  
int str[maxn],vis[maxn];  
char s[maxn];  
int sa[maxn],t[maxn],t2[maxn],c[maxn],key[maxn];  
int height[maxn],Rank[maxn];  
int len1,len2;  
int Min[maxn][20],lca[maxn][20];  
LL dp[maxn];  
inline int max(int a,int b)  
{  
    return a>b?a:b;  
}  
/* 
用SA模板注意在最后添加一个比所有字符都小的字符。 
key[n] = 0; 
build_sa(key,n+1,m); 
getHeight(key,n+1); 
显然sa[0] 就是最后那个位置。。。 
height[i] 表示 sa[i] 和 sa[i-1] 的最长公共前缀。。 
*/  
  
void build_sa(int * s,int n,int m)  
{  
    int i,*x = t,*y = t2;  
    for(i = 0;i < m;i++)    c[i] = 0;  
    for(i = 0;i < n;i++)    c[ x[i] = s[i] ]++;  
    for(i = 1;i < m;i++)    c[i] += c[i-1];  
    for(i = n-1;i >= 0;i--)    sa[--c[x[i]]] = i;  
    for(int k = 1;k <= n;k <<= 1)  
    {  
        int p = 0;  
        for(i = n - k;i < n;i++)    y[p++] = i;  
        for(i = 0;i < n;i++)    if(sa[i] >= k)    y[p++] = sa[i] - k;  
        for(i = 0;i < m;i++)    c[i] = 0;  
        for(i = 0;i < n;i++)    c[ x[y[i]] ]++;  
        for(i = 0;i < m;i++)    c[i] += c[i-1];  
        for(i = n-1;i >= 0;i--)    sa[--c[x[y[i]]]] = y[i];  
        //根据sa和y数组计算新的数y组  
        swap(x,y);  
        p = 1;    x[sa[0]] = 0;  
        for(i = 1;i < n;i++)  
            x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1] + k] == y[sa[i] + k] ? p-1:p++;  
        if(p >= n)    break;  
        m = p;  
    }  
}  
  
void getHeight(int * s,int n)  
{  
    int i,j,k = 0;  
    for(i = 0;i < n;i++)    Rank[sa[i]] = i;  
    for(i = 0;i < n;i++)      
    {  
        if(k) k--;  
        int j = sa[Rank[i]-1];  
        while(s[i+k] == s[j+k])        k++;  
        height[Rank[i]] = k;  
    }  
}  
  
void RMQ_INIT(int n)//求lca  
{  
    for(int i = 1;i < n;i++)    lca[i][0] = height[i];  
    for(int j = 1;(1<<j)<=n;j++)  
    {  
        for(int i = 0;i+(1<<j)-1<n;i++)  
        {  
            lca[i][j] = min(lca[i][j-1],lca[i+(1<<(j-1))][j-1]);  
        }  
    }  
}  
  
int RMQ_Query(int l,int r)  
{  
    int k = 0;  
    while((1<<(k+1) <= r-l+1)) k++;  
    return min(lca[l][k],lca[r-(1<<k)+1][k]);  
}  
void RMQ_INIT1(int n)//求区间最小,这是求出sa后求得  
{  
    for(int i = 1;i < n;i++)    key[i] = sa[i]+1;  
    for(int i = 1;i < n;i++)    Min[i][0] = key[i];  
    for(int j = 1;(1<<j)<=n;j++)  
    {  
        for(int i = 0;i+(1<<j)-1<n;i++)  
        {  
            Min[i][j] = min(Min[i][j-1],Min[i+(1<<(j-1))][j-1]);  
        }  
    }  
}  
int RMQ_Query1(int l,int r)//  
{  
    int k = 0;  
    while((1<<(k+1)) <= r-l+1) k++;  
    return min(Min[l][k],Min[r-(1<<k)+1][k]);  
}  
int main()  
{  
   // freopen("in.txt","r",stdin);  
    while(scanf("%s",s)!=EOF)  
    {  
        int len = strlen(s);  
        for(int i = 0;i < len;i++)  
            str[i] = s[i]-'a'+2;  
        str[len] = 0;  
        build_sa(str,len+1,30);  
        getHeight(str,len+1);  
        dp[0] = 0;  
        dp[1] = len-sa[1];  
        for(int i = 2;i <= len;i++)  
        {  
            LL add = len-sa[i]-height[i];  
            dp[i] = dp[i-1] + add;  
        }  
        RMQ_INIT(len+1);  
        RMQ_INIT1(len+1);  
        LL l = 0,r = 0,v;  
        for(int i=1;i<=len;i++) debug<<sa[i]<<" ";debug<<endl;
        for(int i=1;i<=len;i++) debug<<height[i]<<" ";debug<<endl;
        for(int i=1;i<=len;i++) debug<<dp[i]<<" ";debug<<endl;
        int q;    scanf("%d",&q);  
        while(q--)  
        {  
            scanf("%lld",&v);  
            //LL k = (l^r^v)+1;  
            LL k = v;
            if(k > dp[len])  
            {  
                l = r = 0;  
                cout << 0 << " " << 0 << endl;  
                continue;  
            }  
            int pos = lower_bound(dp+1,dp+1+len,k)-dp;  
            debug<<"pos = "<<pos<<endl;
            debug<<"same strings = "<<height[pos]<<endl;
            //debug<<"pos-1 = "<<pos-1<<endl;
            debug<<"needed time = "<<k-dp[pos-1]<<endl;
            k -= dp[pos-1];  
            int L = sa[pos];  
            int R = L+k+height[pos]-1;////非常没问题  
            //这样从L 到 R就是所要求的字符串，但是还不是满足最小的序号的  
            int Len = R-L+1;  
            int ll = pos+1,rr = len;  
            int ans = pos;  
            while(ll <= rr)  
            {  
                int mid = (ll+rr)>>1;  
                if(RMQ_Query(pos+1,mid) < Len) rr = mid-1;  
                else   
                {  
                    ans = mid;  
                    ll = mid+1;  
                }  
            }  
            int fuck = RMQ_Query1(pos,ans);  
            l = fuck,r = fuck+Len-1;  
            printf("%lld %lld\n",l,r);  
        }  
    }  
    return 0;  
}  
