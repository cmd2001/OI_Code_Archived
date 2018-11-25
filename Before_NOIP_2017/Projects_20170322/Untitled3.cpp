#include<bits/stdc++.h>
using namespace std;
int m,n,x;
set<int> s;
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&x);
        s.insert(x);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        if(s.find(x)==s.end()) printf("0 ");
        else printf("1 ");
    }
    return 0;
}
