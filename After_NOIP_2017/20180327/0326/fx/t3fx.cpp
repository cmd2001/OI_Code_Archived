#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],fa[maxn],w[maxn],sons[maxn];
int n,a,b;

inline  void coredge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int a,int b) {
    coredge(a,b) , coredge(b,a);
}
inline void update(int &mx,int &sec,const int &now) {
    if( now >= mx ) sec = mx , mx = now;
    else if( now > sec ) sec = now;
}
inline void dfs(int pos) {
    int mx = 0 , sec = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , ++sons[pos];
            dfs(t[at]) , update(mx,sec,w[t[at]]);
        }
    w[pos] = sec + sons[pos];
}
inline bool check(int lim) {
    int fs = 0 , tim = 0 , ret = 0 , now = a , last = -1;
    for(int i=a;i!=b;i=fa[i]) fs += sons[i] - ( i != a );
    while( now != b ) {
        ++tim;
        int sum = 0;
        for(int at=s[now];at;at=nxt[at])
            if( t[at] != fa[now] && t[at] != last) {
                if( w[t[at]] + ret + fs > lim ) ++sum , --tim;
                if( tim < 0 ) return 0; // No enough time .
            }
        ret += sum , fs -= sons[now] - ( now != a );
        last = now , now = fa[now];
        if( ret > lim ) return 0;
    }
    return ret <= lim;
}
inline int bin() {
    int ll = -1 , rr = n << 1 , mid;
    while( rr > ll + 1 ) {
        mid = ( ll + rr ) >> 1;
        if( check(mid) ) rr = mid;
        else ll = mid;
    }
    return rr;
}

int main() {
    scanf("%d%d%d",&n,&b,&a);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b) , doubledge(a,b);
    }
    dfs(b);
    printf("%d\n",bin());
    return 0;
}