#include<iostream>
#include<cstdio>

using namespace std;

#define maxn 100000
int n,m,f[(1<<4)][maxn];

int dfs(int s,int p){
	if(p>4){
		if(s==(1<<4)-1)return 1;
		else return 0;
	}
	int ans=0;
	ans=dfs(s|(1<<(p-1)),p+1);
	if(p>1&&!(s&(1<<(p-2))))ans=dfs((s|(3<<(p-2)))) 
}

int main(){
	while(~scanf("%d%d",&n,&m)){
		for(int i=1;i<=n;i++){
			for(int j=0;j<(1<<4);j++){
				f[j][i]=dfs(j,1)+f[j][i-1];
			}
		}
		
	}
	return 0;
} 
