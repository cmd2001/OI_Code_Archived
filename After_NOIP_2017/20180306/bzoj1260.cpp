#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=55;

char in[maxn];
int f[maxn][maxn];

inline int dp(int l,int r) {
    if( f[l][r] ) return f[l][r];
    #define ret f[l][r]
    ret = r - l + 1;
    if( l == r ) return ret = 1;
    if( in[l] == in[r] ) ret = std::min( dp(l,r-1) , dp(l+1,r) );
    if( in[r-1] == in[r] ) ret = std::min( ret , dp(l,r-1) );
    if( in[l] == in[l+1] ) ret = std::min( ret , dp(l+1,r) );
    for(int i=l;i<r;i++) ret = std::min( ret , dp(l,i) + dp(i+1,r) );
    return ret;
}

int main() {
    static int li;
    scanf("%s",in+1) , li = strlen(in+1);
    printf("%d\n",dp(1,li));
    return 0;
}
