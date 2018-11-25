#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int dit[100010],rel[100010],sum[100010],fa[100010],qu[100010],ans[100010];
int find(int x)
{
if(fa[x]==x)
{
return x;
}
else
{
fa[x]=find(fa[x]);
return fa[x];
}
}
int main()
{
int n,m,i,a,b,fz,faa,cnt=0;
char s[5];
sum[1]=1000001;
scanf("%d%d",&n,&m);
for(i=1;i<=n;i++)
{
scanf("%d%d",&a,&b);
rel[b]=a;
}
for(i=1;i<=m;i++)
{
scanf("%s%d",s,&a);
dit[i]=a;
if(s[0]=='C')//change
{
qu[i]=1;
sum[a]++;
}
else//find
{
qu[i]=2;
}
}
for(i=0;i<=100009;i++)
{
fa[i]=i;
}
for(i=m;i>=1;i--)
{
if(qu[i]==1)//change
{
sum[dit[i]]--;
if(sum[dit[i]]==0)
{
fa[dit[i]]=rel[dit[i]];
}
}
else//find
{
fz=dit[i];
while(1)
{
faa=find(fz);
if(sum[faa]==0)
{
fa[faa]=rel[faa];
}
else
{
break;
}
}
cnt++;
ans[cnt]=faa;
}
}
for(i=cnt;i>=1;i--)
{
printf("%d\n",ans[i]);
}
return 0;
}
