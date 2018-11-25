#include<bits/stdc++.h>
using namespace std;
char in[100],out[100];
char cmd[100];
int main()
{
	srand(time(NULL));
	int maxn,maxint=(1<<30)-1;
	unsigned tmp;
	unsigned s,e,x;
	for(int t=0;t<20;t++)
	{
		maxn=t<10?10*(t+1):1e5;
		maxint=t<10?10*(t+1):(1<<30)-1;
		sprintf(in,"ChairmanTree%d.in",t);
		sprintf(out,"ChairmanTree%d.ans",t);
		sprintf(cmd,"stdmaker.exe %s %s",in,out);
		freopen(in,"w",stdout);
		printf("%d %d\n",maxn,maxn);
		for(int i=1;i<=maxn;i++)
		{
			tmp=(long long)(rand()*rand())%maxint;
			printf("%d ",tmp);
		}
		for(int i=1;i<=maxn;i++)
		{
			s=(long long)(rand()*rand())%maxn;
			e=(long long)(rand()*rand())%maxn;
			while(s>e) s=(long long)(rand()*rand())%maxn,e=(long long)(rand()*rand())%maxn;
			x=(long long)(rand()*rand())%maxint;
			printf("%d %d %d\n",s+1,e+1,x);
		}
		fclose(stdout);
		system(cmd);
	}
}
		
			
