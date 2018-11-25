#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<complex>
#define pi 3.141592653589
using namespace std;
const int Mx=200010;
typedef complex <double> C;
int n,m,l,r[Mx],c[Mx];
char s[Mx],t[Mx];
C A[Mx],B[Mx];
void fft(C *A,int tag)
{
    for(int i=0;i<n;i++) if(r[i]>i) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        C e(cos(pi/i),tag*sin(pi/i));
        for(int j=0;j<n;j+=i<<1)
        {
            C ei=1;
            for(int k=0;k<i;k++,ei*=e)
            {
                C x=A[j+k],y=ei*A[j+k+i];
                A[j+k]=x+y,A[j+k+i]=x-y;
            }
        }
    }
}
int main()
{
	#define debug cout
    scanf("%d%s%s",&m,s,t);
    for(int i=0;i<m;i++) A[i]=s[m-i-1]-'0',B[i]=t[m-i-1]-'0';
    for(n=1,m<<=1;n<m;n<<=1) l++;
    debug<<"l="<<l<<endl;
    for(int i=0;i<n;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));//ºûµû 
    for(int i=0;i<n;i++) debug<<A[i].real()<<endl;
    fft(A,1),fft(B,1);
    for(int i=0;i<n;i++) A[i]*=B[i]; fft(A,-1);
    for(int i=0;i<n;i++) A[i]/=n;
    for(int i=0;i<m;i++) c[i]=(int) (A[i].real()+0.1);
    debug<<"ffted"<<endl;
    for(int i=0;i<m;i++) debug<<c[i]<<endl;
    for(int i=0;i<m;i++)
        if(c[i]>=10) c[i+1]+=c[i]/10,c[i]%=10;
        else if(!c[i]&&i==m-1) m--;
    for(int i=m-1;i>=0;i--) printf("%d",c[i]);
    return 0; 
}
