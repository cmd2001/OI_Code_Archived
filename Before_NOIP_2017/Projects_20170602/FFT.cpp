#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e7+1e2;

typedef complex<double> Comp;
Comp a[maxn],b[maxn],c[maxn],tmp[maxn],eps[maxn],anti_eps[maxn];
int len,out[maxn];
char in[maxn],t;

inline void get_eps(int len)
{
	const double pi=acos(-1);
	for(int i=0;i<len;i++)
	{
		eps[i]=Comp(cos(pi*2*i/len),sin(pi*2*i/len));
		anti_eps[i]=conj(eps[i]);
	}
}

void fft(Comp *ret,int len,int step,Comp* eps)
{
	if(len==1) return;
	int m=len>>1;
	fft(ret,m,step<<1,eps);
	fft(ret+step,m,step<<1,eps);
	for(int k=0;k<m;k++)
	{
		int pos=2*step*k; // accessing the next level
		tmp[k]=ret[pos]+eps[k*step]*ret[pos+step];
		tmp[k+m]=ret[pos]-eps[k*step]*ret[pos+step];
	}
	for(int k=0;k<len;k++) ret[k*step]=tmp[k];
}

inline void get_input()
{
	static int t;
	scanf("%s",in);
	len=t=strlen(in);
	for(int i=0;i<t;i++) a[i]=Comp(in[i]-'0',0);
	reverse(a,a+t);
	for(int i=0;i<len;i++) debug<<a[i].real()<<endl;
	scanf("%s",in);
	len=max(len,t=strlen(in));
	for(int i=0;i<t;i++) b[i]=Comp(in[i]-'0',0);
	reverse(b,b+t);
	t=0;
	while((1<<t)<len) t++;
	len=1<<(t+1);
	get_eps(len);
	fft(a,len,1,eps);
	debug<<"a="<<a<<endl;
	for(int i=0;i<len;i++) debug<<a[i].real()<<endl;
	fft(b,len,1,eps);
	debug<<"ffted"<<endl;
	for(int i=0;i<len;i++) c[i]=a[i]*b[i];
	fft(c,len,1,anti_eps);
	debug<<"c="<<c<<endl;
	for(int i=0;i<len;i++) debug<<c[i].real()<<endl;
	for(int i=0;i<len;i++) out[i]=(c[i].real()+0.1)/len;
	for(int i=0;i<len;i++) out[i+1]+=out[i]/10,out[i]%=10;
	while(!out[len]) len--;
	for(int i=len;i>=0;i--) debug<<out[i];
}
	
	
int main()
{
	get_input();
	return 0;
}
