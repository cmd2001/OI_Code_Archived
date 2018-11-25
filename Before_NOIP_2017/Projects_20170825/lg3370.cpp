#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdio>
#define lli long long int

const int mod1=233333,mod2=1000007,mod3=1000009;
const int base1=31,base2=47,base3=59;
bool vis1[mod1+10],vis2[mod2+10],vis3[mod3+10];
int n,ans;
char in[1510];

inline lli hash(char* dst,int base,int mod)
{
	lli ret=0;
	int l=strlen(dst);
	
	for(int i=0;i<l;i++)
	{
		ret=ret*base+dst[i];
		ret%=mod;
	}
	
	return ret;
}

inline void test()
{
	int add=1,h;
	h=hash(in,base1,mod1);
	add&=vis1[h];
	vis1[h]=1;
	h=hash(in,base2,mod2);
	add&=vis2[h];
	vis2[h]=1;
	h=hash(in,base3,mod3);
	add&=vis3[h];
	vis3[h]=1;
	if(!add) ans++;
}

int main()
{
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s",in);
		test();
	}
	
	printf("%d\n",ans);
	
	return 0;
}
	
	

