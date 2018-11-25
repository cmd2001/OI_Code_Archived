#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=31000;
struct node
{
    int nxt[3],fa,fail,dat;
    bool end;
}trie[maxn];
int cnt,n;
int que[maxn],s,e;
char in[maxn];
void build(char *s,int pos,int at,int len)
{
    if(at==len) {trie[pos].end=1;return;}
    else
    {
        if(trie[pos].nxt[s[at]-48]) build(s,trie[pos].nxt[s[at]-48],at+1,len);
        else
        {
            trie[pos].nxt[s[at]-48]=++cnt;
            trie[cnt].fa=pos;
            trie[cnt].dat=s[at]-48;
            build(s,cnt,at+1,len);
        }
    }
}
void bfs()
{
    trie[0].fail=0;
    trie[0].fa=0;
    s=1;
    que[++e]=0;
    while(s<=e)
    {
        int st=e;
        for(int i=s;i<=st;i++)
        {

            const int &x=i,&dat=trie[i].dat,&fa=trie[i].fa;
            s++;
            int j=trie[fa].fail;
            debug<<"j="<<j<<endl;
            while(j&&!trie[j].nxt[dat]) j=trie[j].fail;
            trie[x].fail=j?0:trie[j].nxt[dat];
            for(int i=0;i<=1;i++) if(trie[x].nxt[i]) que[++e]=trie[x].nxt[i];
            //for(int i=0;i<=1;i++) if(!trie[x].dat[i]) trie[x].dat[i]=trie[x].fail;
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",in);
        build(in,0,0,strlen(in));
    }
    bfs();
    for(int i=0;i<=cnt;i++)
    {
        debug<<"i="<<i<<endl;
        debug<<trie[i].dat<<" "<<trie[i].fail<<endl;
        debug<<trie[i].nxt[0]<<"    "<<trie[i].nxt[1]<<endl;
    }
    return 0;
}

