#include<bits/stdc++.h>
#define debug cout
const int maxn=1e3+1e2;
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
    if(gfa)
    {
        treap[pos].fa=treap[fa].fa;
        if(treap[gfa].lson==fa) treap[gfa].lson=pos;
        else treap[gfa].rson=pos;
    }
    else treap[pos].fa=0,s=pos;
    if(treap[pos].lson)
    {
        treap[fa].lson=treap[pos].rson;
        treap[treap[pos].rson].fa=fa;
    }
    else treap[fa].lson=0;
    treap[pos].rson=fa;
    treap[fa].fa=pos;
}
void lrot(int pos)
{
    const int fa=treap[pos].fa,gfa=treap[treap[pos].fa].fa;
    if(gfa)
    {
        treap[pos].fa=gfa;
        if(treap[gfa].lson==fa) treap[gfa].lson=pos;
        else treap[gfa].rson=pos;
    }
    else treap[pos].fa=0,s=pos;
    if(treap[pos].lson)
    {
        treap[fa].rson=treap[pos].lson;
        treap[treap[pos].lson].fa=fa;
    }
    else treap[fa].rson=0;
    treap[pos].lson=fa;
    treap[fa].fa=pos;
}
void nodedebug()
{
    for(int i=0;i<=cnt;i++)
    {
        debug<<"Node"<<i<<endl;
        debug<<treap[i].dat<<"    "<<treap[i].hpd<<endl;
        debug<<treap[i].lson<<"   "<<treap[i].rson<<endl;
        debug<<treap[i].fa<<endl;
    }
}
void fix(int pos)
{
    debug<<"fixing="<<pos<<endl;
    debug<<"before"<<endl;
    nodedebug();
    if(pos==treap[treap[pos].fa].lson) rrot(pos);
    else lrot(pos);
    if(!treap[pos].fa) {s=pos;return;}
    debug<<"after"<<endl;
    nodedebug();
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
    //debug<<"pos="<<pos<<endl;
    debug<<treap[pos].dat<<endl;
    if(x==treap[pos].dat) return 1;
    else return 0;
}
int main()
{
    srand(1);
    int m,n;
    scanf("%d%d",&n,&m);
    scanf("%d",&treap[++cnt].dat),treap[cnt].hpd=rand(),s=cnt;
    for(int i=1,x;i<n;i++)
    {
        scanf("%d",&x);
        //debug<<"inserting num="<<x<<endl;
        insert(x);
    }
    nodedebug();
    for(int i=1,x;i<=m;i++)
    {
        scanf("%d",&x);
        debug<<"x="<<x<<endl;
        if(tpfind(x)) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}




