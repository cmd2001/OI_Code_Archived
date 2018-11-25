#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1;

int f[maxn][maxn];
int n,k;

int main() {
	scanf("%d%d",&n,&k);
	f[0][0] = 1 , f[1][1] = 1;
	for(int i=2;i<=n;i++) {
		//debug<<"i = "<<i<<endl;
		for(int j=1;j<i;j++) {
			//debug<<"j = "<<j<<endl;
			for(int l=0;l<=k;l++)
				for(int r=0;r<=k;r++)
					if( i - ( l + r ) >= 0 ) f[i][i-l-r] += f[j][l] * f[i-j-1][r];
		}
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=k;j++) debug<<f[i][j]<<" ";debug<<endl;
	}
	printf("%d\n",f[n][k]);
	return 0;
}
