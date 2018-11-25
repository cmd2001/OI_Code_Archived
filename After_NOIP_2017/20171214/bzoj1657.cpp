#include<cstdio>
#include<algorithm>
#include<iostream>
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

int inh[maxn],inv[maxn],f[maxn];
int stk[maxn],id[maxn];
int top;
int n,ans;

inline void pop(int x)
{
   while( top && stk[top] < x )
       stk[top] = id[top] = 0,
       --top;
}

inline void push(int x,int iid)
{
   stk[++top] = x;
   id[top] = iid;
}

int main()
{
   scanf("%d",&n);
   for(int i=1;i<=n;i++)
       scanf("%d%d",inh+i,inv+i);
    
   for(int i=1;i<=n;i++)
   {
       pop(inh[i]);
       if( top )
           f[id[top]] += inv[i];
       push(inh[i],i);
   }
    
    while( top )
        stk[top] = id[top] = 0,
        top--;
    
   for(int i=n;i;i--)
   {
       pop(inh[i]);
       if( top )
           f[id[top]] += inv[i];
       push(inh[i],i);
   }
   
   ans = -0x3f3f3f3f;
   
   for(int i=1;i<=n;i++)
       ans = max( ans , f[i] );
    
   printf("%d\n",ans);
    
   return 0;
}
