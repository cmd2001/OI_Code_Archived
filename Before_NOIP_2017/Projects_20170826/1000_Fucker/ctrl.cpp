#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;

char cmd[maxn];

int main()
{
	for(int i=1;i<=20;i++)
	{
		cerr<<"i="<<i<<endl;
		freopen("arg.txt","w",stdout);
		if(i<=10) cout<<10*i<<endl;
		else cout<<5000*i<<endl;
		fclose(stdout);
		sprintf(cmd,"mker.exe > apb%d.in",i-1);
		system(cmd);
		sprintf(cmd,"std.exe < apb%d.in > apb%d.out",i-1,i-1);
		system(cmd);
	}
	return 0;
}
