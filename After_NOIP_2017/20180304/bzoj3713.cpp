#include<cstdio>
#define lli long long int
const int maxn=100,lim=1e9;

lli fib[maxn];
int cnt;

inline void gen() {
    fib[1] = 0 , fib[2] = 1;
    for(cnt=3;(fib[cnt]=fib[cnt-1]+fib[cnt-2])<=lim;cnt++) ;
    --cnt;
}
inline bool query(lli x) {
    for(int i=1;i<=cnt;i++)
        for(int j=i;j<=cnt;j++)
            if( x == fib[i] * fib[j] ) return 1;
    return 0;
}

int main() {
    static int T,x;
    scanf("%d",&T) , gen();
    while(T--) scanf("%d",&x) , puts(query(x)?"TAK":"NIE");
    return 0;
}
