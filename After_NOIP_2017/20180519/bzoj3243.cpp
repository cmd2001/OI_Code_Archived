#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
const int maxn=1e5+1e2,maxd=1e2+1e1;

int in[maxn][maxd],sum[maxd][maxd],rin[maxd][maxn],ran[maxn],mul1[maxd],mul2[maxn];
int n,d,k;


inline void solve2() {
    for(int T=5,su,pa,pb;T;T--) {
        su = 0 , memset(mul1+1,0,d<<2) , memset(mul2+1,0,n<<2) , pa = pb = -1;
        for(int i=1;i<=n;i++) ( su += ( ran[i] = rand() ) % k ) %= k;
        for(int i=1;i<=n;i++) for(int j=1;j<=d;j++) ( mul1[j] += ran[i] * rin[j][i] ) %= k;
        for(int i=1;i<=n;i++) for(int j=1;j<=d;j++) ( mul2[i] += mul1[j] * in[i][j] ) %= k;
        for(int i=1;i<=n&&!~pa;i++) if( mul2[i] != su ) pa = i;
        if( !~pa ) continue;
        for(int i=1;i<=n&&!~pb;i++) if( i != pa ) {
            int ss = 0;
            for(int j=1;j<=d;j++) ( ss += rin[j][pa] * in[i][j] ) %= k;
            if( !ss ) pb = i;
        }
        if( ~pb ) return void( printf("%d %d\n",std::min(pa,pb),std::max(pa,pb)) );
    }
    puts("-1 -1");
}
inline void solve3() {
    static int pmu[maxn];
    for(int i=1;i<=n;i++) pmu[i] = i;
    std::random_shuffle(pmu+1,pmu+1+n);
    for(int i=1;i<=n;i++) {
        int ss = 0;
        for(int j=1;j<=d;j++) for(int p=1;p<=d;p++) ( ss += sum[j][p] * in[pmu[i]][j] * in[pmu[i]][p] ) %= k , ( sum[j][p] += in[pmu[i]][j] * in[pmu[i]][p] ) %= k;
        if( ss != ( i - 1 ) % k ) {
            int pa = pmu[i] , pb = -1;
            for(int j=1;j<i&&!~pb;j++) {
                int sss = 0;
                for(int k=1;k<=d;k++) ( sss += rin[k][pmu[i]] * in[pmu[j]][k] ) %= 3;
                if( !sss ) pb = pmu[j];
            }
            return void( printf("%d %d\n",std::min(pa,pb),std::max(pa,pb)) );
        }
    }
    puts("-1 -1");
}

inline int getint() { // you will get dangerous_system_call when using fread on uoj .
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , d = getint() , k = getint();
    for(int i=1;i<=n;i++) for(int j=1;j<=d;j++) in[i][j] = rin[j][i] = getint() % k;
    k == 2 ? solve2() : solve3();
    return 0;
}
