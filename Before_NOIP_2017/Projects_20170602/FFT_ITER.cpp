#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
typedef complex<double> Comp;


Comp a[maxn],b[maxn],c[maxn],eps[maxn],anti_eps[maxn];
char in[maxn];
int out[maxn],len;

inline void geteps(int len)
{
	const double pi=acos(-1.0);
	for(int k=0;k<len;k++) eps[k]=Comp(cos(pi*2*k/len),sin(pi*2*k/len)),anti_eps[k]=conj(eps[k]);
}

void bitrev(int n,Comp* x)
{
	for(int i=0,j=0;i<n;i++)
	{
		debug<<"i="<<i<<"j="<<j<<endl;
		if(i>j) swap(x[i],x[j]),debug<<"swap"<<endl;
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
}

inline void iter_fft(int len,Comp* x,Comp* eps)
{
	bitrev(len,x);
	for(int i=2;i<=len;i<<=1) // i is the step
	{
		int m=i>>1;
		for(int j=0;j<len;j+=i) // j is the calcing pos?
			for(int k=0;k<m;k++) // k is calcing length
			{
				Comp z=x[j+m+k]*eps[len/i*k];
				x[j+m+k]=x[j+k]-z;
				x[j+k]+=z;
			}
	}
}



inline void getput()
{
	int t,maxt;
	scanf("%s",in);
	maxt=t=strlen(in);
	for(int i=0;i<t;i++) a[i]=Comp(in[i]-'0',0);
	reverse(a,a+t);
	scanf("%s",in);
	maxt=max(maxt,t=strlen(in));
	for(int i=0;i<t;i++) b[i]=Comp(in[i]-'0',0);
	reverse(b,b+t);
	t=0;
	while((1<<t)<maxt) t++;
	len=1<<(t+1);
}
int main()
{
	getput();
	geteps(len);
	iter_fft(len,a,eps);
	iter_fft(len,b,eps);
	for(int i=0;i<len;i++) c[i]=a[i]*b[i];
	iter_fft(len,c,anti_eps);
	for(int i=0;i<len;i++) out[i]=(c[i].real()+0.1)/len;
	for(int i=0;i<len;i++) out[i+1]+=out[i]/10,out[i]%=10;
	while((!out[len])&&len>=0) len--;
	if(len<0) putchar('0');
	while(len>=0) printf("%d",out[len]),len--;
	putchar('\n');
	return 0;
}
	
				
			
