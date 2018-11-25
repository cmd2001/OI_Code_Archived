#include<iostream>  
#include<cstdio>  
#define N 1610  
#define M 15005  
#define inf 99999999  
using namespace std;  
struct edge{  
    int e,q,f,next;  
} ed[M*4];  
int n,m,s,e,q,i,ne=1,nd,t,j,a[N],d[N],que[N*10],inq[N],last[N],road[N],minf[N];  
void add(int s,int e,int f,int q)  
{  
    ed[++ne].e=e;ed[ne].f=f;  
    ed[ne].q=q;  
    ed[ne].next=a[s];a[s]=ne;  
}  
bool spfa(int s,int t)  
{  
    int head=1,tail=1,hh=1,tt=1,get,i,j,to;  
    for (i=0;i<=nd;i++) inq[i]=0,last[i]=road[i]=-1,d[i]=inf;  
    que[1]=s;inq[s]=1;d[s]=0;minf[s]=inf;  
    while (hh<=tt)  
    {  
        get=que[head++];hh++;  
        if (head>16000) head=1;  
        for (j=a[get];j;j=ed[j].next)  
            if (ed[j].f&&ed[j].q+d[get]<d[to=ed[j].e])  
            {  
                d[to]=d[get]+ed[j].q;  
                minf[to]=min(minf[get],ed[j].f);  
                last[to]=get;road[to]=j;  
                if (!inq[to])  
                {  
                    tail++;tt++;  
                    if (tail>16000) tail=1;  
                    que[tail]=to;inq[to]=1;  
                }  
            }  
        inq[get]=0;  
    }  
    return last[t]!=-1;  
}  
int fyl(int s,int t)  
{  
    int i,ans=0,j;  
    while (spfa(s,t))  
    {  
        i=t;ans+=minf[t]*d[t];  
        while (last[i]!=-1)  
        {  
            j=road[i];  
            ed[j].f-=minf[t];ed[j^1].f+=minf[t];  
            i=last[i];  
        }  
    }  
    return ans;  
}  
int main()  
{  
    //freopen("1927.in","r",stdin);  
    scanf("%d%d",&n,&m);  
    nd=2*n+1;  
    for (i=0;i<=nd;i++) a[i]=0;  
    for (i=1;i<=n;i++)  
    {  
        scanf("%d",&t);  
        add(0,i,1,0);add(i,0,0,0);  
        add(0,i+n,inf,t);add(i+n,0,0,-t);  
    }  
    for (i=1;i<=m;i++)  
    {  
        scanf("%d%d%d",&s,&e,&q);  
        if (s>e) swap(s,e);  
        add(s,e+n,1,q);add(e+n,s,0,-q);  
    }  
    for (i=1;i<=n;i++)   
        add(i+n,nd,1,0),add(nd,i+n,0,0);  
    printf("%d\n",fyl(0,nd));  
}  