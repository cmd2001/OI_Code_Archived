#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
const int maxn=1e5+1e2;

struct Node
{
    int ed,val;
    friend bool operator < (const Node &a,const Node &b)
    {
        return a.ed < b.ed;
    }
}ns[maxn];
long long int ans;
int n,ss;
multiset<int> sel;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&ns[i].ed,&ns[i].val);
    
    sort(ns+1,ns+1+n);
    
    for(int i=1;i<=n;i++)
        if( ss < ns[i].ed )
        {
            sel.insert(ns[i].val);
            ++ss;
        }
        else if( ns[i].val > *sel.begin() )
        {
            sel.erase(sel.begin());
            sel.insert(ns[i].val);
        }
    while( sel.size() )
    {
        ans += *sel.begin();
        sel.erase(sel.begin());
    }
    
    printf("%lld\n",ans);
    
    return 0;
}