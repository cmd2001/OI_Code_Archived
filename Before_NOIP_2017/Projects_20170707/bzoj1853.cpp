#include<iostream>
#include<cstdio>
#include<cstirng>
#include<algorithm>
#define lli long long int 
#define debug cout
const int maxn=12e2+1e2;
using namespace std;

lli num[maxn],cnt,mx;
lli l,r;

inline void pre(int pos,lli x)
{
	if(pos>mx||x>r) return;
	num[cnt++]=x;
	pre(pos+1,x*10+6);
	pre(pos++1,x*10+8);
}
	

