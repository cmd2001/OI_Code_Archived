using namespace std;
int main(){}

#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
struct _Main{
int minsiz[10010];//分割后 
int size[10010];//不含自己 
int nxt[20010],to[20010],head[10010];
int idx;
void inline add(int a,int b){
	idx++;
	nxt[idx]=head[a];
	head[a]=idx;
	to[idx]=b;
}
void read(int &a){
	char t;
	while(!isdigit(t=getchar()));
	a=t-'0';
	while(isdigit(t=getchar())){
		a*=10;
		a+=t-'0';
	}
	
}

int n;
_Main(){
	freopen("treecut.in","r",stdin);
	freopen("treecut.out","w",stdout);
	int i,j,k;
	read(n);
	for(i=1;i<n;i++){
		read(j);read(k);
		add(j,k);
		add(k,j);
	}
	dfs1(1,0);
	dfs2(1,0);
	for(i=1;i<=n;i++){
		if(minsiz[i]<= (n>>1)){
			printf("%d\n",i);
		}
	}
	fclose(stdout);
}

void dfs1(int nd,int from){
	int i;
	for(i=head[nd];i;i=nxt[i]){
		if(to[i]!=from){
			dfs1(to[i],nd);
			size[nd]+=size[to[i]]+1;
		}
	}
}
void dfs2(int nd,int from){
	int i;
	minsiz[nd]=max(minsiz[nd],size[1]-size[nd]);
	for(i=head[nd];i;i=nxt[i]){
		if(to[i]!=from){
			minsiz[nd]=max(minsiz[nd],size[to[i]]+1);
			dfs2(to[i],nd);
		}
	}
}

	
	
}treecut; 
