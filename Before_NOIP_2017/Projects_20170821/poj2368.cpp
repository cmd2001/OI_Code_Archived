#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e4+1e2;

long long int k,len,solved;
long long int dat[maxn];

int main()
{
	while(scanf("%lld",&k)==1)
	{
		
		len=solved=0;
		for(long long int i=1;i*i<=k;i++)
		{
			if(!(k%i))
			{
				dat[++len]=i;
				dat[++len]=k/i;
			}
		}
		
		sort(dat+1,dat+1+len);
		
		for(int i=1;i<=len;i++)
		{
			if(dat[i]>2)
			{
				printf("%lld\n",dat[i]-1);
				solved=1;
				break;
			}
		}
		
		if(!solved) puts("0");
		
	}
	return 0;
}
