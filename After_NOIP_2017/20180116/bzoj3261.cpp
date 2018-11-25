#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=6e5+1e2;

int xorsum[maxn];
int root[maxn],cnt;
int ch[maxn*25][2],sum[maxn*25];

inline void insert(int pos,int pre,int bit,int x) {
    sum[pos] = sum[pre] + 1;
    if( bit < 0 ) return;
    int c = ( x >> bit ) & 1;
    ch[pos][c^1] = ch[pre][c^1];
    insert(ch[pos][c]=++cnt,ch[pre][c],bit-1,x);
}
inline int query(int pos,int pre,int bit,int x) {
    if( bit < 0 ) return 0;
    int c = ( ( x >> bit ) & 1 ) ^ 1;
    if( sum[ch[pos][c]] - sum[ch[pre][c]] )
        return ( 1 << bit ) + query(ch[pos][c],ch[pre][c],bit-1,x);
    else return query(ch[pos][c^1],ch[pre][c^1],bit-1,x);
}

int main() {
    static int n,m;
    static char com[10];
    
    insert(root[1]=++cnt,root[0],24,0);
    
    scanf("%d%d",&n,&m);n++;
    for(int i=2,x;i<=n;i++) {
        scanf("%d",&x);
        xorsum[i] = xorsum[i-1] ^ x;
        insert(root[i]=++cnt,root[i-1],24,xorsum[i]);
    }
    for(int i=1,l,r,x;i<=m;i++) {
        scanf("%s",com);
        if( *com == 'A' ) {
            scanf("%d",&x) , ++n;
            xorsum[n] = xorsum[n-1] ^ x;
            insert(root[n]=++cnt,root[n-1],24,xorsum[n]);
        } else {
            scanf("%d%d%d",&l,&r,&x);
            x ^= xorsum[n];
            printf("%d\n",query(root[r],root[l-1],24,x));
        }
    }
    return 0;
}
