#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1048576;
const double pi = acos(-1.0);

struct Comp {
    double r,i;
    friend Comp operator + (const Comp &a,const Comp &b) {
        return (Comp){a.r+b.r,a.i+b.i};
    }
    friend Comp operator - (const Comp &a,const Comp &b) {
        return (Comp){a.r-b.r,a.i-b.i};
    }
    friend Comp operator * (const Comp &a,const Comp &b) {
        return (Comp){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r};
    }
    friend Comp operator * (const double &a,const Comp &b) {
    	return (Comp){a*b.r,a*b.i};
    }
    Comp operator = (const int &x) {
        r = x;
        return *this;
    }
    inline double real() {
        return r;
    }
}t1[maxn],t2[maxn],t3[maxn],t4[maxn],t5[maxn],t6[maxn];
char ina[maxn],inb[maxn];
double a[maxn],b[maxn];
int ans[maxn],top,la,lb,len=1;

inline void fft(Comp* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap( dst[i] , dst[j] );
        for(int t = n >> 1 ; ( j ^= t ) < t ; t >>= 1 ) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const Comp per = (Comp){ cos(ope*pi/(len>>1)) , sin(ope*pi/(len>>1)) };
        for(int st=0;st<n;st+=len) {
            Comp w = (Comp){1.0,0.0};
            for(int pos=0;pos<(len>>1);pos++) {
                const Comp u = dst[st+pos] , v = dst[st+pos+(len>>1)]*w;
                dst[st+pos] = u + v ,
                dst[st+pos+(len>>1)] = u - v;
                w = w * per;
            }
        }
    }
    if( !~ope ) {
        for(int i=0;i<n;i++)
            dst[i].r /= n;
    }
}

int main() {
	scanf("%d%d",&la,&lb);
	scanf("%s%s",ina,inb);
	for(int i=0;i<la;i++)
		a[la-i-1] = ina[i] != '*' ? ina[i] - 'a' + 1 : 0;
	for(int i=0;i<lb;i++)
		b[i] = inb[i] != '*' ? inb[i] - 'a' + 1 : 0;
	while( len < lb ) len <<= 1;
	for(int i=0;i<len;i++)
		t1[i].r = a[i] * a[i] * a[i] , t2[i].r = b[i] , t3[i].r = a[i] * a[i] ,
		t4[i].r = b[i] * b[i] , t5[i].r = a[i] , t6[i].r = b[i] * b[i] * b[i] ;
	fft(t1,len,1) , fft(t2,len,1) , fft(t3,len,1) ,
	fft(t4,len,1) , fft(t5,len,1) , fft(t6,len,1);
	for(int i=0;i<len;i++)
		t1[i] = t1[i] * t2[i] - 2.0 * t3[i] * t4[i] + t5[i] * t6[i];
	fft(t1,len,-1);
	for(int i=0;i<lb;i++)
		if( fabs(t1[i].real()+0.2) <= 0.5 && i - la + 2 > 0 )
			ans[++top] = i - la + 2;
	printf("%d\n",top);
	for(int i=1;i<=top;i++)
		printf("%d%c",ans[i],i!=top?' ':'\n');
	return 0;
}




