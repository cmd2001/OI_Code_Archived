#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cctype>
#include<cstdlib>
using namespace std;
const int inf=0x3f3f3f3f;

set<int> ss;
long long int ans;
int n;

int main()
{
    scanf("%d",&n);
    
    ss.insert(inf);
    ss.insert(-inf);
    
    for(int i=1,xx;i<=n;i++)
    {
        scanf("%d",&xx);
        if( i == 1 )
        {
            ans += xx;
            ss.insert(xx);
        }
        else if( ss.find(xx) != ss.end() )
            continue;
        else
        {
            ss.insert(xx);
            set<int>::iterator it = ss.find(xx);
            set<int>::iterator prv = it , nxt = it;
            --prv , ++nxt;
            ans += min( abs( xx - *prv ) , abs( xx - *nxt ) );
        }
    }
    printf("%lld\n",ans);
    
    return 0;
}