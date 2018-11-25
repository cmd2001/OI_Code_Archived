#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long double ldb;
using namespace std;
const int maxn=1e4+1e2;
const ldb eps = 1e-8;

struct Line {
    int k,b,id;
    friend bool operator < (const Line &a,const Line &b) {
        return a.k != b.k ? a.k < b.k : a.b < b.b;
    }
    friend ldb inter(const Line &a,const Line &b) {
        return ((ldb)a.b-b.b) / ((ldb)b.k-a.k);
    }
    friend bool calc(const Line &a,const Line &b,const Line &t) {
        return inter(a,b) > inter(b,t);
    }
}ps[maxn],stk[maxn];

int ans[maxn],n,top;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&ps[i].b) , ps[i].id = i;
    for(int i=1;i<=n;i++) scanf("%d",&ps[i].k);
    sort(ps+1,ps+1+n) , top = 1;
    for(int i=2;i<=n;i++) top += ps[i].k != ps[i-1].k || ps[i].b == ps[i-1].b , ps[top] = ps[i];
    n = top , top = 0;
    for(int i=1;i<=n;i++) {
        while( top && inter(stk[top],ps[i]) < -eps ) --top;
        while( top > 1 && calc(stk[top-1],stk[top],ps[i]) ) --top;
        stk[++top] = ps[i];
    }
    for(int i=1;i<=top;i++) ans[i] = stk[i].id;
    printf("%d\n",top);
    sort(ans+1,ans+1+top);
    for(int i=1;i<=top;i++) printf("%d%c",ans[i],i!=top?' ':'\n');
    return 0;
}

