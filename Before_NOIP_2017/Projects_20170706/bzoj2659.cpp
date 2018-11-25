#include<cstdio>

long long int p,q,ans;

int main()
{
	scanf("%lld%lld",&p,&q);
	
	if(p!=q) ans=(p-1)*(q-1)>>2;
	else ans=(p-1)*(q+1)>>2;
	
	printf("%lld\n",ans);
	
	return 0;
}
