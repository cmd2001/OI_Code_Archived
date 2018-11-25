#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define N 10001
#define M 1000001
using namespace std;
int n,q,m,block;
int c[N],pos[N],pre[N],b[N],last[M];
int find(int x,int v)
{
    int l=(x-1)*block+1,r=min(x*block,n);
    int first=l;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(pre[mid]<v)l=mid+1;
        else r=mid-1;
    }
    return l-first;
}
void reset(int x)
{
    int l=(x-1)*block+1,r=min(x*block,n);
    for(int i=l;i<=r;i++)pre[i]=b[i];
    sort(pre+l,pre+r+1);
}
void build()
{
    for(int i=1;i<=n;i++)
    {
        b[i]=last[c[i]];
        last[c[i]]=i;
        pos[i]=(i-1)/block+1;
    }
    for(int i=1;i<=m;i++)reset(i);
}
int ask(int l,int r)
{
    int ans=0;
    if(pos[l]==pos[r])
    {
        for(int i=l;i<=r;i++)if(b[i]<l)ans++;
    }
    else 
    {
        for(int i=l;i<=block*pos[l];i++)if(b[i]<l)ans++;
        for(int i=block*(pos[r]-1)+1;i<=r;i++)if(b[i]<l)ans++;
    }
    for(int i=pos[l]+1;i<pos[r];i++)
        ans+=find(i,l);
    return ans;
}
void change(int x,int v)
{
    for(int i=1;i<=n;i++)last[c[i]]=0;
    c[x]=v;
    for(int i=1;i<=n;i++)
    {
        int t=b[i];
        b[i]=last[c[i]];
        if(t!=b[i])reset(pos[i]);
        last[c[i]]=i;
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]);
    block=int(sqrt(n)+log(2*n)/log(2));
    if(n%block)m=n/block+1;
    else m=n/block;
    build();
    char ch[5];int x,y;
    for(int i=1;i<=q;i++)
    {
        scanf("%s%d%d",ch,&x,&y);
        if(ch[0]=='Q')printf("%d\n",ask(x,y));
        else change(x,y);
    }
    return 0;
}
