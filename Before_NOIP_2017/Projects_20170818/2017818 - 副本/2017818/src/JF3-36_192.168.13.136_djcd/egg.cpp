#include<bits/stdc++.h>
using namespace std;
int n,m;
int ret;
int ans;
int l,r,mid;
bool find(int x)
{	int num=0;
	for(int i=x;i>=0;i--)	num+=i;
	if(num>=n) return 1;
	return 0;
}
int main()
{
    freopen("egg.in","r",stdin);
    freopen("egg.out","w",stdout);
	cin>>n>>m;
	if(m==1) {
		cout<<n<<endl;
		return 0;
	}
	if(n==1)
	{
	    cout<<1<<endl;
	    return 0;
	}
	while(m>2)
	{
		m--;
		ans++;
		n=n/2;
		if(n==0) {
		    cout<<ans<<endl;
		    return 0;
		}
	}
	l=1;r=n;
	while(l!=r)
	{
		mid=(l+r)>>1;
		if(find(mid)) r=mid;
		else l=mid+1;
	}
	mid=(l+r)>>1;
	//if(find(mid))
	cout<<mid+ans<<endl;
}
