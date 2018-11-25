#include<cstdio>
using namespace std;
int n,m,tot;
int root[600001],ch[600001*25][2];
int b[600001],sum[600001*25];
struct TRIE
{
    void insert(int pre,int & now,int d,int w)
    {
        if(!now) now=++tot;
        sum[now]=sum[pre]+1;
        if(d<0) return;
        int p=1&(w>>d);
        ch[now][p^1]=ch[pre][p^1];
        insert(ch[pre][p],ch[now][p],d-1,w);
    }
    int query(int l,int r,int d,int w)
    {
        if(d<0) return 0;
        int p=1&(w>>d);
        if(sum[ch[r][p^1]]-sum[ch[l][p^1]]) return (1<<d)+query(ch[l][p^1],ch[r][p^1],d-1,w);
        else return query(ch[l][p],ch[r][p],d-1,w);
    }
}Trie;
int main()
{
    scanf("%d%d",&n,&m); 
    int x,K=25;  n++;
    Trie.insert(root[0],root[1],K,0);
    for(int i=2;i<=n;i++)
    {    
          scanf("%d",&x);
        b[i]=b[i-1]^x;
        Trie.insert(root[i-1],root[i],K,b[i]); 
    }
    char c[3]; int l,r; 
    while(m--)
    {
        scanf("%s",c);
        if(c[0]=='A') 
        {
            scanf("%d",&x); n++;
            b[n]=b[n-1]^x;
            Trie.insert(root[n-1],root[n],K,b[n]);
        }
        else
        {
            scanf("%d%d%d",&l,&r,&x);
            x^=b[n];
            printf("%d\n",Trie.query(root[l-1],root[r],K,x));
        }
    }
}