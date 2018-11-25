#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int ins,st,ed,cnt,ans;
int rea[500010],uni[500010],root[500010];
struct segtree
{
	int num,lson,rson;
}tree[12000010];
int pre(int n)
{
	int m;
	sort(uni+1,uni+n+1);
	m=unique(uni+1,uni+n+1)-uni;
	/*puts("------------");
	for(int i=1;i<=n;++i) printf("%d ",uni[i]);
	puts("");
	printf("m=%d\n",m)*/;
	return m-1;
}
void init(int pos)
{
	tree[pos].lson=0;
	tree[pos].rson=0;
	tree[pos].num=0;
}
void build(int l,int r,int pos)
{
	init(pos);
	if (l==r) return;
	int mid=(l+r)/2;
	tree[pos].lson=cnt++;
	build(l,mid,tree[pos].lson);
	tree[pos].rson=cnt++;
	build(mid+1,r,tree[pos].rson);
	return;
}
void insert(int l,int r,int pos,int pla)
{
	init(pos);
	if(l==r)
	{
		tree[pos].num=tree[pla].num+1;
		return;
	}
	int mid=(l+r)/2;
	if(ins<=mid)
	{
		tree[pos].rson=tree[pla].rson;
		tree[pos].lson=cnt++;
		init(tree[pos].lson);
		insert(l,mid,tree[pos].lson,tree[pla].lson);
	}
	else
	{
		tree[pos].lson=tree[pla].lson;
		tree[pos].rson=cnt++;
		init(tree[pos].rson);
		insert(mid+1,r,tree[pos].rson,tree[pla].rson);
	}
	tree[pos].num=tree[tree[pos].lson].num+tree[tree[pos].rson].num;
	return;
}
int midcut(int i,int m)
{
	int l=0,r=m+1,mid,ans=0;
	uni[m+1]=2000000000;
	while(l<r)
	{
		mid=(l+r)/2;
		if(i<uni[mid])
		{
			r=mid;
		}
		else
		{
			l=mid+1;
			ans=max(mid,ans);
		}
	}
	return ans;
}
void find(int l,int r,int pos,int pla)
{
	if(r<=ins)
	{
		ans+=tree[pos].num-tree[pla].num;
		return;
	}
	if(ins<l)
	{
		return;
	}
	int mid=(l+r)/2;
	find(l,mid,tree[pos].lson,tree[pla].lson);
	find(mid+1,r,tree[pos].rson,tree[pla].rson);
	return;
}
void debug(int n,int m)
{
	int i;
	printf("m=%d\n",m);
	for(i=1;i<=m;i++)
	{
		printf("i=%d  uni=%d\n",i,uni[i]);
	}
	return;
}
int main()
{
	int n,m,q,t,i,k=0;
		cnt=2;
		root[0]=1;
		scanf("%d%d",&n,&q);
		for(i=1;i<=n;i++)
		{
			scanf("%d",&rea[i]);
			rea[i]+=1;
			uni[i]=rea[i];
		}
		m=pre(n);
		build(1,m,1);
		//debug(n,m);
		for(i=1;i<=n;i++)
		{
			root[i]=cnt++;
			ins=lower_bound(uni+1,uni+m+1,rea[i])-uni;
			insert(1,m,root[i],root[i-1]);
		}
		for(i=1;i<=q;i++)
		{
			ans=0;
			scanf("%d%d%d",&st,&ed,&ins);
			ins=midcut(ins+1,m);
			//printf("ins=%d\n",ins);
			find(1,m,root[ed],root[st-1]);
			printf("%d\n",ans);
		}
		return 0;
}
