#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
const int base=1000000000;

struct bignum
{
	int num[maxn],len;
	
	bignum(){}
	bignum(const char *s)
	{
		int strl=strlen(s),t,st,ed;
		len=strl/9;
		len+=(bool)(strl%9);
		for(int i=1;i<=len;i++)
		{
			t=0;
			ed=strl-(i-1)*9-1;
			st=max(strl-i*9,0);
			//debug<<"i="<<i<<"st="<<st<<"ed="<<ed<<endl;
			for(int k=st;k<=ed;k++) t=t*10+s[k]-'0';
			num[i]=t;
			//debug<<"i="<<i<<"num[i]="<<num[i]<<endl;
		}
			
		
	}
			
	void operator -= (const bignum &arg)
	{
		for(int i=1;i<=arg.len;i++)
		{
			num[i]-=arg.num[i];
			if(num[i]<0) num[i]+=base,num[i+1]--;
		}
		for(int i=arg.len+1;i<=len;i++)
			if(num[i]<0) num[i]+=base,num[i+1]--;
			else break;
		while(!num[len]) len--;
	}
	void operator *= (const int &x)
	{
		for(int i=1;i<=len;i++) num[i]*=x;
		for(int i=1;i<=len;i++)
		{
			num[i+1]+=num[i]/base;
			num[i]%=base;
		}
		while(num[len+1])
		{
			len++;
			num[len+1]+=num[len]/base;
			num[len]%=base;
		}
	}
	bool operator < (const bignum &arg)
	{
		if(arg.len>len) return 1;
		if(arg.len<len) return 0;
		for(int i=len;i;i--)
		{
			if(num[i]<arg.num[i]) return 1;
			if(num[i]>arg.num[i]) return 0;
		}
		return 0;
	}
	bool operator == (const bignum &arg)
	{
		if(len!=arg.len) return 0;
		for(int i=1;i<=len;i++) if(num[i]!=arg.num[i]) return 0;
		return 1;
	}
	
	bool judge()
	{
		if(!len) return 1;
		return !(num[1]&1);
	}
	void div()
	{
		for(int i=len;i>0;i--)
		{
			num[i-1]+=(num[i]&1)*base;
			num[i]>>=1;
		}
		while(!num[len]) len--;
	}
	
	void print()
	{
		printf("%d",num[len]);
		for(int i=len-1;i>0;i--) printf("%09d",num[i]);
		putchar('\n');
	}
}a,b;

char s[maxn];
int cnt=0;

int main()
{
	/*freopen("dat.txt","r",stdin);
	freopen("my.txt","w",stdout);*/ 
	scanf("%s",s);
	a=bignum(s);
	//a.print();
	scanf("%s",s);
	b=bignum(s);
	
	while(1)
	{
		
		while(a.judge()&&b.judge())
		{
			a.div();
			b.div();
			cnt++;
		}
		while(a.judge()) a.div();
		while(b.judge()) b.div();
		if(a==b) break;
		if(b<a) a-=b;
		else b-=a;
	}
	while(cnt--) a*=2;
	
	a.print();
	
	return 0;
}
	
		
