#include<bits/stdc++.h>
using namespace std;
int main()
{
	static int in[11],n,ans=0;
	for(int i=1;i<=10;i++) cin>>in[i];
	cin>>n;
	n+=30;
	for(int i=1;i<=10;i++) ans+=in[i]<=n;
	cout<<ans<<endl;
	return 0;
}
