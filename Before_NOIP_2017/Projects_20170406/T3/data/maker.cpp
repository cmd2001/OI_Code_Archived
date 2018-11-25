#include<bits/stdc++.h>
using namespace std;
int t;
char in[20],out[20],cmd[100];
int m;
int a,b;
int main()
{
	for(int i=0;i<20;i++)
	{
		if(t<10) t=100*(t+1);
		else t=100000;
		sprintf(in,"mod%d.in",i);
		sprintf(out,"mod%d.ans",i);
		freopen(in,"w",stdout);
		printf("%d\n",t);
		for(int j=1;j<=t;j++)
		{
			m=rand()%3+1;
			printf("%d\n",m);
			for(int k=1;k<=m;k++)
			{
				a=rand()%9999+1;
				b=rand()%a;
				printf("%d %d\n",a,b);
			}
		}
		fclose(stdout);
		sprintf(cmd,"maker_std.exe < %s > %s",in,out);
		system(cmd);
		printf("dat %d made\n",i+1);
	}
	return 0;
}
