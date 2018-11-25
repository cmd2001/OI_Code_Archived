#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int INF=0x3fffffff;
//egg

int n,m;
int ans;
bool find(int x)
{
	int hh=0;
	for(int i=x;i>=0;i--) hh+=i;
	if(hh>=n)	return 1;
	else return 0;
}



int main()
{
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	scanf("%d%d",&n , &m );
	if(m==1||n==1||n==2)	{cout<<n;return 0;}
	
	while(m>2){
		n/=2;m--;
		ans++;
		if(n==0){
			cout<<ans<<endl;
			return 0;
		}
	}
	int l=1,r=n,mid;
	while(l!=r){
		mid=(l+r)/2;
		if(find(mid))	r=mid;
		else l=mid+1;
	}
	mid=(l+r)/2;
	cout<<mid+ans<<endl;
	
	return 0;


}
