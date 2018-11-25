#include<cstdio>
#include<algorithm>

int dat[12],n;
inline int calc() {
    static int d[2][12];
    int cur = 0;
    for(int i=1;i<=n;i++) d[cur][i] = dat[i];
    for(int T=n-1;T;T--) {
        cur ^= 1;
        for(int i=1;i<=T;i++)
            d[cur][i] = d[cur^1][i] + d[cur^1][i+1];
    }
    return d[cur][1];
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) dat[i] = i;
    do {
        if( calc() == m ) {
            for(int i=1;i<=n;i++)
                printf("%d%c",dat[i],i!=n?' ':'\n');
            return 0;
        }
    }while( std::next_permutation(dat+1,dat+1+n) );
    return 0;
}
