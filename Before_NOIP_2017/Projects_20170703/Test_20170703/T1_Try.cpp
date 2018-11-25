#include<bits/stdc++.h>
using namespace std;
const int maxn=35,maxl=1e2+1e1;

bool ccmp(const char *a,const char *b)
{
    int la=strlen(a),lb=strlen(b);
    int len=min(la,lb);
    for(int i=0;i<len;i++)
    {
        if(a[i]<b[i]) return 1;
        if(a[i]>b[i]) return 0;
    }
    return la<lb;
}
bool jeq(const char *a,const char *b,int la)
{
    int lb=strlen(b);
    if(la!=lb) return 0;
    for(int i=0;i<len;i++) if(a[i]!=b[i]) return 0;
    return 1;
}
struct node
{
    char str[maxl],*nxt[maxn];
    bool sta;
    int cnt;
    friend bool operator < (const node a,const node b)
    {
        return a.sta==b.sta?a.sta<b.sta:ccmp(a.str,b.str);
    }
}books[maxl],st;
bool cmp(const node* a,const node* b)
{
    return *a<*b;
}

inline void book_insert(char *c,node *pos) // inserting to pos's sub directory
{
    int l=strlen(c);
    for(i=0;i<l;i++)
    {
        if(c[i]=='/') break;
    }
    for(int k=1;k<=pos->cnt;k++)
    {
        if()

