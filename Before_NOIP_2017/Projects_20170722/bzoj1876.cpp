#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

struct bigint
{
	int num[maxn],len;
	bigint(void) {}
	bigint(const char* s)
	{
		//memset(num,0,sizeof(num));
		len=strlen(s);
		for(int i=len-1,j=1;i>=0;i--,j++)
		{
			num[j]=s[i]-'0';
		}
	}
	
	void operator *= (const int &x)
	{
		for(int i=1;i<=len;i++) num[i]*=x;
		for(int i=1;i<=len;i++) num[i+1]+=num[i]/10,num[i]%=10;
		while(num[len+1]) len++,num[len+1]+=num[len]/10,num[len]%=10;
	}
	friend bigint operator - (const bigint &a,const bigint &b)
	{
		bigint ret=a;
		for(int i=1;i<=a.len;i++)
		{
			ret.num[i]-=b.num[i];
			if(ret.num[i]<0) ret.num[i]+=10,ret.num[i+1]--;
		}
		while(!ret.num[ret.len]) ret.len--;
		return ret;
	}
	friend bool operator != (const bigint &a,const bigint &b)
	{
		if(a.len!=b.len) return 1;
		for(int i=1;i<=a.len;i++) if(a.num[i]!=b.num[i]) return 1;
		return 0;
	}
	friend bool operator < (const bigint &a,const bigint &b)
	{
		if(a.len<b.len) return 1;
		if(a.len>b.len) return 0;
		for(int i=a.len;i;i--)
		{
			if(a.num[i]<b.num[i]) return 1;
			if(a.num[i]>b.num[i]) return 0;
		}
		return 0;
	}
	bool judge()
	{
		return !(num[1]&1);
	}
	void div()
	{
		for(int i=len;i;i--)
		{
			num[i-1]+=(num[i]&1)*10;
			num[i]>>=1;;
		}
		while(!num[len]&&len) len--;
	}
	void print()
	{
		for(int i=len;i;i--) printf("%d",num[i]);
		putchar('\n');
	}
}a,b;

char s[maxn];
int cnt;
//int itr;

int main()
{
	scanf("%s",s);
	a=bigint(s);
	scanf("%s",s);
	b=bigint(s); 
	cnt=0;
	
	while(a!=b)
	{
		while(a.judge()&&b.judge())
		{
			a.div();
			b.div();
			cnt++;
		}
		while(a.judge()) a.div();
		while(b.judge()) b.div();
		if(!(a!=b)) break;
		if(b<a) a=a-b;
		else b=b-a;
		
	}
	while(cnt--) a*=2;
	
	a.print();
	
	return 0;
}
		
