#include<iostream>
using namespace std;

int n,ans,t;

int main()
{
	cin>>n;
	ans=1;
	do
	{
		if(ans<=n) ans<<=1;
		else ans=((ans<<1)-1)%(n<<1);
		t++;
	}
	while(ans!=1);
	cout<<t<<endl;
	return 0;
}
	
	
