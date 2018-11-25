#include<bits/stdc++.h>
using namespace std;
char c[1000];

int main()
{
	for(int i=1;i<=20;i++)
	{
		cerr<<"Case :: "<<i<<endl;
		freopen("arg.txt","w",stdout);
		cout<<i<<endl;
		fclose(stdout);
		sprintf(c,"gen.exe < arg.txt > chain%d.in",i-1);
		system(c);
		//cerr<<"gened"<<endl;
		sprintf(c,"std.exe < chain%d.in > chain%d.out",i-1,i-1);
		system(c);
	}
	
	return 0;
}
		
