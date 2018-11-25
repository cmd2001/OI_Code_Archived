#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
struct node{
	bool a[2][2];
	bool* operator [] (int x){return a[x];}
	void chu(){
		a[0][0]=a[1][1]=true;
		a[1][0]=a[0][1]=false;
		return;
	}
}tree[810000],ans;
node merge(bool p[2],node a,node b){
	node ret;
	ret[0][0]=((a[0][0]&p[0]&b[0][0])|(a[0][1]&p[1]&b[1][0]));
	ret[0][1]=((a[0][0]&p[0]&b[0][1])|(a[0][1]&p[1]&b[1][1]));
	ret[1][0]=((a[1][0]&p[0]&b[0][0])|(a[1][1]&p[1]&b[1][0]));
	ret[1][1]=((a[1][0]&p[0]&b[0][1])|(a[1][1]&p[1]&b[1][1]));
	return ret;
}
bool a[100010][2];
int mb,val,g,st,ed;
void build(int l,int r,int pos){
	if(l==r){
		tree[pos].chu();
		return;
	}
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	build(l,mid,lson);
	build(mid+1,r,rson);
	tree[pos]=merge(a[mid],tree[lson],tree[rson]);
	return;
}
void heng(int l,int r,int pos){
	if(l==r) return;
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	if(mb<=mid) heng(l,mid,lson);
	else heng(mid+1,r,rson);
	tree[pos]=merge(a[mid],tree[lson],tree[rson]);
	return;
}
void shu(int l,int r,int pos){
	if(l==r){
		tree[pos].a[0][1]=val;
		tree[pos].a[1][0]=val;
		return;
	}
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	if(mb<=mid) shu(l,mid,lson);
	else shu(mid+1,r,rson);
	tree[pos]=merge(a[mid],tree[lson],tree[rson]);
	return;
}
void left(int l,int r,int pos){
	if(l==r) return;
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	node tmp=merge(a[r],tree[rson],ans);
	if(tmp.a[0][g]==true||tmp.a[1][g]==true){
		mb=mid+1,ans=tmp;
		left(l,mid,lson);
	}
	else left(mid+1,r,rson);
	return;
}
void findleft(int l,int r,int pos){
	if(l==r){
		ans.chu();
		return;
	}
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	if(mb<=mid) findleft(l,mid,lson);
	else{
		findleft(mid+1,r,rson);
		if(mb!=mid+1) return;
		node tmp=merge(a[mid],tree[lson],ans);
		if(tmp[0][g]==true||tmp[1][g]==true) mb=l,ans=tmp;
		else left(l,mid,lson);
	}
	return;
}
void right(int l,int r,int pos){
	if(l==r) return;
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	node tmp=merge(a[l-1],ans,tree[lson]);
	if(tmp.a[g][0]==true||tmp.a[g][1]==true){
		mb=mid,ans=tmp;
		right(mid+1,r,rson);
	}
	else right(l,mid,lson);
	return;
}
void findright(int l,int r,int pos){
	if(l==r){
		ans.chu();
		return;
	}
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	if(mid<mb) findright(mid+1,r,rson);
	else{
		findright(l,mid,lson);
		if(mb!=mid) return;
		node tmp=merge(a[mid],ans,tree[rson]);
		if(tmp.a[g][0]==true||tmp.a[g][1]==true) mb=r,ans=tmp;
		else right(mid+1,r,rson);
	}
	return;
}
node find(int l,int r,int pos){
	if(st<=l&&r<=ed) return tree[pos];
	int mid=(l+r)/2,lson=pos*2,rson=pos*2+1;
	if(st<=mid&&mid<ed) return merge(a[mid],find(l,mid,lson),find(mid+1,r,rson));
	if(st<=mid) return find(l,mid,lson);
	return find(mid+1,r,rson);
}
int main()
{
	freopen("dat.txt","r",stdin);
	freopen("rbq.txt","w",stdout);
	int n,x,y,xx,yy;
	char in[10];
	scanf("%d",&n);
	build(1,n,1);
	while(scanf("%s",in)!=EOF){
		if(in[0]=='E') break;
		scanf("%d%d%d%d",&x,&y,&xx,&yy);
		if(in[0]=='A'){
			if(y>yy) swap(x,xx),swap(y,yy);
			g=x-1;mb=y;
			findleft(1,n,1);
			st=mb;
			x=ans[0][g]?0:1;
			g=xx-1;mb=yy;
			findright(1,n,1);
			ed=mb;
			xx=ans[g][0]?0:1;
			ans=find(1,n,1);
			if(ans.a[x][xx]==true) printf("Y\n");
			else printf("N\n");
		}
		else{
			if(in[0]=='O') val=1;
			else val=0;
			mb=y;
			if(x==xx){
				if(y>yy) swap(y,yy);
				a[y][x-1]=val;
				mb=y;
				heng(1,n,1);
			}
			else shu(1,n,1);
		}
	}
}
