#include<cstdio>
using namespace std;
int n,cnt,at[20];
bool used[20];
bool judge(int x,int y)
{
    for(int i=1;i<x;i++)
    {
        if((at[i]+i==x+y)||(i-at[i]==x-y)) return 0;
    }
    return 1;
}
void dfs(int x)
{
    if(x>n) {++cnt;return;}
    for(int i=1;i<=n;i++)
    {
        if((!used[i])&&judge(x,i))
        {
            used[i]=1;
            at[x]=i;
            dfs(x+1);
            used[i]=0;
            at[x]=0;
        }
    }
}
int main()
{
    scanf("%d",&n);
    dfs(1);
    printf("%d\n",cnt);
    return 0;
}

