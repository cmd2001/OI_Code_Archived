//Cv1037_By_Cmd2001
#include<cstdio>
using namespace std;

int n,in,cnt,ans,fst;

int main()
{
	scanf("%d",&n);
	
	while(n--)
	{
		scanf("%d",&in);
		if(in) ++cnt;
		else ans|=(cnt&1),cnt=0;
	}
	
	ans|=(cnt&1);
	
	if(ans) puts("YES");
	else puts("NO");
	
	return 0;
}
