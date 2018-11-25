#include<bits/stdc++.h>
const int maxn=1e3+1e2;
using namespace std;
struct node
{
    int lson,rson,dat,hpds,siz,fa;
    friend bool operator < (const node &a,const node &b){return a.dat<b.dat;}
    friend bool cmp (const node &a,const node &b) {return a.hpd<b.hpd;}
}treap[maxn];
void calcsiz(int pos)
{
    const int &lson=treap[pos].lson,rson=treap[pos].rson;
    treap[pos].siz=treap[lson].siz+treap[rson].siz;
}
void rrot(int pos)
{
    const int &fa=treap[pos].fa;
    treap[pos].fa=treap[fa].fa;
    treap[fa].lson=treap[pos].rson;
    treap[treap[pos].rson].fa=fa;
    treap[pos].rson=fa;
    treap[fa].fa=pos;
    calcsiz(treap[pos].rson);
    calcsiz(pos);
}
void lrot(int pos)
{
    const int &fa=treap[pos].fa;
    treap[pos].fa=treap[fa].fa;
    treap[fa].rson=treap[pos].lson;
    treap[treap[pos].lson].fa=fa;
    treap[pos].lson=fa;
    treap[fa].fa=pos;
    calcsiz(treap[pos].lson);
    calcsiz(pos);
}
void insrt()
{

