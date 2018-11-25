#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ulli unsigned long long int
using namespace std;
const ulli base1 = 233 , base2 = 2333;
const int maxn=1e3+1e2;

char in[maxn][maxn],tar[maxn][maxn];
ulli hsh[maxn][maxn],hsht[maxn][maxn],pows[maxn];

inline void inithsh(char in[maxn][maxn],ulli hsh[maxn][maxn],int n,int m) {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            in[i][j] -= '0' - 1;
    pows[0] = 1;
    for(int j=1;j<=m;j++) pows[j] = pows[j-1] * base1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            hsh[i][j] = hsh[i][j-1] * base1 + in[i][j];
}
inline ulli segmenthsh(ulli* sou,int st,int ed) {
    --ed;
    return sou[ed] - sou[st] * sou[ed-st];
}
inline ulli squarejudge(int stx,int sty,int lx,int ly) {
    for(int i=stx;i<lx;i++) {
        if( hsht[i-stx+1][ly] != segmenthsh(hsh[i],sty,sty+ly-1) )
            return 0;
    }
    return 1;
}
inline bool getans(int n,int m,int a,int b) {
    for(int i=1;i+a-1<=n;i++)
        for(int j=1;j+b-1<=m;j++)
            if( squarejudge(i,j,a,b) )
                return 1;
    return 0;
}
int main() {
    static int n,m,a,b,q;
    scanf("%d%d%d%d",&n,&m,&a,&b);
    for(int i=1;i<=n;i++)
        scanf("%s",in[i]+1);
    inithsh(in,hsh,n,m);
    scanf("%d",&q);
    while( q-- ) {
        for(int i=1;i<=a;i++)
            scanf("%s",tar[i]+1);
        inithsh(tar,hsh,a,b);
        puts(getans(n,m,a,b)?"1":"0");
    }
    return 0;
}
