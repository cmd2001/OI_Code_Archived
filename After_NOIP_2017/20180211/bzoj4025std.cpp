#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 100100
using namespace std;

struct edge{
    int x,y;
    int st,ed;
    edge() {}
    edge(int _,int __,int ___,int ____):
        x(_),y(__),st(___),ed(____) {}
};

int n,m,T;
int stack[M<<2],top;
//若x<0 代表x的rank被加了1
//若x>0 表示x的父亲被修改了 

namespace Union_Find_Set{
    int fa[M],rank[M],a[M];
    int Find(int x)
    {
        while(fa[x]!=x)
            x=fa[x];
        return fa[x]=x;
    }
    int Distance(int x)
    {
        int re=0;
        while(fa[x]!=x&&fa[x])
            re^=a[x],x=fa[x];
        return re;
    }
    void Union(int x,int y,int z)
    {
        x=Find(x);y=Find(y);
        if(x==y) return ;
        if(rank[x]>rank[y])
            swap(x,y);
        if(rank[x]==rank[y])
            rank[y]++,stack[++top]=-y;
        fa[x]=y;a[x]=z;stack[++top]=x;
    }
    void Restore(int bottom)
    {
        while(top>bottom)
        {
            if(stack[top]<0)
                rank[-stack[top]]--;
            else
                fa[stack[top]]=stack[top],a[stack[top]]=0;
            top--;
        }
    }
}

void Divid_And_Conquer(int x,int y,vector<edge> &e)
{
    using namespace Union_Find_Set;
    vector<edge>::iterator it;
    int i,mid=x+y>>1,bottom=top;
    vector<edge> l,r;
    for(it=e.begin();it!=e.end();it++)
    {
        if(it->st==x&&it->ed==y)
        {
            int _x=Find(it->x);
            int _y=Find(it->y);
            int _z=Distance(it->x)^Distance(it->y)^1;
            if(_x!=_y)
                Union(_x,_y,_z);
            else if(_z&1)
            {
                for(i=x;i<=y;i++)
                    puts("No");
                Restore(bottom);
                return ;
            }
        }
        else if(it->ed<=mid)
            l.push_back(*it);
        else if(it->st>mid)
            r.push_back(*it);
        else
            l.push_back(edge(it->x,it->y,it->st,mid)),r.push_back(edge(it->x,it->y,mid+1,it->ed));
    }
    if(x==y)
        puts("Yes");
    else
        Divid_And_Conquer(x,mid,l),Divid_And_Conquer(mid+1,y,r);
    Restore(bottom);
}

int main()
{
    int i;
    edge e;
    vector<edge> v;
    cin>>n>>m>>T;
    for(i=1;i<=n;i++)
        Union_Find_Set::fa[i]=i;
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&e.x,&e.y,&e.st,&e.ed);
        e.st++;
        if(e.st>e.ed)
            continue;
        v.push_back(e);
    }
    Divid_And_Conquer(1,T,v);
    return 0;
}
