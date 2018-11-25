#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=1e5+1e2;

int cmp;
struct Node {
    int d,a,id;
    friend bool operator < (const Node &a,const Node &b) {
        return cmp ? a.d < b.d : a.a > b.a;
    }
}na[maxn],nb[maxn];

int n,cna,cnb;
lli h;

int main() {
    scanf("%d%lld",&n,&h);
    for(int i=1,d,a;i<=n;i++) scanf("%d%d",&d,&a) ,  d <= a ? na[++cna] = (Node){d,a,i} : nb[++cnb] = (Node){d,a,i} ;
    cmp = 1 , std::sort(na+1,na+1+cna) , cmp = 0  , std::sort(nb+1,nb+1+cnb);
    for(int i=1;i<=cna;i++)
        if( h <= na[i].d ) return puts("NIE"),0;
        else h += na[i].a - na[i].d;
    for(int i=1;i<=cnb;i++)
        if( h <= nb[i].d ) return puts("NIE"),0;
        else h += nb[i].a - nb[i].d;
    puts("TAK");
    for(int i=1;i<=cna;i++) printf("%d%c",na[i].id,cnb||i!=cna?' ':'\n');
    for(int i=1;i<=cnb;i++) printf("%d%c",nb[i].id,i!=cnb?' ':'\n');
    return 0;
}
