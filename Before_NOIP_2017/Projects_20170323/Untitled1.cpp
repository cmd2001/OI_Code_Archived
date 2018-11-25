#include<bits/stdc++.h>
#define debug cout
const int maxn=1e6+1e2;
using namespace std;
struct node
{
    int lson,rson,dat,hpd,fa;
    friend bool operator < (const node &a,const node &b){return a.dat<b.dat;}
}treap[maxn];
int cnt,s;
void rrot(int pos)
{
    const int fa=treap[pos].fa,gfa=treap[treap[pos].fa].fa;
    treap[pos].fa=gfa;
    if(gfa)
    {
        if(treap[gfa].lson==fa) treap[gfa].lson=pos;
        else treap[gfa].rson=pos;
    }
    else s=pos;
    treap[fa].lson=treap[pos].rson;
    if(treap[pos].rson) treap[treap[pos].rson].fa=fa;
    treap[pos].rson=fa;
    treap[fa].fa=pos;
}
void lrot(int pos)
{
    const int fa=treap[pos].fa,gfa=treap[treap[pos].fa].fa;
    treap[pos].fa=gfa;
    if(gfa)
    {
        if(treap[gfa].lson==fa) treap[gfa].lson=pos;
        else treap[gfa].rson=pos;
    }
    else s=pos;
    treap[fa].rson=treap[pos].lson;
    if(treap[pos].lson) treap[treap[pos].lson].fa=fa;
    treap[pos].lson=fa;
    treap[fa].fa=pos;
}
void fix(int pos)
{
    if(pos==treap[treap[pos].fa].lson) rrot(pos);
    else lrot(pos);
    if(!treap[pos].fa) {s=pos;return;}
    if(treap[pos].hpd<treap[treap[pos].fa].hpd) fix(pos);
}
void insert(int x)
{
    treap[++cnt].dat=x,treap[cnt].hpd=rand();
    int pos=s;
    while(1)
    {
        if(treap[cnt]<treap[pos])
        {
            if(treap[pos].lson) pos=treap[pos].lson;
            else
            {
                treap[pos].lson=cnt;
                treap[cnt].fa=pos;
                break;
            }
        }
        else
        {
            if(treap[pos].rson) pos=treap[pos].rson;
            else
            {
                treap[pos].rson=cnt;
                treap[cnt].fa=pos;
                break;
            }
        }
    }
    pos=cnt;
    if(treap[pos].hpd<treap[treap[pos].fa].hpd) fix(pos);
}
bool tpfind(int x)
{
    int pos=s;
    while(1)
    {
        if(x==treap[pos].dat) return 1;
        if(x<treap[pos].dat)
            if(treap[pos].lson )pos=treap[pos].lson;
            else break;
        else
            if(treap[pos].rson) pos=treap[pos].rson;
            else break;
    }
    if(x==treap[pos].dat) return 1;
    else return 0;
}
int main()
{
    srand(time(NULL));
    int m,n;
    scanf("%d%d",&n,&m);
    scanf("%d",&treap[++cnt].dat),treap[cnt].hpd=rand(),s=cnt;
    for(int i=1,x;i<n;i++)
    {
        scanf("%d",&x);
        insert(x);
    }
    for(int i=1,x;i<=m;i++)
    {
        scanf("%d",&x);
        if(tpfind(x)) printf("1 ");
        else printf("0 ");
    }

    return 0;
}




