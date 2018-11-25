#include<cstdio>
#include<cstring>
const int maxn=5e3+1e2,maxl=1e3+1e2;

double f[2][maxn];
char otp[maxl];

inline double max(const double &a,const double &b) {
    return a < b ? b : a;
}

int main() {
    int n,m,len,cur;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        cur ^= 1 , f[cur][0] = i;
        for(int j=1;j<=m;j++)
            f[cur][j] = max( ( f[cur][j-1] - 1 ) * j / ( i + j ) + ( f[cur^1][j] + 1 ) * i / ( i + j ) , 0 );
    }
    sprintf(otp,"%0.7lf",f[cur][m]) , len = strlen(otp);
    otp[len-1] = 0;
    puts(otp);
    return 0;
}
