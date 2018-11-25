#include<cstdio>
#include<ctime>
#include<cstdlib>
long long inline lrand(){
	long long ans=rand();
	ans|=(long long)rand()<<15LL;
	ans|=(long long)rand()<<30LL;
	ans|=(long long)rand()<<45LL;
}
int main(){
	srand(time(0));
	freopen("data.in","w",stdout);
	long long n,p,k,r;
	n=1+lrand()%1000000000;
	k=1+lrand()%50;
	k=1;
	r=lrand()%k%n;
	p=lrand()%1000000000;
	printf("%lld %lld %lld %lld",n,p,k,r);



}
