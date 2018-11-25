#include<cstdio>
#include<iostream>
using namespace std;
int num[100001],sum[100001],l[200001],r[200001];
int n,b,point,ans;
int main()
{
	scanf("%d%d",&n,&b);
	for(int i=1;i<=n;i++)
    {
    	scanf("%d",&num[i]);
    	if(num[i]>b)num[i]=1;
    	else if(num[i]==b){num[i]=0;point=i;}
    	else num[i]=-1;
    }
    l[n]=1;r[n]=1;
    for(int i=point-1;i>=1;i--)
       {sum[i]=sum[i+1]+num[i];l[sum[i]+n]++;}
    for(int i=point+1;i<=n;i++)
       {sum[i]=sum[i-1]+num[i];r[sum[i]+n]++;}
    for(int i=0;i<=2*n-1;i++)ans+=l[i]*r[2*n-i];
    printf("%d",ans);
	return 0;
}
