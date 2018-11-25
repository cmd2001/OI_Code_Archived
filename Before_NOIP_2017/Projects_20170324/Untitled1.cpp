#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=3*1e5+1e2;
int dat[maxn],lson[maxn],rson[maxn],dis[maxn],cnt;
int n,m;
void merge(int x,int y)//merge y to x
{
    //dat[x]>=dat[y]
    if(!rson[x]) rson[x]=y;
    else if(rson[x]&&dat[rson[x]]>=dat[y]) merge(rson[x],y);
    else if(rson[x]&&dat[rson[x]]<dat[y]) {merge(y,rson[x]);rson[x]=y;}
    if(dis[rson[x]]>dis[lson[x]]) swap(lson[x],rson[x]);
    dis[x]=dis[rson[x]]+1;
    return;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",dat+i);
    for(int i=2;i<=n;i++) merge(1,i);
    return 0;
}





