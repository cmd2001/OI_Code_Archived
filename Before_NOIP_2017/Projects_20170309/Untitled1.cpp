#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
struct node
{
    int nxt[27],dat,fail,ans;
    bool end;
}trie[maxn];
struct ansnode
{
    int pos[210];
    int r;
    void addedge(const int &x){pos[++r]=x;}
}aat[210];
int acnt;
int cnt,t,n;
int ans[maxn];
int ret[maxn];
int que[maxn],s,e;
void build(char *s,int pos,int at,int len,int ansat)
{
    if(at==len)
    {
        trie[pos].end=1;
        if(trie[pos].ans) aat[trie[pos].ans].addedge(ansat);
        else
        {
            trie[pos].ans=++acnt;
            aat[trie[pos].ans].addedge(ansat);
        }
        return;
    }
    else
    {
        if(trie[pos].nxt[s[at]-'a']) build(s,trie[pos].nxt[s[at]-'a'],at+1,len,ansat);
        else
        {
            trie[pos].nxt[s[at]-'a']=++cnt;
            trie[cnt].dat=s[at]-'a';
            build(s,cnt,at+1,len,ansat);
        }
    }
}
void buildfail()
{
    s++;
    for(int i=0;i<26;i++) if(trie[0].nxt[i]){que[++e]=trie[0].nxt[i];trie[que[e]].fail=0;}
    //debug<<"e="<<e<<endl;
    for(int i=s;i<=e;i++) trie[que[i]].fail=0;//deleteable
    while(s<=e)
    {
        const int &now=que[s++];
        for(int i=0;i<26;i++)
        {
            const int &x=trie[now].nxt[i];
            const int &dat=trie[trie[now].nxt[i]].dat;
            if(!x) {trie[now].nxt[i]=trie[trie[now].fail].nxt[i];continue;}
            int at=trie[now].fail;
            while(at&&!trie[at].nxt[dat]) at=trie[at].fail;
            trie[x].fail=trie[at].nxt[dat];
            que[++e]=x;
        }
    }
}
void find(const char *a)
{
    int at=0,len=strlen(a);
    int pos=0;
    while(at!=len)
    {
        ans[pos]++;
        pos=trie[pos].nxt[a[at++]-'a'];
    }
    ans[pos]++;
}
void calc()
{
    for(int i=e;i>0;i--)
    {
        if(ans[que[i]])
        {
            if(trie[que[i]].end)
            {
                const int &a=ans[que[i]];
                const int &x=trie[que[i]].ans;
                const int &r=aat[x].r;
                const int *at=aat[x].pos;
                for(int i=1;i<=r;i++) ret[at[i]]=a;
            }
            if(trie[que[i]].fail) ans[trie[que[i]].fail]+=ans[que[i]];
        }
    }
}
char in[210][maxn];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",in[i]);
        build(in[i],0,0,strlen(in[i]),i);
    }
    buildfail();
    for(int i=1;i<=n;i++) find(in[i]);
    calc();
    for(int i=1;i<=n;i++) printf("%d\n",ret[i]);
    return 0;
}

