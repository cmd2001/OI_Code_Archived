#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;

int n;
long long p;

struct Maxtri{
	long long a[20][20];
	void init(){
		for(int i=0;i<=15;i++)
			for(int j=0;j<=15;j++)
				if(i==j) a[i][j]=1;
				else a[i][j]=0;
	}
	void operator=(const Maxtri b){
		for(int i=0;i<=15;i++)
			for(int j=0;j<=15;j++)
				a[i][j]=b.a[i][j];
	}
	Maxtri operator*(const Maxtri b)const{
		Maxtri c;
		for(int i=0;i<=15;i++)
			for(int j=0;j<=15;j++){
				long long tmp=0;
				for(int k=0;k<=15;k++)
					tmp=(tmp+a[i][k]*b.a[k][j])%p;
				c.a[i][j]=tmp;
			}
		return c;
	}
}res,a,mode;

long long quick_pow(int b){
	res.init(); a=mode;
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	}
	return res.a[0][0];
}

bool ok(int a,int b){
	for(int i=0;i<=3;i++) if((a>>i&1)&&(b>>i&1)) return false;
	bool c[5]={0,0,0,0,1};
	for(int i=0;i<=3;i++) if((a>>i&1)||(b>>i&1)) c[i]=1;
	for(int i=0;i<=3;i++)
		if(!c[i]){
			if(c[i+1])return false;
			else c[i+1]=1;
		}
	return true;
}

int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	
	for(int i=0;i<=15;i++)	
		for(int j=0;j<=15;j++)
			if(ok(i,j)) mode.a[i][j]=1;
	while(cin>>n>>p&&n&&p){
		cout<<quick_pow(n)<<endl;
	}
	
	fclose(stdin);fclose(stdout);
	return 0;
}

