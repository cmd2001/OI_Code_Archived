#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
#define N 1050
#define inf 0x3fffffff
using namespace std;
int e=2,head[N];
struct edge{
    int u,v,f,next;
}ed[N*N<<1];
void add(int u,int v,int f){
    ed[e].u=u;ed[e].v=v;ed[e].f=f;
    ed[e].next=head[u];head[u]=e++;
    ed[e].u=v;ed[e].v=u;ed[e].f=0;
    ed[e].next=head[v];head[v]=e++;
}
int dep[N],S,T;
bool bfs(){
    memset(dep,0,sizeof dep);
    queue<int> q;q.push(S);dep[S]=1;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=head[x];i;i=ed[i].next){
            if(ed[i].f&&!dep[ed[i].v]){
                dep[ed[i].v]=dep[x]+1;
                if(ed[i].v==T)return 1;
                q.push(ed[i].v);
            }
        }
    }
    return 0;
}
int dfs(int x,int f){
    if(x==T||!f)return f;
    int ans=0;
    for(int i=head[x];i;i=ed[i].next){
        if(ed[i].f&&dep[ed[i].v]==dep[x]+1){
            int nxt=dfs(ed[i].v,min(f,ed[i].f));
            ans+=nxt;f-=nxt;ed[i].f-=nxt;ed[i^1].f+=nxt;
        }
    }
    if(!ans)dep[x]=-1;
    return ans;
}
int dinic(){
    int ans=0;
    while(bfs())ans+=dfs(S,inf);
    return ans;
}
int cnt[20]={0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
int n,K,m,p,c[N],id[N],x[N],y[N],a[5][55];
int fa[N];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
struct data{int u,v,w,x;}d[N*10];
bool cmp1(data a,data b){return y[a.u]<y[b.u];}
bool cmp2(int a,int b){return y[a]<y[b];}
char s[N];
int in[N],w[55][17],f[55][215][17],ans;
void getmax(int &x,int y){x>y?x=x:x=y;}
int main(){
    scanf("%d%d%d%d%s",&n,&K,&m,&p,s+1);
    S=m+1;T=S+1;
    register int i,j,k,l,s1,s2,l1,r1,l2,r2,V,now;
    for(i=1;i<=m;i++)
        scanf("%d",&c[i]),id[i]=fa[i]=i;
    for(i=1;i<=K;i++)
        for(j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            x[a[i][j]]=i;y[a[i][j]]=j;
        }
    for(i=1;i<=p;i++){
        double x;
        scanf("%d%d%d%lf",&d[i].u,&d[i].v,&d[i].w,&x);
        d[i].x=d[i].w*x;
        if(find(d[i].u)!=find(d[i].v))fa[fa[d[i].u]]=fa[d[i].v];
    }
    for(i=1;i<=m;i++){
        if(y[find(i)])y[i]=y[fa[i]];
        if(!y[fa[i]]&&y[i])y[fa[i]]=y[i];
    }
    for(i=1;i<=m;i++){
        if(!y[fa[i]])y[fa[i]]=1;
        y[i]=y[fa[i]];
    }
    sort(d+1,d+p+1,cmp1);
    sort(id+1,id+m+1,cmp2);
    for(l=0;l<=(n-1)*K;l++){
        if(!l||(floor(10*log(1.0*l))!=floor(10*log(1.0*(l+1))))){
            V=floor(10*log(1.0*(l+1)));
            for(i=1,l1=1,r1=0,l2=1,r2=0;i<=n;i++){
                while(r1<p&&y[d[r1+1].u]==i)r1++;
                while(r2<m&&y[id[r2+1]]==i)r2++;
                for(j=0;j<(1<<K);j++){
                    e=2;now=head[S]=head[T]=0;
                    for(k=l2;k<=r2;k++)in[id[k]]=head[id[k]]=0;
                    for(k=l1;k<=r1;k++){
                        now+=V*d[k].w*2;
                        in[d[k].u]+=V*(d[k].w-d[k].x);
                        in[d[k].v]+=V*(d[k].w-d[k].x);
                        add(d[k].u,d[k].v,V*(d[k].w+d[k].x));
                        add(d[k].v,d[k].u,V*(d[k].w+d[k].x));
                    }
                    for(k=l2;k<=r2;k++){
                        if(!x[id[k]])add(S,id[k],c[id[k]]*2+in[id[k]]),add(id[k],T,0);
                        else if(j&(1<<x[id[k]]-1))add(S,id[k],c[id[k]]*2+in[id[k]]),add(id[k],T,inf);
                        else add(S,id[k],inf),add(id[k],T,0);
                    }
                    w[i][j]=(now-dinic())/2;
                }
                l1=r1+1;l2=r2+1;
            }
        }
        memset(f,-0x3f,sizeof f);
        for(i=0;i<(1<<K);i++)f[1][0][i]=w[1][i];
        for(i=1;i<n;i++)
            for(j=0;j<=l&&j<=(i-1)*K;j++)
                for(s1=0;s1<(1<<K);s1++)if(f[i][j][s1]!=f[0][0][0])
                    for(s2=0;s2<(1<<K);s2++)
                        getmax(f[i+1][j+cnt[s1^s2]][s2],f[i][j][s1]+w[i+1][s2]);
        for(i=0;i<(1<<K);i++)ans=max(ans,f[n][l][i]);
    }
    printf("%d\n",ans);
    return 0;
}
