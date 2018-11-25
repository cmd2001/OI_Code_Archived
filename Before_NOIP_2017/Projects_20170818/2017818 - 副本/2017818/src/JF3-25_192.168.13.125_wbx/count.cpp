#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int f[50010][20],n,imod;
void dfs(int i,int j,int now,int nxt){
	if(j==n){
		f[i+1][nxt]+=f[i][now];
		f[i+1][nxt]%=imod;
		return;
	}
	if(((1<<j)&now)>0)	dfs(i,j+1,now,nxt);
	if(((1<<j)&now)==0)	dfs(i,j+1,now,(nxt|(1<<j)));
	if((j<n-1)&&((1<<j)&now)==0&&(((1<<(j+1))&now)==0))	dfs(i,j+2,now,nxt);
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int m,i,j; n=4;
	while(1)
	{
		scanf("%d%d",&m,&imod);
		if(m==0&&imod==0)	break;
		memset(f,0,sizeof(f));
		f[1][0]=1;
		for(i=1;i<=m;i++){
			for(j=0;j<16;j++){
				if(f[i][j]!=0){
					dfs(i,0,j,0);
				}
			}
		}
		printf("%d\n",f[m+1][0]);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
