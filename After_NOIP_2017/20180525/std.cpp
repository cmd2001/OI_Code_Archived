#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cmath>  
#include<cstring>  
#define N 150003  
using namespace std;  
int n,m,top,st[N],father[N],rev[N],a[N];  
int belong[N],fa[N],ch[N][2],val[N],mx[N];  
int read()  
{  
    char c=getchar();  
    for (;c>'9'||c<'0';c=getchar());  
    int num=0;  
    for (;c>='0'&&c<='9';c=getchar())    
        num=num*10+c-'0';  
    return num;  
}  
int findset(int x)  
{  
    if (belong[x]==x) return x;  
    belong[x]=findset(belong[x]);  
    return belong[x];  
}  
int find(int x)  
{  
    if (father[x]==x) return x;  
    father[x]=find(father[x]);  
    return father[x];  
}  
int isroot(int x)  
{  
    int f=findset(fa[x]);  
    return ch[f][1]!=x&&ch[f][0]!=x;  
}  
int get(int x)  
{  
    return ch[findset(fa[x])][1]==x;  
}  
void update(int x)  
{  
    mx[x]=val[x];  
    if (ch[x][0]) mx[x]+=mx[ch[x][0]];  
    if (ch[x][1]) mx[x]+=mx[ch[x][1]];  
}  
void pushdown(int x)  
{  
    if (rev[x]){  
        swap(ch[x][0],ch[x][1]);  
        rev[ch[x][1]]^=1; rev[ch[x][0]]^=1;  
        rev[x]=0;  
    }  
}  
void rotate(int x)  
{  
    int y=fa[x]; int z=fa[y]; int which=get(x);  
    if (!isroot(y)) ch[z][ch[z][1]==y]=x;  
    ch[y][which]=ch[x][which^1]; fa[ch[x][which^1]]=y;  
    ch[x][which^1]=y; fa[y]=x; fa[x]=z;  
    update(y); update(x);  
}  
void splay(int x)  
{  
    top=0; st[++top]=x;  
    for (int i=x;!isroot(i);i=findset(fa[i]))  
        st[++top]=findset(fa[i]);  
    for (int i=top;i>=1;i--) pushdown(st[i]),fa[st[i]]=findset(fa[st[i]]);  
    int y;  
    while (!isroot(x)){  
        y=fa[x];  
        if (!isroot(y)) rotate(get(x)==get(y)?y:x);  
        rotate(x);  
    }  
}  
void access(int x)  
{  
    int t=0;  
    while (x){  
        splay(x);  
        ch[x][1]=t;  
        update(x);  
        t=x; x=findset(fa[x]);  
    }  
}  
void rever(int x)  
{  
    access(x); splay(x); rev[x]^=1;  
}  
void link(int x,int y)  
{  
    rever(x); fa[x]=y;  
}  
void merge(int x,int y)  
{  
    belong[findset(x)]=findset(y); pushdown(x);  
    if (x!=y) val[y]+=val[x];  
    //fa[x]=0;  
    if (ch[x][0]) merge(ch[x][0],y);  
    if (ch[x][1]) merge(ch[x][1],y);  
    ch[x][1]=ch[x][0]=0;  
}  
int main()  
{   
    n=read();  
    m=read();  
    for (int i=1;i<=n;i++){  
        val[i]=read(); a[i]=val[i];  
        belong[i]=i; father[i]=i;  
    }  
    for (int i=1;i<=m;i++) {  
        int opt,x,y; opt=read(); x=read(); y=read();  
        if (opt==1) {  
            x=findset(x); y=findset(y);  
            if (x==y) continue;  
            int r1=find(x); int r2=find(y);  
            if (r1!=r2) {  
                father[r2]=r1;  
                link(x,y);  
            }  
            else {  
                rever(x); access(y); splay(y);   
                merge(y,y); update(y);  
            }  
        }  
        if (opt==2) {  
            int xx=x;  
            x=findset(x);  
            access(x); splay(x); val[x]+=y-a[xx]; a[xx]=y;  
            update(x);   
        }  
        if (opt==3) {  
            x=findset(x); y=findset(y);  
            if (find(x)!=find(y)) {  
                printf("-1\n");  
                continue;  
            }  
            rever(x); access(y); splay(y); printf("%d\n",mx[y]);  
        }  
    }  
}  