#include<queue>  
#include<stdio.h>  
#include<string.h>  
#include<algorithm>  
#define N 260000  
#define S 26  
using namespace std;  
char str[N];  
int f[N];  
namespace SAM  
{  
    int son[N<<1][S],len[N<<1],pre[N<<1];  
    int in[N<<1],right[N<<1];  
    int tot,last;  
    queue<int>q;  
    int newnode()  
    {  
        tot++;  
        memset(son[tot],0,sizeof(int)*S);  
        pre[tot]=len[tot]=0;  
        return tot;  
    }  
    void init()  
    {  
        tot=0;  
        last=newnode();  
    }  
    void Insert(int x)  
    {  
        int p,np=newnode();  
        right[np]=1;  
        len[np]=len[last]+1;  
        for(p=last;p&&!son[p][x];p=pre[p])  
            son[p][x]=np;  
        if(!p)  
            pre[np]=1;  
        else  
        {  
            int q=son[p][x];  
            if(len[q]==len[p]+1)  
                pre[np]=q;  
            else  
            {  
                int nq=newnode();  
                pre[nq]=pre[q];  
                len[nq]=len[p]+1;  
                memcpy(son[nq],son[q],sizeof(int)*S);  
                pre[np]=pre[q]=nq;  
                for(;son[p][x]==q;p=pre[p])  
                    son[p][x]=nq;  
            }  
        }  
        last=np;  
    }  
    void Build()  
    {  
        int x,i;  
        for(i=1;i<=tot;i++)  
        {  
            in[pre[i]]++;  
        }  
        for(i=1;i<=tot;i++)  
        {  
            if(!in[i])  
                q.push(i);  
        }  
        while(!q.empty())  
        {  
            x=q.front(),q.pop();  
            in[pre[x]]--;  
            right[pre[x]]+=right[x];  
            if(!in[pre[x]])  
                q.push(pre[x]);  
        }  
    }  
    void calc(int n)  
    {  
        for(int i=1;i<=tot;i++)  
            f[len[i]]=max(f[len[i]],right[i]);  
        for(int i=n-1;i>=1;i--)  
            f[i]=max(f[i],f[i+1]);  
    }  
}  
int main()  
{  
    freopen("dat.txt","r",stdin);
    freopen("std.txt","w",stdout);
    int n,m,i,j,k;  
    scanf("%s",str+1);  
    n=strlen(str+1);  
    SAM::init();  
    for(i=1;i<=n;i++)  
    {  
        SAM::Insert(str[i]-'a');  
    }  
    SAM::Build();  
    SAM::calc(n);  
    for(i=1;i<=n;i++)  
    {  
        printf("%d\n",f[i]);  
    }  
    return 0;  
}  