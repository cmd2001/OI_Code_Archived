#include<cmath>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define inf 1000000000
#define mod 1000000007
#define ll long long
#define eps 1e-12
using namespace std;
ll read()
{
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,D;
ll lastans;
struct P{
	int d[2],mx[2],mn[2],v,l,r;
	ll sum;
	int &operator[](int x){
		return d[x];
	}
	friend bool operator==(P a,P b){
		return a.d[0]==b.d[0]&&a.d[1]==b.d[1];
	}
	friend bool operator<(P a,P b){
		return a[D]<b[D];
	}
}p[200005];
bool in(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{
	return x1<=X1&&X2<=x2&&y1<=Y1&&Y2<=y2;
}
bool out(int x1,int y1,int x2,int y2,int X1,int Y1,int X2,int Y2)
{
	return x1>X2||x2<X1||y1>Y2||y2<Y1;
}
struct data{
	P t[200005],now;
	int rt,cnt;
	void update(int k){
		int l=t[k].l,r=t[k].r;
		for(int i=0;i<2;i++)
		{
			t[k].mn[i]=t[k].mx[i]=t[k][i];
			if(l)t[k].mn[i]=min(t[k].mn[i],t[l].mn[i]);
			if(l)t[k].mx[i]=max(t[k].mx[i],t[l].mx[i]);
			if(r)t[k].mn[i]=min(t[k].mn[i],t[r].mn[i]);
			if(r)t[k].mx[i]=max(t[k].mx[i],t[r].mx[i]);
		}
		t[k].sum=t[k].v+t[l].sum+t[r].sum;
	}
	void insert(int &k,bool D){
        if(!k)
        {
            k=++cnt;
            t[k][0]=t[k].mn[0]=t[k].mx[0]=now[0];
            t[k][1]=t[k].mn[1]=t[k].mx[1]=now[1];
        }
        if(now==t[k])
        {
            t[k].v+=now.v,t[k].sum+=now.v;
            return;
        }
        if(now[D]<t[k][D])insert(t[k].l,D^1);
        else insert(t[k].r,D^1);
        update(k);
    }
	ll query(int k,int x1,int y1,int x2,int y2){
		if(!k)return 0;
		ll tmp=0;
		if(in(x1,y1,x2,y2,t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1]))return t[k].sum;
		if(out(x1,y1,x2,y2,t[k].mn[0],t[k].mn[1],t[k].mx[0],t[k].mx[1]))return 0;
		if(in(x1,y1,x2,y2,t[k][0],t[k][1],t[k][0],t[k][1]))tmp+=t[k].v;
		tmp+=query(t[k].l,x1,y1,x2,y2)+query(t[k].r,x1,y1,x2,y2);
		return tmp;
	}
    int rebuild(int l,int r,bool f){
		if(l>r)return 0;
		int mid=(l+r)>>1;
		D=f;nth_element(p+l,p+mid,p+r+1);
		t[mid]=p[mid];
		t[mid].l=rebuild(l,mid-1,f^1);
		t[mid].r=rebuild(mid+1,r,f^1);
	    update(mid);
		return mid;
	}
}T;
int main()
{
	n=read();
	int opt,x,y,x2,y2,A,m=10000;
	while(1)
	{
		opt=read();if(opt==3)break;
        lastans = 0;
		x=read()^lastans;y=read()^lastans;
		if(opt==1)
		{
			A=read()^lastans;T.now[0]=x;T.now[1]=y;
			T.now.v=T.now.sum=A;
			T.insert(T.rt,0);
			if(T.cnt==m)
			{
				for(int i=1;i<=T.cnt;i++)p[i]=T.t[i];
				T.rt=T.rebuild(1,T.cnt,0);m+=10000;
			}
		}
		if(opt==2)
		{
			x2=read()^lastans;y2=read()^lastans;
			lastans=T.query(T.rt,x,y,x2,y2);
			printf("%lld\n",lastans);
		}		
	}
	return 0;
}