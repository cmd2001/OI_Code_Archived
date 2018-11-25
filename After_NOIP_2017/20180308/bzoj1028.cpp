#include<cstdio>
#include<cstring>
const int maxn=4e2+1e1;

int in[maxn],t[maxn],ans[maxn],cnt;
int n;

inline bool judge() {
    for(int i=1;i<=n;i++)
        if( t[i] ) {
            t[i] %= 3;
            if( ( t[i+1] -= t[i] ) < 0 )return 0;
            if( ( t[i+2] -= t[i] ) < 0 ) return 0;
        }
    return 1;
}
inline bool force() {
    for(int i=1;i<=n;i++)
        if( in[i] >= 2 ) {
            memcpy(t,in,sizeof(in)) , t[i] -= 2;
            if( judge() ) return 1;
        }
    return 0;
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=m*3+1;i++) scanf("%d",&x) , ++in[x];
    for(int i=1;i<=n;i++) {
        ++in[i];
        if( force() ) ans[++cnt] = i;
        --in[i];
    }
    if( !cnt ) puts("NO");
    else for(int i=1;i<=cnt;i++) printf("%d%c",ans[i],i!=cnt?' ':'\n');
    return 0;
}
