#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
using namespace std;

int n,m,f[1005][1005];

int maxlen(int c,int x){
	int i=1,p=n,len=0;
	while(i<=x){
		while(f[c][p]+i>x) p--;
		len+=p;
		i++;
	}
	return len;
}

int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	
	cin>>n>>m;
	if(m==1) cout<<n;
	else if(m==2) {
		int l=0,r=n;
		while(r>l){
			int mid=(l+r)/2;
			if(mid*mid+mid<2*n) l=mid+1;
			else r=mid;
		}
		cout<<l;
	}
	else{
		memset(f,0x3f3f3f,sizeof(f));
		int p=0;
		for(int i=0;i<=45;i++) while(i*i+i>=2*p) f[2][p++]=i;
		for(int i=3;i<=m;i++)
			for(int j=1;j<=n;j++){
				int l=1,r=j;
				while(l<r){
					int mid=(l+r)/2;
					if(maxlen(i-1,mid)<n) l=mid+1;
					else r=mid;
				}
				f[i][j]=l;
			}
		cout<<f[m][n];
	}
	
	fclose(stdin);fclose(stdout);
	return 0;
}

