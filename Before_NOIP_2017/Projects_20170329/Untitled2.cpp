#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=15100;
char s[maxn];
int sa[maxn],t[maxn],t2[maxn],c[maxn],n;
int out[maxn];
void build(int m)
{
    int *x=t,*y=t2;
    for(int i=0;i<m;i++) c[i]=0;
    for(int i=0;i<n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<m;i++) c[i]+=c[i-1];
    for(int i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=n-1;i>=n-k;i--) y[p++]=i;
        for(int i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
        for(int i=0;i<m;i++) c[i]=0;
        for(int i=0;i<n;i++) c[x[y[i]]]++;
        for(int i=1;i<m;i++) c[i]+=c[i-1];
        for(int i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(int i=1;i<n;i++) x[sa[i]]=(y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++);
        if(p>=n) break;
        m=p;
    }
}
int main()
{
	scanf("%d",&n);
    scanf("%s",s);
    for(int i=0;i<n;i++) s[i]-='a';
    build(26);
    for(int i=0;i<n;i++) printf("%d\n",sa[i]+1);
    return 0;
    
}

