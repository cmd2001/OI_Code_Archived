#include<cstdio>
using namespace std;
const int maxn=5e5+1e2;

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
	for(int i=1;i<=lx;i++)
		for(int j=1;j<=ly;j++)
			for(int k=1;k<=lz;k++)
				if( judge(i,j,k) )
					++ans;
	printf("%d\n",ans);
	
	return 0;
}
