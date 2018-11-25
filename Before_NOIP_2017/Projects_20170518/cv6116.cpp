//Codevs_6116_By_Cmd2001
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e8;
bitset<maxn> vis;
int tab[maxn],cnt,l,r,ans;
inline void getprime()
{
    for(int i=2,j;i<=r;i++)
    {
        if(!vis[i]) tab[++cnt]=i;
        for(j=1;j<=cnt&&i*tab[j]<=r&&i%tab[j];j++) vis[i*tab[j]]=1;
        vis[i*tab[j]]=1;
    }
}
int main()
{
    scanf("%d%d",&l,&r);
    getprime();
    for(int i=l;i<=r;i++) if(!vis[i]) ++ans;
    printf("%d\n",ans);
    return 0;
}
