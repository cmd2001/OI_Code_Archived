#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1e5+1e2;

int a[maxn],b[maxn];
int al,bl,l;
char s[maxn];

int main()
{
	scanf("%s",s+1);
	al=strlen(s+1);
	for(int i=1;i<=al;i++) a[i]=s[al-i+1]-'0';
	
	scanf("%s",s+1);
	bl=strlen(s+1);
	for(int i=1;i<=bl;i++) b[i]=s[bl-i+1]-'0';
	
	l=max(al,bl);
	
	for(int i=1;i<=l;i++)
	{
		a[i]+=b[i];
		a[i+1]+=a[i]/10;
		a[i]%=10;
	}
	
	while(a[l+1])
	{
		l++;
		a[l+1]+=a[l]/10;
		a[l]%=10;
	}
	
	for(int i=l;i;i--) printf("%d",a[i]);
	
	putchar('\n');
	
	return 0;
}
	
