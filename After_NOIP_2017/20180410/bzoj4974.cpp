#include<cstdio>
const int maxn=1e5+1e2;

int in[maxn],vis[maxn],n;
char ans[maxn];

inline int findbit(int x) {
    for(int i=0;i<26;i++) if( ! ( x & ( 1 << i ) ) ) return i;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , in[i] = i - in[i] + 1;
    for(int i=1;i<=n;i++) {
        if( in[i] != 1 ) ans[i] = ans[in[i]-1];
        else ans[i] = findbit(vis[i]);
        vis[i+1] = vis[in[i]] | ( 1 << ans[in[i]] );
    }
    for(int i=1;i<=n;i++) putchar('a'+ans[i]);
    putchar('\n');
    return 0;
}

