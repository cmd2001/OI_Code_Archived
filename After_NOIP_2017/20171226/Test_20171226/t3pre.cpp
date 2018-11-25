#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e3+1e2;

int a[maxn],b[maxn],c[maxn],n,ans;
int lx,ly,lz;

inline bool cjudge(int i,int aa,int bb,int cc) {
	int ret =0;
	ret += ( aa > a[i] );
	ret += ( bb > b[i] );
	ret += ( cc > c[i] );
	return ret >= 2;
}

inline bool judge(int aa,int bb,int cc) {
	int ret = 1;
	for(int i=1;i<=n;i++) {
		ret &= cjudge(i,aa,bb,cc);
		if( !ret )
			return 0;
	}
	return ret;
}

int main() {
	scanf("%d%d%d%d",&n,&lx,&ly,&lz);
	for(int i=1;i<=n;i++)
		scanf("%d%d%d",a+i,b+i,c+i);
	puts("Answers are::");
	for(int i=1;i<=lx;i++)
	{
		int last = ans;
		for(int j=1;j<=ly;j++)
			for(int k=1;k<=lz;k++)
				if( judge(i,j,k) ) {
					++ans;
					//printf("%d %d %d\n",i,j,k);
				}
		if( ans - last )
			debug<<"i = "<<i<<" inserted"<<ans-last<<endl;
	}
	printf("%d\n",ans);
	
	return 0;
}
