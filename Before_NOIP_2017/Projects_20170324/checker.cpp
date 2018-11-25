#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	for(int i=1,x,y;i<=n;i++)
	{
		freopen("my.out","r",stdin);
		cin>>x;
		freopen("o3.txt","r",stdin);
		cin>>y;
		if(x!=y)
		{
			cout<<"at"<<i<<endl;
			cout<<"x="<<x<<endl;
			cout<<"y="<<y<<endl;
			break;
		}
	}
	return 0;
}
		
