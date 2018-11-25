#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

#define maxn 20
int n,edge[maxn][maxn],color[maxn];
unsigned int ans=0;
bool used[maxn];
int f[(1<<maxn)];

void ccalf(int id){
	memset(color,-1,sizeof(color));
	int b=id,tot=0,p=0;
	while(b){
		if(b&1){
			for(int i=0;i<p;i++){
				if(color[i]>=0&&edge[i][p]){
					used[color[i]]=1;//if(id==15)cout<<p<<' '<<i<<' '<<endl;
				}
			}
			for(int i=0;i<tot;i++){
				if(!used[i])color[p]=i;
			}
			if(color[p]<0)color[p]=tot++;
			for(int i=0;i<p;i++){
				if(color[i]>=0&&edge[i][p]){
					used[color[i]]=0;
				}
			}
		}
		b>>=1;
		p++;
	}
	f[id]=tot;
}

unsigned int power(unsigned int a,int b){
	unsigned int ret=1;
	while(b){
		if(b&1)ret=ret*a;
		b>>=1;
		a=a*a;
	}
	return ret;
}

void dfs(int p,int id){
	if(p>=n){
		ccalf(id);
	//	cout<<id<<' '<<f[id]<<endl;
		ans+=f[id]*power(233u,id);
		return ;
	}
	dfs(p+1,id+(1<<p));
	dfs(p+1,id);
}

int main(){
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	char ch[20];
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%s",ch);
		for(int j=0;j<n;j++){
			edge[i][j]=ch[j]-'0';
		}
	}
	dfs(0,0);
	cout<<ans<<endl;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
