#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2,maxl=27;

struct node
{
	char str[maxn];
	int len,id;
	
	void in()
	{
		scanf("%s",str);
		len=strlen(str);
	}
	char& operator [] (const int &p)
	{
		return str[p-1];
	}
	friend bool operator < (const node &a,const node &b)
	{
		return memcmp(a.str,b.str,sizeof(a.str)) < 0;
	}
}in[maxn];

int n;
short int cov[maxn],f[maxn];

inline int calc(int x,int y)
{
	int lim=min(in[x].len,in[y].len);
	
	for(int i=1;i<=lim;i++)
		if(in[x][i]!=in[y][i]) return i;
	
	return lim+1;
}

int main()
{
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
	{
		in[i].id=i;
		in[i].in();
	}
	
	sort(in+1,in+1+n);
	for(int i=1;i<=n;i++)
		cov[in[i].id]=i;
	
	for(int i=1;i<=n;i++)
	{
		int flast,fnext;
		if(i==1) flast=1;
		else flast=calc(i-1,i);
		if(i==n) fnext=1;
		else fnext=calc(i,i+1);
		f[i]=max(fnext,flast);
	}
	
		
	
	for(int i=1;i<=n;i++)
	{
		const int &pos=cov[i];
		for(int j=1;j<=f[pos];j++) putchar(in[pos][j]);
		putchar('\n');
	}
	
	return 0;
}
	
