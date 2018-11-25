#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=4e3+1e2;

char dis[110];
int cnt,d;
struct node //space first!
{
    char dat;
    node *nxt[30];
    node *num_nxt[15];
    node *spa,*lft;
    char tmp[110];
    int at;
    bool dire,isend;
}books[maxn];

inline node* getnode()
{
    static int cnt=0;
    return &books[++cnt];
}
inline void book_insert(char *c,node *pos)
{
    int l=strlen(c),lst,sec;
    for(int i=l-2;i;i--)
    {
        if(c[i]=='/')
        {
            lst=i;
            break;
        }
    }
    for(int i=lst-1;i;i--)
    {
    	if(c[i]=='/')
    	{
    		sec=i;
    		break;
    	}
    }
    for(int i=0;i<l;i++)
    {
        if(c[i]==' ')
        {
            if(!pos->spa) pos->spa=getnode();
            pos=pos->spa;
            pos->dat=c[i];
            if(i<=lst) pos->dire=1;
        }
        else if(c[i]=='/')
        {
            if(!pos->lft) pos->lft=getnode();
            pos=pos->lft;
            pos->dat=c[i];
            if(i<=lst) pos->dire=1;
        }
        else if(c[i]>='A'&&c[i]<='Z')
        {
            if(!pos->nxt[c[i]-'A']) pos->nxt[c[i]-'A']=getnode();
            pos=pos->nxt[c[i]-'A'];
            pos->dat=c[i];
            if(i<=lst) pos->dire=1;

        }
        else
        {
            if(!pos->num_nxt[c[i]-'0']) pos->num_nxt[c[i]-'0']=getnode();
            pos=pos->num_nxt[c[i]-'0'];
            pos->dat=c[i];
            if(i<=lst) pos->dire=1;
        }
        if(i>lst) pos->isend=1;
    }
}
inline bool judge(node *pos)
{
	bool ret=!pos->spa;
	for(int i=0;i<10;i++) ret&=(!pos->num_nxt[i]);
	for(int i=0;i<26;i++) ret&=(!pos->nxt[i]);
	return ret;
}
inline void display(node *pos,int num)
{
	dis[++cnt]=pos->dat;
    if(pos->spa&&pos->spa->isend&&pos->spa->dire) display(pos->spa,num);
    for(int i=0;i<10;i++) if(pos->num_nxt[i]&&pos->num_nxt[i]->isend&&pos->num_nxt[i]->dire) display(pos->num_nxt[i],num);
    for(int i=0;i<26;i++) if(pos->nxt[i]&&pos->nxt[i]->isend&&pos->nxt[i]->dire) display(pos->nxt[i],num);
    if(judge(pos))
	{
		for(int i=1;i<=num;i++) putchar(' ');
		puts(dis+1);
	}
    dis[cnt--]=0;
}
inline void dfs(node *pos,int num)
{
    if(!pos) return;
    if(pos->dat=='/')
    {
        memcpy(pos->tmp,dis,sizeof(dis));
        pos->at=cnt;
        for(int i=1;i<=num;i++) putchar(' ');
        puts(dis+1);
        memset(dis,0,sizeof(dis));
        cnt=0;
        if(pos->lft&&pos->lft->dire) dfs(pos->lft,num+4);
        if(pos->spa&&pos->spa->dire )dfs(pos->spa,num+4);
        for(int i=0;i<10;i++) if(pos->num_nxt[i]&&pos->num_nxt[i]->dire) dfs(pos->num_nxt[i],num+4);
        for(int i=0;i<26;i++) if(pos->nxt[i]&&pos->nxt[i]->dire) dfs(pos->nxt[i],num+4);
        if(pos->lft&&!pos->lft->dire) dfs(pos->lft,num+4);
        if(pos->spa&&!pos->spa->dire)dfs(pos->spa,num+4);
        for(int i=0;i<10;i++) if(pos->num_nxt[i]&&!pos->num_nxt[i]->dire) dfs(pos->num_nxt[i],num+4);
        for(int i=0;i<26;i++) if(pos->nxt[i]&&!pos->nxt[i]->dire) dfs(pos->nxt[i],num+4);
        {
    		if(pos->spa&&pos->spa->isend&&pos->spa->dire) display(pos->spa,num+4);
    		for(int i=0;i<10;i++) if(pos->num_nxt[i]&&pos->num_nxt[i]->isend&&pos->num_nxt[i]->dire) display(pos->num_nxt[i],num+4);
    		for(int i=0;i<26;i++) if(pos->nxt[i]&&pos->nxt[i]->isend&&pos->nxt[i]->dire) display(pos->nxt[i],num+4);
    	}
    	
        memcpy(dis,pos->tmp,sizeof(dis));
        cnt=pos->at;
    }
    else
    {
        if(pos->dat) dis[++cnt]=pos->dat;
        if(pos->lft&&pos->lft->dire) dfs(pos->lft,num);
        if(pos->spa&&pos->spa->dire )dfs(pos->spa,num);
        for(int i=0;i<10;i++) if(pos->num_nxt[i]&&pos->num_nxt[i]->dire) dfs(pos->num_nxt[i],num);
        for(int i=0;i<26;i++) if(pos->nxt[i]&&pos->nxt[i]->dire) dfs(pos->nxt[i],num);
        if(pos->lft&&!pos->lft->dire) dfs(pos->lft,num);
        if(pos->spa&&!pos->spa->dire )dfs(pos->spa,num);
        for(int i=0;i<10;i++) if(pos->num_nxt[i]&&!pos->num_nxt[i]->dire) dfs(pos->num_nxt[i],num);
        for(int i=0;i<26;i++) if(pos->nxt[i]&&!pos->nxt[i]->dire) dfs(pos->nxt[i],num);
        dis[cnt--]=0;
    }
}

int main()
{
    static char in[110];
    static node *st=getnode();
    while(gets(in))
    {
    	if(*in=='0'&&strlen(in)==1) break;
        in[strlen(in)]='/';
        book_insert(in,st);
        memset(in,0,sizeof(in));
    }
    dfs(st,0);
    return 0;
}
