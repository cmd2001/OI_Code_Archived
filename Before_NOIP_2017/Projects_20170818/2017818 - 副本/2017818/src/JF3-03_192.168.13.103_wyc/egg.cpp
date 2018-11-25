#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=1005;
const int INF=0x3f3f3f3f;

int f[maxn][maxn];

int main(){
	freopen("egg.in","r",stdin);
	freopen("egg.out","w",stdout);
	memset(f,INF,sizeof(f));
	int n,m;
	scanf("%d%d",&n,&m);
	f[0][0]=0;
	for(int i=1;i<=m;i++){
		f[0][i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=min(i,m);j++){
			for(int k=1;k<=i;k++){
				f[i][j]=min(f[i][j],max(f[k-1][j-1],f[i-k][j]));
			}
			f[i][j]++;
			//printf("f[%d][%d]=%d\n",i,j,f[i][j]);
		}
	}
	if(m>n) m=n;
	printf("%d",f[n][m]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
