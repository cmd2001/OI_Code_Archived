#include<cstdio>
#include<algorithm>
const int maxn=2e4+1e2,maxl=1e5+1e2;

int in[maxl],at[maxn][6],f[maxl],n,len,ans;
struct BinaryIndexTree {
    int dat[maxl];
    #define lowbit(x) (x&-x)
    inline void update(int pos,int x) {
        while( pos <= len ) dat[pos] = std::max(dat[pos],x) , pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos ) ret = std::max(ret,dat[pos]) , pos -= lowbit(pos);
        return ret;
    }
}bit;

int main() {
    scanf("%d",&n) , len = n * 5;
    for(int i=1,t;i<=len;i++) scanf("%d",&t) , at[t][++*at[t]] = i;
    for(int i=1,t;i<=len;i++) {
        scanf("%d",&t);
        for(int j=5;j;j--) ans = std::max(ans,f[at[t][j]]=std::max(f[at[t][j]],bit.query(at[t][j]-1)+1)) , bit.update(at[t][j],f[at[t][j]]);
    }
    printf("%d\n",ans);
    return 0;
}

