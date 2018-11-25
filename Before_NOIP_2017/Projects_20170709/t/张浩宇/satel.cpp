using namespace std;
int main() {}


#include<cstdio>
#include<cstring>
#include<algorithm>
struct _Main {
	char map[68][67];//67行66列
	bool vis[68][67];
	bool judge() {
		int i,j;
		for(i=t; i<=b; i++) {
			for(j=l; j<=r; j++) {
				if(map[i][j]=='.') {
					return false;
				}
			}
		}
		return true;
	}
	int R,C;//r行c列
	int l,r,t,b;
	void inline ini() {
		l=66,r=0,t=66,b=0;
	}
	bool inline legal(int x,int y) {
		return x>0&&x<=R&&y>0&&y<=C&&(!vis[x][y])&&map[x][y]=='#';
	}
	int room,nerd;
	_Main() {
		freopen("satel.in","r",stdin);
		freopen("satel.out","w",stdout);
		room=nerd=0;
		int i,j;
		char t;
		scanf("%d%d",&R,&C);
		for(i=1; i<=R; i++) {
			for(j=1; j<=C; j++) {
				while((t=getchar())!='.'&&t!='#'){
					if(t==EOF){
						break;
					}
				}
				map[i][j]=t;
			}
		}
		for(i=1; i<=R; i++) {
			for(j=1; j<=C; j++) {
				if(legal(i,j)) {
					ini();
					dfs(i,j);
					if(judge()) {
						room++;
					} else {
						nerd++;
					}
				}
			}
		}
		printf("%d\n%d",room,nerd);
		fclose(stdout);

	}
	void dfs(int x,int y) {
		l=min(l,y);
		r=max(r,y);
		t=min(t,x);
		b=max(b,x);
		vis[x][y]=true;
		if(legal(x-1,y)) dfs(x-1,y);
		if(legal(x,y-1)) dfs(x,y-1);
		if(legal(x+1,y)) dfs(x+1,y);
		if(legal(x,y+1)) dfs(x,y+1);

	}







} satel;

