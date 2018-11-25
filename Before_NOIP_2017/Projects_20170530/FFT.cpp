#include<bits/stdc++.h>
#define debug cout
const int maxn=1e7+1e2;
using namespace std;
typedef complex<double> Comp;

Comp eps[maxn],anti_eps[maxn],a[maxn],b[maxn],c[maxn],tmp[maxn];
int ans[maxn],la,lb,len,t;
char in[maxn];

inline void get_eps(int n)
{
	const double pi=acos(-1);
	for(int i=0;i<n;i++)
	{
		eps[i]=Comp(cos(pi*2*i/n),sin(pi*2*i/n));
		anti_eps[i]=conj(eps[i]);
	}
}
		
void fft(int len,Comp* ret,int delta,int step,Comp* eps)
{
	if(len==1) return;
	int m=len>>1;
	fft(m,ret,delta,step<<1,eps);
	fft(m,ret,delta+step,step<<1,eps);
	for(int k=0;k<m;k++)
	{
		int pos=2*step*k;
		tmp[k]=ret[pos+delta]+eps[k*step]*ret[pos+delta+step];
		tmp[k+m]=ret[pos+delta]-eps[k*step]*ret[pos+delta+step];
	}
	for(int i=0;i<len;i++)
	{
		ret[i*step+delta]=tmp[i];
	}
}

int main()
{
	//return 0;
	scanf("%s",in);
	la=strlen(in);
	for(int i=0;i<la;i++) a[i]=Comp(in[i]-'0',0);
	scanf("%s",in);
	lb=strlen(in);
	for(int i=0;i<lb;i++) b[i]=Comp(in[i]-'0',0);
	debug<<"inputed"<<endl;
	len=max(la,lb);
	while((1<<t)<=len) t++;
	len=1<<t;
	debug<<"len="<<len<<endl;
	get_eps(len);
	debug<<"eps got"<<endl;
	fft(len,a,0,1,eps);
	fft(len,b,0,1,eps);
	debug<<"ffted"<<endl;
	for(int i=0;i<len;i++) c[i]=a[i]*b[i];
	fft(len,c,0,1,anti_eps);
	for(int i=0;i<len;i++) ans[i]=(c[i].real()+0.1),debug<<ans[i]<<endl;
	for(int i=0;i<len;i++) ans[i+1]+=ans[i]/10,ans[i]%=10;
	while(ans[len]>=10) ans[len+1]=ans[len]/10,ans[len]%=10,len++;
	for(int i=0;i<len;i++) debug<<ans[i];
	return 0;
}
