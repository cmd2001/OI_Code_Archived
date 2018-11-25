#include<cstdio>
const int maxn=1<<22;

int s[maxn],f[maxn];
int n,m,full,ans;

inline int max(int a,int b) {
    return a > b ? a : b;
}
int main() {
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&s[1<<i]);
    scanf("%d",&m);
    for(int i=0;i<m;i++) scanf("%d",&s[1<<(i+n)]) , s[1<<(i+n)] = - s[1<<(i+n)];
    full = ( 1 << ( n + m ) ) - 1;
    for(int i=1;i<=full;i++) {
        s[i] = s[ i - ( i & -i ) ] + s[ ( i & -i ) ];
        for(int j=0;j<n+m;j++)
            if( i & ( 1 << j ) ) f[i] = max( f[i] , f[i^(1<<j)] );
        f[i] += !s[i];
    }
    ans = n + m - 2 * f[full];
    printf("%d\n",ans);
    return 0;
}
