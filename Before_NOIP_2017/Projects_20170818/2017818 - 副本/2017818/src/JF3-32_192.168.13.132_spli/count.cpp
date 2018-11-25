// by spli
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>
#define LL long long
using namespace std;

LL n,m;
struct Matrix{
	LL a[6][6];
	Matrix operator * (const Matrix &b)const{
		Matrix ret;
		for(int i=1;i<=5;++i)
			for(int j=1;j<=5;++j){
				ret.a[i][j]=0;
				for(int k=1;k<=5;++k)
					(ret.a[i][j]+=a[i][k]*b.a[k][j])%=m;
			}
		return ret;
	}
}s,x,y;

Matrix exp(Matrix k,LL b){
	Matrix ret=k;
	Matrix c=k;
	b--;
	if(!b) return ret;
	while(b){
		if(b&1) ret=ret*c;
		b>>=1;
		c=c*c;
	}
	return ret;
}

int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	
	for(int i=1;i<=5;++i)
		for(int j=1;j<=5;++j)
			s.a[i][j]=0;
	s.a[1][1]=s.a[1][2]=s.a[1][4]=1;s.a[1][5]=2;
	s.a[2][1]=1;
	s.a[3][4]=1;
	s.a[4][1]=s.a[4][3]=1;
	s.a[5][1]=s.a[5][5]=1;
	y.a[1][1]=1;
	y.a[2][1]=1;
	y.a[3][1]=0;
	y.a[4][1]=1;
	y.a[5][1]=1;
	while(scanf("%lld%lld",&n,&m)){
		if(n==1||n==0){
			printf("%d\n",1%m);
			continue;
		}
		x=exp(s,n-1);
		x=x*y;
		printf("%lld\n",x.a[1][1]%m);
	}
	return 0;
}














