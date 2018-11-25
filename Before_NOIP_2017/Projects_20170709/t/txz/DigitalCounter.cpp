#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[20];
int shu[11]={6,2,5,5,4,5,6,3,7,5,6};
int next[11]={0,0,1,2,0,4,0,0,0,0};
int ans,sum,sum1;
char q[16];
void add(int x)
{
	a[x]++;
	if(a[x]==10)
	{
		a[x]=0;
		add(x-1);
	}
}
void find()
{
	sum1=0;
	for(int i=16-n;i<=15;i++) sum1+=shu[a[i]];
}
void qing()
{
	for(int i=1;i<=15;i++) a[i]=0;
}
int main()
{
	freopen("DigitalCounter.in","r",stdin);
	freopen("DigitalCounter.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",&q);
	for(int i=0;i<n;i++) a[16-n+i]=q[i]-48;
	if(next[a[15]]>0) cout<<next[a[15]]<<endl;
	else
	{
		for(int i=16-n;i<=15;i++) sum+=shu[a[i]];
		while(1)
		{
			ans++;
			add(15);
			if(a[16-n]!=0) qing();
			find();
			if(sum1==sum) break;
		}
		cout<<ans<<endl;
	}
	fclose(stdin);
	fclose(stdout);
}
/*
3
007

4
0099
*/
