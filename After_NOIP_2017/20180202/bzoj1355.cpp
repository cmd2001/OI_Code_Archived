#include<cstdio>
const int maxn=1e6+1e2;

char in[maxn];
int fail[maxn],n;

inline void getfail() {
    for(int i=2,j=0;i<=n;i++) {
        while( j && in[j+1] != in[i] ) j = fail[j];
        fail[i] = ( in[j+1] == in[i] ? ++j : j );
    }
}

int main() {
    scanf("%d%s",&n,in+1);
    getfail();
    printf("%d\n",n-fail[n]);
    return 0;
}
