#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=10000;
const int prime[14]={2,3,5,7,11,13,19,17,23,29,31,37,41};
const int cas=10;

inline long long mul(long long a,long long b,long long p){
	a%=p;
	b%=p;
	long long ret=0;
	while(b){
		if (b&1) ret=(ret+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	return ret;
    // long long tmp=(a*b-(long long)((long double)a/p*b+1e-8)*p);
    // return tmp<0?tmp+p:tmp;
}

inline long long pow(long long a,long long b,long long p){
	a%=p;
	long long ret=1;
	while(b){
		if (b&1) ret=mul(ret,a,p);
		a=mul(a,a,p);
		b>>=1;
    }
	return ret;
}

inline bool miller(long long a){
	for (int i=0;i<cas;i++){
		if (prime[i]==a) return true;
		long long k=a-1;
		while(~k&1) k>>=1;
		long long rr=pow(prime[i],k,a),kk;
		if (rr==1) continue;
		if (k==a-1) return false;
		for(;;){
			kk=rr;
			rr=mul(rr,rr,a);
			if (rr==a-1) break;
			if (rr==1){
				if (kk!=a-1) return false;
				break;
			}
			k<<=1;
			if (k==a-1) return false;
		}
	}
	return true;
}

inline long long get(long long n){
	return ((long long)rand()<<15^rand()<<15^rand())%n;
}

long long gcd(long long a,long long b){
	if (a==0||b==0) return a+b;
	do{
		swap(a,b);
		b%=a;
	}while(b);
	return a;
}

inline long long fj(long long n,long long c){
	long long y,x;
	do{y=get(n);}while(y==c);
	x=y;
	for(;;){
		x=(mul(x,x,n)+mul(x,13,n)+c)%n;
		x=(mul(x,x,n)+mul(x,13,n)+c)%n;
		y=(mul(y,y,n)+mul(y,13,n)+c)%n;
		if (x==y) return n;
		long long g=(x>y)?gcd(x-y,n):gcd(y-x,n);
		if (g>1&&g<n) return g;
	}
}

long long rec[1000];
int tot;
void solve(long long n){
	if (n==1) return;
	if (miller(n)){
		rec[++tot]=n;
		return;
	}
	long long p=fj(n,get(n));
	while(p>=n) p=fj(n,get(n));
	solve(p);
	solve(n/p);
	return;
}

int main(){
#define debug cout
	freopen("dat.txt","r",stdin);
	freopen("std.txt","w",stdout);
	int t=0;
	scanf("%d",&t);
	long long n;
	while(t--){
		scanf("%lld",&n);
		tot=0;
		solve(n);
		long long ans=1;
		sort(rec+1,rec+tot+1);
		for (int i=1;i<=tot;++i){
			if (rec[i]!=rec[i-1]) ans*=rec[i]-1;
			else ans*=rec[i];
		}
		cout<<ans<<endl;
	}
	return 0;
}
