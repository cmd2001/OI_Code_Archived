#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

int n,mod,num;

struct matrix
{
    long long a[10][10];
    matrix operator*(const matrix &b)const{
        matrix ret;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                ret.a[i][j]=0;
                for(int k=1;k<=n;k++) ret.a[i][j]=(ret.a[i][j]+a[i][k]*b.a[k][j])%mod;
            }
        return ret;
    }
}a,b;

matrix matrix_pow(matrix a,long long b)
{
    matrix ret=a,tmp=a;
    b--;
    for(;b;b>>=1,tmp=tmp*tmp)
        if(b&1) ret=ret*tmp;
    return ret;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d",&num,&mod);
	n=6;
	while(num+mod)
	{
		if(num==1)printf("1\n");
		else
		{
			for(int i=1;i<=6;i++)for(int j=1;j<=n;j++)a.a[i][j]=b.a[i][j]=0;
			for(int i=1;i<=6;i++)if(i!=3){b.a[i][1]=a.a[1][i]=a.a[i][1]=1;}
			for(int i=2;i<=5;i++)a.a[i][6-i+1]=1;
			a=matrix_pow(a,num-1);
			b=a*b;
			printf("%lld\n",b.a[1][1]);
		}
		scanf("%d%d",&num,&mod);
	}
	return 0; 
}
