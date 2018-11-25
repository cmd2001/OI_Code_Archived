#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
struct node
{
    int pos,state;//mark==1
}que[maxn];
int cnt,ans[maxn],fa[maxn],m,n;
int tme[maxn];
int anst;
int marked[maxn];
int findmark(int x)
{
    if(tme[marked[x]]) return marked[x];
    return marked[x]==x?x:marked[x]=findmark(fa[x]);
}
int main()
{
    marked[1]=1;
    tme[1]=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) marked[i]=1;
    for(int i=1,a,b;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        fa[b]=a;
    }
    char c[10];
    for(int i=1,x;i<=m;i++)
    {
        //debug<<i<<endl;
        scanf("%s%d",c,&x);
        if(c[0]=='C')
        {
            que[++cnt].pos=x;
            que[cnt].state=1;
            marked[x]=x;
            tme[x]++;
        }
        else if(c[0]=='Q')
        {
            que[++cnt].pos=x;
            que[cnt].state=0;
        }
    }
    for(int i=cnt;i>0;i--)
    {
        if(que[i].state)
        {
            tme[que[i].pos]--;
            if(!tme[que[i].pos]) marked[que[i].pos]=findmark(fa[que[i].pos]);
        }
        else
        {
            ans[++anst]=findmark(que[i].pos);
        }
    }
    for(int i=anst;i>0;i--)
    {
        if(ans[i]) printf("%d\n",ans[i]);
        else printf("1\n");
    }
    return 0;
}

