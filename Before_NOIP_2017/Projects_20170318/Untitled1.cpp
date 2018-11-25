#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
struct node
{
    bool sta;
    int pos,x,at,ans;
    friend bool operator < (const node &a,const node &b){return a.pos<b.pos;}
}que[2*maxn];
int in[maxn],srt[maxn],data[2*maxn],out[maxn],m,n,len;
void update(int pos)
{
    while(pos<=len)
    {
        data[pos]++;
        pos+=lowbit(pos);
    }
}
int query(int pos)
{
    int ret=0;
    while(pos)
    {
        ret+=data[pos];
        pos-=lowbit(pos);
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i),srt[i]=in[i];
    sort(srt+1,srt+1+n);
    len=unique(srt+1,srt+1+n)-srt-1;
    for(int i=1;i<=n;i++) in[i]=lower_bound(srt+1,srt+1+len,in[i])-srt;
    for(int i=1,s,e,x;i<=m;i++)
    {
        scanf("%d%d%d",&s,&e,&x);
        //s++,e++;
        int p=lower_bound(srt+1,srt+1+len,x)-srt;
        if(srt[p]!=x) p--;
        que[i].at=que[i+n].at=i;
        que[i].x=que[i+n].x=p;
        que[i].pos=s-1,que[i+n].pos=e;
        que[i].sta=1;
    }
    sort(que+1,que+1+2*n);
    int t=1;
    for(int i=1;i<=2*n;i++)
    {
        int &maxp=que[i].pos;
        while(t<=maxp) update(in[t++]);
        que[i].ans=query(que[i].x);
    }
    for(int i=1;i<=2*n;i++)
    {
        if(que[i].sta) out[que[i].at]-=que[i].ans;
        else out[que[i].at]+=que[i].ans;
    }
    for(int i=1;i<=n;i++) printf("%d\n",out[i]);
    return 0;
}
