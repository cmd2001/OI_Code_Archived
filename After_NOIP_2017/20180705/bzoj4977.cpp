#include<cstdio>
#include<algorithm>
#include<queue>
#include<functional>
#include<vector>
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

priority_queue<int,vector<int>,greater<int> > used,killed;
priority_queue<int,vector<int>,less<int> > rem;

struct Node {
    int a,c,t;
    friend bool operator < (const Node &a,const Node &b) {
        return a.a != b.a ? a.a < b.a : a.t < b.t;
    }
}in[maxn<<1];

int main() {
    static int n,m;
    static lli ans;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&in[i].a) , in[i].t = 1;
    for(int i=n+1;i<=n+m;i++) scanf("%d%d",&in[i].a,&in[i].c) , in[i].t = 2;
    sort(in+1,in+1+n+m) , n += m;
    for(int i=1;i<=n;i++) {
        if( in[i].t == 1 ) {
            if( rem.size() ) ans += in[i].a + rem.top() , used.push(in[i].a) , killed.push(rem.top()) , rem.pop();
            else if( used.size() ) ans += in[i].a - used.top() , used.pop() , used.push(in[i].a);
        } else rem.push(in[i].c-in[i].a);
    }
    while( used.size() && killed.size() && used.top() + killed.top() < 0 ) ans -= used.top() + killed.top() , used.pop() , killed.pop();
    printf("%lld\n",ans);
    return 0;
}
