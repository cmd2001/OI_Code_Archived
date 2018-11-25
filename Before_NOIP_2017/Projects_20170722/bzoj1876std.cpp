#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 1000000000
using namespace std;
char ch1[10005],ch2[10005];
int la,lb,cnt;
struct data{int a[1205],l;}a,b;
bool com()
{
	if(a.l<b.l)return 0;
	if(a.l>b.l)return 1;
	for(int i=a.l;i>0;--i)
	    if(a.a[i]>b.a[i])return 1;
	    else if(a.a[i]<b.a[i])return 0;
	return 1;
}
void print(data a)
{
    while(a.a[a.l]==0)a.l--;
	for(int i=a.l;i>0;--i)
	    if(i==a.l)printf("%d",a.a[i]);
	    else printf("%09d",a.a[i]);
}
inline data sub(data a,data b)
{
	int k;
    data c;
	for(int i=1;i<=1200;++i)
	{
	   if(i<=b.l)c.a[i]=a.a[i]-b.a[i];
	   else if(i<=a.l)c.a[i]=a.a[i];
	   else c.a[i]=0;
	   if(c.a[i]<0)
	   {
	      c.a[i]+=inf;
	      a.a[i+1]--;
	   }
    }
    c.l=a.l;
    while(c.a[c.l]==0&&c.l)c.l--;
    return c;
}
void diva()
{
	for(int i=1;i<=a.l;i++)
	{
	    if(a.a[i]&1)a.a[i-1]+=inf/2;
	    a.a[i]>>=1;
	}
	if(!a.a[a.l])a.l--;
}
void divb()
{
    for(int i=1;i<=b.l;i++)
	{
	    if(b.a[i]&1)b.a[i-1]+=inf/2;
	    b.a[i]>>=1;
	}
	if(!b.a[b.l])b.l--;
}
void mul()
{
	for(int i=a.l;i>0;i--)
	{
	   a.a[i]<<=1;
	   a.a[i+1]+=a.a[i]/inf;
	   a.a[i]%=inf;
    }
    while(a.a[a.l]>0)a.l++;
    for(int i=b.l;i>0;i--)
	{
	   b.a[i]<<=1;
	   b.a[i+1]+=b.a[i]/inf;
	   b.a[i]%=inf;
    }
    while(b.a[b.l]>0)b.l++;
}
int main()
{
	scanf("%s%s",ch1+1,ch2+1);
	la=strlen(ch1+1);lb=strlen(ch2+1);
	if(la%9)a.l=la/9+1;
	else a.l=la/9;
	if(lb%9)b.l=lb/9+1;
	else b.l=lb/9;
	for(int i=1;i<=a.l;++i)
	{
		int k1=max(1,la-i*9+1),k2=la-(i-1)*9;
		for(int j=k1;j<=k2;++j)
		    a.a[i]=a.a[i]*10+ch1[j]-'0';
	}
	for(int i=1;i<=b.l;++i)
	{
		int k1=max(1,lb-i*9+1),k2=lb-(i-1)*9;
		for(int j=k1;j<=k2;++j)
		    b.a[i]=b.a[i]*10+ch2[j]-'0';
	}
	while(1)
    {
    	if((a.a[1]%2==0)&&(b.a[1]%2==0)){diva();divb();cnt++;}
    	else if((a.a[1]%2==0))diva();
    	else if((b.a[1]%2==0))divb();
	    if(com()){a=sub(a,b);if(!a.l){while(cnt--)mul();print(b);break;}}
	    else {b=sub(b,a);if(!b.l){while(cnt--)mul();print(a);break;}}
    }
    //system("pause");
	return 0;
}
