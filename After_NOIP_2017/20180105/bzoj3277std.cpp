#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#include<cmath>  
#define N 200003  
#define LL long long   
using namespace std;  
int n,m,np,nq,p,q,cnt,root,last,len,sz;  
int ch[N][20],fa[N],size[N],l[N],nxt[N],a[N],now,pd[N],mark[N],v[N],pos[N];  
int point[N],next[N],vi[N],tot,tt;  
int head[N],nt[N];  
LL c[N];  
char s[N];  
void add(int x,int y)  
{  
    tot++; next[tot]=point[x]; point[x]=tot; vi[tot]=y;  
}  
void addfa(int x,int y)  
{  
    tt++; nt[tt]=head[x]; head[x]=tt; v[tt]=y;   
    //cout<<x<<" "<<y<<endl;  
}  
void extend(int x)  
{  
    int c=a[x];  
    p=last; np=++cnt; last=np;  
    l[np]=l[p]+1;  
    for (;p&&!ch[p][c];p=fa[p]) ch[p][c]=np;  
    if (!p) fa[np]=root;  
    else {  
        q=ch[p][c];  
        if (l[q]==l[p]+1) fa[np]=q;  
        else {  
            nq=++cnt; l[nq]=l[p]+1;  
            memcpy(ch[nq],ch[q],sizeof ch[nq]); size[nq]=size[q]; nxt[nq]=nxt[q];  
            fa[nq]=fa[q];  
            fa[q]=fa[np]=nq;  
            for (;ch[p][c]==q;p=fa[p]) ch[p][c]=nq;  
        }  
    }  
    add(now,np);  
    for (;np;np=fa[np])  
     if (nxt[np]!=now) {  
        nxt[np]=now;  
        size[np]++;  
     }  
     else break;  
}  
void dfs(int x)  
{  
    c[x]+=c[fa[x]];  
    for (int i=head[x];i;i=nt[i])  
     dfs(v[i]);  
}  
int main()  
{  
    scanf("%d%d",&n,&m);  
    root=++cnt;  
    for(int i=1;i<=n;i++){  
        scanf("%s",s+1);  
        last=root;  
        len=strlen(s+1); now=i;  
        for (int j=1;j<=len;j++) a[++sz]=s[j]-'a',extend(sz);  
        mark[i]=sz;  
    }  
    for (int i=1;i<=cnt;i++) v[l[i]]++;
    for (int i=1;i<=cnt;i++) v[i]+=v[i-1];  
    for (int i=1;i<=cnt;i++) pos[v[l[i]]--]=i;  
    for (int i=1;i<=cnt;i++) {  
        int t=pos[i];  
        addfa(fa[t],t);  
        if (size[t]>=m) c[t]=(LL)(l[t]-l[fa[t]]);  
        else c[t]=0;  
    }  
    c[1]=0;  
    dfs(1);  
    for (int i=1;i<=n;i++) {  
        LL ans=0;  
        for (int j=point[i];j;j=next[j])  
         ans+=c[vi[j]];  
        printf("%I64d ",ans);  
    }  
}  
