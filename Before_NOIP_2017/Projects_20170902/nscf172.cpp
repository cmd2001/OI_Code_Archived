#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define war cerr
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const double eps=1e-8;

struct Splay
{
	struct node
	{
		double s;
		int siz;
		node *fa,*lson,*rson;
		node(double xx=0)
		{
			s=xx;
		}
	}SPLAY[maxn],*root;
	
	node* newnode()
	{
		static int cnt;
		return &SPLAY[++cnt];
	}
	Splay()
	{
		root=newnode();
		root->s=40000; //max dis is 37994
		root->siz=1;
	}
	
	inline void update(node* pos)
	{
		pos->siz=1;
		if(pos->lson) pos->siz+=pos->lson->siz;
		if(pos->rson) pos->siz+=pos->rson->siz;
	}
	
	void zig(node* pos)
	{
		//debug<<"zig pos = "<<pos-SPLAY<<endl;
		node *son=pos->lson;
		if(pos->fa)
		{
			if(pos==pos->fa->lson) pos->fa->lson=son;
			else if(pos==pos->fa->rson) pos->fa->rson=son;
			else war<<"Fuck you!"<<endl;
		}
		else if(pos==root) root=son;
		else war<<"Fuck you!"<<endl;
		son->fa=pos->fa;
		pos->lson=son->rson;
		if(pos->lson) pos->lson->fa=pos;
		son->rson=pos;
		pos->fa=son;
		update(pos);
		update(son);
	}
	void zag(node* pos)
	{
		//debug<<"zag pos  = "<<pos-SPLAY<<endl;
		node *son=pos->rson;
		if(pos->fa)
		{
			if(pos==pos->fa->lson) pos->fa->lson=son;
			else if(pos==pos->fa->rson) pos->fa->rson=son;
			else war<<"Fuck you!"<<endl;
		}
		else if(pos==root) root=son;
		else war<<"Fuck you!"<<endl;
		//debug<<"first complete"<<endl;
		son->fa=pos->fa;
		pos->rson=son->lson;
		if(pos->rson) pos->rson->fa=pos;
		son->lson=pos;
		pos->fa=son;
		update(pos);
		update(son);
	}
	
	inline void splay_to_root(node* pos)
	{
		//debug<<"in to root pos = "<<pos-SPLAY<<endl;
		static node* fa;
		while(pos!=root)
		{
			fa=pos->fa;
			if(!fa) war<<"No fa && pos != root"<<endl;
			if(!fa->fa)
			{
				if(pos==fa->lson) zig(fa);
				else if(pos==fa->rson) zag(fa);
				else war<<"Not double son @ 90"<<endl;
			}
			else
			{
				node *ffa=fa->fa;
				if(fa==ffa->lson) zig(ffa);
				else if(fa==ffa->rson) zag(ffa);
				else war<<"Not double son @ 97"<<endl;
				fa=pos->fa;
				if(pos==fa->lson) zig(fa);
				else if(pos==fa->rson) zag(fa);
				else war<<"Not double son @ 101"<<endl;
			}
		}
	}
	
	void insert(double x)
	{
		//debug<<"inserting x = "<<x<<endl;
		node *pos=root;
		while(1)
		{
			//debug<<"pos = "<<pos-SPLAY<<endl;
			pos->siz++;
			if(x<pos->s)
			{
				if(pos->lson) pos=pos->lson;
				else
				{
					pos->lson=newnode();
					pos->lson->s=x;
					pos->lson->siz=1;
					pos->lson->fa=pos;
					pos=pos->lson;
					break;
				}
			}
			else
			{
				if(pos->rson) pos=pos->rson;
				else
				{
					pos->rson=newnode();
					pos->rson->s=x;
					pos->rson->siz=1;
					pos->rson->fa=pos;
					pos=pos->rson;
					break;
				}
			}
		}
		//debug<<"inserted to splay to root"<<endl;
		splay_to_root(pos);
	}
	
	inline int getrank(double x)
	{
		//debug<<"in getrank x = "<<x<<endl;
		int ret=0;
		node* pos=root;
		while(1)
		{
			if(x<pos->s)
			{
				if(pos->lson) pos=pos->lson;
				else return ret;
			}
			else
			{
				ret+=pos->siz-(pos->rson?pos->rson->siz:0);
				if(pos->rson) pos=pos->rson;
				else return ret;
			}
		}
	}
}splay;

struct target
{
	double x,y;
	double s1,s2;
	friend bool operator < (const target &a,const target &b)
	{
		return a.s1<b.s1;
	}
}tar[maxn];

int n,ans;
double x1,yy1,x2,y2,t;
double getdis(double x,double y,double a,double b)
{
	return ((x-a)*(x-a)+(y-b)*(y-b))*(double)3.141;
}

int main()
{
	scanf("%d",&n);
	scanf("%lf%lf%lf%lf%lf",&x1,&yy1,&x2,&y2,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf",&tar[i].x,&tar[i].y);
		tar[i].s1=getdis(x1,yy1,tar[i].x,tar[i].y);
		tar[i].s2=getdis(x2,y2,tar[i].x,tar[i].y);
	}
	
	
	sort(tar+1,tar+1+n);
	
	
	for(int i=n;i;i--)
	{
		if(t>=tar[i].s1)
		{
			ans=max(ans,i+splay.getrank(t-tar[i].s1));
		}
		splay.insert(tar[i].s2);
	}
	
	printf("%d\n",n-ans);
		
}
		
	
