#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=1e6+1e2;

struct BinaryIndexTree {
    int dat[maxn],len;
    #define lowbit(x) (x&-x)
    inline void update(int pos) {
        while( pos <= len ) ++dat[pos] , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos ) ret += dat[pos] , pos -= lowbit(pos);
        return ret;
    }
    inline void resize(int ss) {
        len = ss;
    }
}bit;
char a[maxn],b[maxn];
int s[maxn],pos[maxn<<1],nxt[maxn<<1],pir[maxn],n;

inline void addnode(int st,int id) {
    static int cnt = 0;
    pos[++cnt] = id , nxt[cnt] = s[st] , s[st] = cnt;
}
inline int getnode(int id) {
    if( !s[id] ) return -1;
    int ret = pos[s[id]];
    s[id] = nxt[s[id]];
    return ret;
}

int main() {
    scanf("%d",&n);
    scanf("%s%s",a+1,b+1);
    for(int i=1;i<=n;i++)
        addnode(a[i],i);
    for(int i=n;i;i--) {
        pir[i] = getnode(b[i]);
        if( !~pir[i] ) return puts("-1"),0;
    }
    lli ans = 0;
    bit.resize(n);
    for(int i=1;i<=n;i++)
        bit.update(pir[i]) , ans += i - bit.query(pir[i]);
    printf("%lld\n",ans);
    return 0;
}
