#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=31000;
struct node
{
    int nxt[3],fail,dat;
    bool end,danger;
}trie[maxn];
int cnt,n;
int que[maxn],s,e;
char in[maxn];
int vis[maxn],dis[maxn];
void build(char *s,int pos,int at,int len)
{
    if(at==len) {trie[pos].end=1;trie[pos].danger=1;return;}
    else
    {
        if(trie[pos].nxt[s[at]-48]) build(s,trie[pos].nxt[s[at]-48],at+1,len);
        else
        {
            trie[pos].nxt[s[at]-48]=++cnt;
            trie[cnt].dat=s[at]-48;
            build(s,cnt,at+1,len);
        }
    }
}
void buildfail()
{
    s++;
    if(trie[0].nxt[0]) que[++e]=trie[0].nxt[0];
    if(trie[0].nxt[1]) que[++e]=trie[0].nxt[1];
    for(int i=s;i<=e;i++) trie[que[i]].fail=0;
    while(s<=e)
    {
        const int &now=que[s++];
        for(int i=0;i<2;i++)
        {
            const int x=trie[now].nxt[i];
            const int dat=trie[trie[now].nxt[i]].dat;
            if(!x) {trie[now].nxt[i]=trie[trie[now].fail].nxt[i];continue;}
            int at=trie[now].fail;
            while(!trie[at].nxt[dat]) at=trie[at].fail;
            trie[x].fail=trie[at].nxt[dat];
            trie[x].danger|=trie[trie[x].fail].danger;
            que[++e]=x;
        }
    }
}
bool dfs(int pos)
{
    dis[pos]=1;
    for(int i=0;i<2;i++)
    {
        const int &v=trie[pos].nxt[i];
        //if(dis[v]) {debug<<"pos="<<pos<<endl;debug<<"i="<<i<<endl;debug<<"v="<<v<<endl;return 1;}
        if(dis[v]) return 1;
        if(vis[v]||trie[v].danger) continue;
        vis[v]=1;
        if(dfs(v)) return 1;
    }
    dis[pos]=0;
    return 0;
}
int main()
{
    scanf("%d",&n);
    cnt=0;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",in);
        build(in,0,0,strlen(in));
    }
    buildfail();
    //debug<<trie[2].nxt[0]<<endl;
    //debug<<"dfsans=="<<endl;
    //debug<<dfs(0)<<endl;
    if(dfs(0)) printf("TAK\n");
    else printf("NIE\n");
    /*for(int i=0;i<=cnt;i++)
    {
        debug<<"i="<<i<<endl;
        //debug<<"fail="<<trie[i].fail<<endl;
        //debug<<trie[i].dat<<" "<<trie[i].fail<<endl;
        debug<<trie[i].nxt[0]<<"    "<<trie[i].nxt[1]<<endl;
        //debug<<"danger"<<trie[i].danger<<endl;
    }*/
    return 0;
}

