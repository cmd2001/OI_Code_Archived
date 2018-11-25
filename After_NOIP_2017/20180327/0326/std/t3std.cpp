#include<cstdio>
#include<algorithm>
#define N 1000010
using namespace std;
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
inline int read(){
    int x=0;char ch=gc();
    while(ch<'0'||ch>'9') ch=gc();
    while(ch<='9'&&ch>='0') x=x*10+ch-'0',ch=gc();
    return x;
}
struct node{
    int y,next;
}data[N<<1];
int fa[N],h[N],leaf[N],w[N],a,b,n,num;
inline void dfs(int x){
    int cnt=0,mx1=0,mx2=0;
    for (int i=h[x];i;i=data[i].next){
        int y=data[i].y;if (y==fa[x]) continue;fa[y]=x;++cnt;dfs(y);
        if (w[y]>mx1) mx2=mx1,mx1=w[y];else if (w[y]>mx2) mx2=w[y];
    }w[x]=(leaf[x]=cnt)+mx2;
}
inline bool check(int md){
    int last=a,x=a,all=1,ans=0,sum=0;
    for (int i=a;i!=b;i=fa[i]) all+=leaf[i]-1;
    while(x!=b){
        int ans1=0;++sum;
        for (int i=h[x];i;i=data[i].next){
            int y=data[i].y;if (y==last||y==fa[x]) continue;
            if (all+w[y]+ans>md) ++ans1,--sum;
            if(sum<0) return 0;
        }
        ans+=ans1;all-=leaf[x]-(last!=x);
        last=x;x=fa[x];
        if (ans>md) return 0;
    }
    return ans<=md?1:0;
}
int main(){
    n=read();b=read();a=read();
    for (int i=1;i<n;++i){
        int x=read(),y=read();
        data[++num].y=y;data[num].next=h[x];h[x]=num;
        data[++num].y=x;data[num].next=h[y];h[y]=num;
    }
    dfs(b);int l=0,r=n<<1;
    while(l<=r){
        int mid=l+r>>1;
        if(check(mid)) r=mid-1;else l=mid+1;
    }printf("%d\n",l);
    return 0;
}