#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 50010
using namespace std;
struct node{
	int left,right,sum;//sum是当前节点的值 
	int mid(){
		return (left+right)>>1;
	}
};
node tree[MAXN*4];
int ans;
void build(int left,int right,int rt){//rt=root
	tree[rt].left=left;
	tree[rt].right=right;
	if(left==right){
		scanf("%d",&tree[rt].sum);
		return;
	}
	int mid=tree[rt].mid();
	build(left,mid,rt<<1);
	build(mid+1,right,rt<<1|1);
	tree[rt].sum=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
void query(int left,int right,int rt,int L,int R){
	if(L<=left&&right<=R){
		ans+=tree[rt].sum;
		return;
	}
	int mid=tree[rt].mid();
	if(R<mid)
		query(left,mid,rt<<1,L,R);//lson
	else if(L>mid)
		query(mid+1,right,rt<<1|1,L,R);
	else{
		query(left,mid,rt<<1,L,R);
		query(mid+1,right,rt<<1|1,L,R);
	}
}
void update(int left,int right,int rt,int pos,int add){
	if(left==right){
		tree[rt].sum+=add;
		return;
	}
	int mid=tree[rt].mid();
	if(pos<=mid)
		update(left,mid,rt<<1,pos,add);
	else
		update(mid+1,right,rt<<1|1,pos,add);
	tree[rt].sum+=tree[rt<<1].sum+tree[rt<<1|1].sum;
}
int main(){
	//freopen("test.txt","r",stdin);
	int t,n;
	scanf("%d",&t);
	for(int k=1;k<=t;k++){
		scanf("%d",&n);
		build(1,n,1);
		printf("Case %d:\n",k);
		char cmd[10];
		while(scanf("%s",cmd)){
			if(cmd[0]=='E')
				break;
			int i,j;
			scanf("%d%d",&i,&j);
			if(cmd[0]=='Q'){
				ans=0;
				query(1,n,1,i,j); 
				printf("%d\n",ans);
			}
			else if(cmd[0]=='A')
				update(1,n,1,i,j);
			else
				update(1,n,1,i,-j);
		}
	}
	//fclose(stdin);
	return 0;
}
