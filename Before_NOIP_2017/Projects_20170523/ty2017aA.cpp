#include<bits/stdc++.h>
#define debug cout
using namespace std;
char word[150][150];
bool vis[150],bd[150],nsp[150];
int cnt;
inline bool getline()
{
    memset(word,0,sizeof(word));
    memset(vis,0,sizeof(vis));
    memset(bd,0,sizeof(bd));
    memset(nsp,0,sizeof(nsp));
    int at=0;
    cnt=1;
    char c=getchar(),nxtch=0,from=0;
    while(c!='\n')
    {
        if(c==EOF) return 0;
        if(c==' ')
        {
            cnt++,at=0;
        }
        else if(c=='.'||c==',')
        {
            cnt++,at=0;
            word[cnt][++at]=c;
            bd[cnt]=1;
            nxtch=getchar();
            if(nxtch!=' ') cnt++,at=0;
        }
        else word[cnt][++at]=c;
        from=c;
        if(at==0&&from!=' ') bd[cnt]=1;
        if(nxtch) c=nxtch,nxtch=0;
        else c=getchar();
    }
    return 1;
}
inline void getvis()
{
    for(int i=1;i<=cnt;i++)
    {
        if('A'<=word[i][1]&&word[i][1]<='Z'&&'a'<=word[i][2]&&word[i][2]<='z')
        {
            vis[i]=1;
            for(int k=2;word[i][k]!='\0';k++)
                if(!('a'<=word[i][k]&&word[i][k]<='z'))
                    vis[i]=0;
        }
    }
}
inline void getoutput()
{
    for(int i=1;i<=cnt;i++)
    {
        if(vis[i])
        {
            int k;
            for(k=i;k<=cnt;k++) if(!vis[k+1]) break;
            if(k==i)
            {
                printf("%s",word[i]+1);
                if(i!=cnt&&!bd[i+1]) putchar(' ');
                continue;
            }
            for(int p=i;p<=k;p++) putchar(word[p][1]);
            putchar(' ');
            putchar('(');
            for(int p=i;p<=k;p++)
            {
                printf("%s",word[p]+1);
                if(p!=k) putchar(' ');
            }
            putchar(')');
            if(!bd[k+1]&&k!=cnt) putchar(' ');
            i=k;
        }
        else
        {
            printf("%s",word[i]+1);
            if(i!=cnt&&(!bd[i+1])) putchar(' ');
        }
    }
    putchar('\n');
}
int main()
{
    while(getline())
    {
        getvis();
        getoutput();
    }
    return 0;

}



