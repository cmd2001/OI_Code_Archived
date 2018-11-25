#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <algorithm>  
  
using namespace std;  
  
const int maxn=99000;  
  
int sa[maxn],rk[maxn],rk2[maxn],h[maxn],c[maxn];  
int *x,*y,ans[maxn];  
char str[maxn];  
  
bool cmp(int*r,int a,int b,int l,int n)  
{  
    if(r[a]==r[b]&&a+l<n&&b+l<n&&r[a+l]==r[b+l])  
        return true;  
    return false;  
}  
  
void radix_sort(int n,int sz)  
{  
    for(int i=0;i<sz;i++) c[i]=0;  
    for(int i=0;i<n;i++) c[x[y[i]]]++;  
    for(int i=1;i<sz;i++) c[i]+=c[i-1];  
    for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];  
}  
  
void get_sa(char c[],int n,int sz=128)  
{  
    x=rk,y=rk2;  
    for(int i=0;i<n;i++)  
        x[i]=c[i],y[i]=i;  
    radix_sort(n,sz);  
    for(int len=1;len<n;len=len*2)  
    {  
        int yid=0;  
        for(int i=n-len;i<n;i++)  
            y[yid++]=i;  
        for(int i=0;i<n;i++)  
            if(sa[i]>=len)  
                y[yid++]=sa[i]-len;  
  
        radix_sort(n,sz);  
  
        swap(x,y);  
        x[sa[0]]=yid=0;  
  
        for(int i=1;i<n;i++)  
            x[sa[i]]=cmp(y,sa[i],sa[i-1],len,n)?yid:++yid;  
  
        sz=yid+1;  
        if(sz>=n) break;  
    }  
    for(int i=0;i<n;i++)  
        rk[i]=x[i];  
}  
  
void get_h(char str[],int n)  
{  
    int k=0; h[0]=0;  
    for(int i=0;i<n;i++)  
    {  
        if(rk[i]==0) continue;  
        k=max(k-1,0);  
        int j=sa[rk[i]-1];  
        while(i+k<n&&j+k<n&&str[i+k]==str[j+k])  
            k++;  
        h[rk[i]]=k;  
    }  
}  
  
int sum[maxn];  
  
int main()  
{  

    freopen("dat.txt","r",stdin);
    freopen("std.txt","w",stdout);
    scanf("%s",str);  
    int n=strlen(str);  
    get_sa(str,n);  
    get_h(str,n);  
  
    for(int i=0;i<n;i++)  
    {  
        sum[i]=n-sa[i]-h[i];  
        if(i-1>=0) sum[i]+=sum[i-1];  
    }  
  
    int T_T;  
    scanf("%d",&T_T);  
    while(T_T--)  
    {  
        int x;  
        scanf("%d",&x);  
        int low=0,high=n-1,ans,mid;  
        while(low<=high)  
        {  
            mid=(low+high)/2;  
            if(sum[mid]>=x)  
                ans=mid,high=mid-1;  
            else if(sum[mid]<x) low=mid+1;  
            else break;  
        }  
        int t=(ans==0)?0:sum[ans-1];  
        for(int i=0;i<h[ans];i++)  
            putchar(str[sa[ans]+i]);  
        for(int i=0;i<x-t;i++)  
            putchar(str[sa[ans]+h[ans]+i]);  
        putchar(10);  
    }  
    return 0;  
}  
