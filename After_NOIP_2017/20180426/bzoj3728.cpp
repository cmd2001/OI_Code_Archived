#include<cstdio>
#include<algorithm>
#include<cctype>
#include<queue>
#include<set>
typedef long long int lli;
const int maxn=5e5+1e2;

int p[maxn];
std::multiset<int> ms;
std::priority_queue<int> pq;

__inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    static int n,k;
    static lli ans;
    n = getint() , k = getint();
    for(int i=1;i<=n;i++) p[i] = getint();
    for(int i=1;i<=n;i++) ms.insert(getint());
    std::sort(p+1,p+1+n);
    for(int i=1;i<=n;i++) {
        std::multiset<int>::iterator it = ms.upper_bound(p[i]);
        if( it != ms.begin() ) pq.push(p[i]-*--it) , ms.erase(it) , ans += p[i];
    }
    if( k < (signed) ms.size() ) return puts("NIE"),0;
    for(std::multiset<int>::iterator it=ms.begin();it!=ms.end();it++) ans += *it , --k;
    while(k--) ans -= pq.top() , pq.pop();
    printf("%lld\n",ans);
    return 0;
}