#include<iostream>
#include<cstdio>
#include<cstring>
#define debug cout
using namespace std;
const int maxn=10000*50+100;
struct node
{
    int nxt[27],dat,fail;
    bool end;
    int num;
}trie[maxn];
int cnt,t,n;
bool ans[maxn];
int que[maxn],s,e;
void build(char *s,int pos,int at,int len)
{
    if(at==len) {trie[pos].end=1;trie[pos].num++;return;}
    else
    {
        if(trie[pos].nxt[s[at]-'a']) build(s,trie[pos].nxt[s[at]-'a'],at+1,len);
        else
        {
            trie[pos].nxt[s[at]-'a']=++cnt;
            trie[cnt].dat=s[at]-'a';
            build(s,cnt,at+1,len);
        }
    }
}
void buildfail()
{
    s++;
    for(int i=0;i<26;i++) if(trie[0].nxt[i]){que[++e]=trie[0].nxt[i];trie[que[e]].fail=0;}
    //debug<<"e="<<e<<endl;
    for(int i=s;i<=e;i++) trie[que[i]].fail=0;//deletable
    while(s<=e)
    {
        //debug<<"s="<<s<<"e="<<e<<endl;
        const int &now=que[s++];
        for(int i=0;i<26;i++)
        {
            //debug<<"i="<<i<<endl;
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
        //debug<<"at=="<<at;
        ans[pos]=1;
        pos=trie[pos].nxt[a[at++]-'a'];
        //debug<<"pos=="<<pos<<endl;
    }
    ans[pos]=1;
    //debug<<"at=="<<at<<"pos=="<<pos<<endl;
}
int ret=0;
void calc()
{
    for(int i=e;i>0;i--)
    {
        //debug<<"i="<<i<<endl;
        if(ans[que[i]])
        {
            //debug<<"num="<<trie[que[i]].num<<endl;
            //debug<<ans[que[i]]<<endl;
            if(trie[que[i]].end) {ret+=ans[que[i]]*trie[que[i]].num;/*debug<<"ret="<<ret<<endl;*/}
            if(trie[que[i]].fail) ans[trie[que[i]].fail]++;
            //else ++ret;
        }
    }
}
char in[1000010];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(ans,0,sizeof(ans));
        memset(que,0,sizeof(que));
        memset(trie,0,sizeof(trie));
        s=e=cnt=0;
        ret=0;
        while(n--)
        {
            scanf("%s",in);
            build(in,0,0,strlen(in));
        }
        buildfail();
        scanf("%s",in);
        find(in);
        //debug<<"e="<<e<<endl;
        calc();
        //for(int i=0;i<=cnt;i++)
        //{
            //debug<<"i="<<i<<endl;
            //debug<<(char)(trie[i].dat+'a')<<endl;
            //debug<<trie[i].fail<<endl;
        //}
        printf("%d\n",ret);
    }
    return 0;
}

