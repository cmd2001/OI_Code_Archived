#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;
char in[maxn];
int dat[maxn],sq[maxn],len,sql,pos,tmp;

int main()
{
	scanf("%s",in);
	len=strlen(in);
	for(int i=1;i<=len;i++) dat[i]=in[i-1]-'0';
	if(len&1) sq[++sql]=sqrt(dat[1]),pos=2,tmp=dat[1]-sq[1]*sq[1];
	else sq[++sql]=sqrt(10*dat[1]+dat[2]),pos=3,tmp=10*dat[1]+dat[2]-sq[1]*sq[1];
	for(pos;pos<=len;pos+=2)
	{
		tmp=tmp*10+dat[pos]*10+dat[pos+1];
		sq[sql+1]=tmp/(20*sq[sql]);
		sql++;
		if(tmp<())
	}
	
	return 0;
}
