#include<cstdio>
#include<cstring>
#include<vector>
#define bool unsigned char
const int maxn=1e2+1e1,maxl=1.5e2+1e1;

char in[maxl],tar[maxn][maxl];
int val[maxn],sum[maxl],lt[maxn],g[maxl]; 
bool* f[maxl][maxl][maxn];
bool dp[maxl][maxl];
int n,li;

inline void getans() {
    for(int len=1;len<=li;len++)
        for(int st=1;st+len-1<=li;st++) {
            const int ed = st + len - 1;
            for(int p=1;p<=n;p++) { // p is the pairing string .
                for(int k=1;k<=lt[p]&&k<=len;k++) {
                    if( in[ed] != tar[p][k] ) continue;
                    if( k == 1 ) {
                        if( st == ed ) f[st][ed][p][k] = 1;
                        else f[st][ed][p][k] = dp[st][ed-1];
                        continue;
                    }
                    for(int l=st;l<ed;l++) {
                        if( l == ed - 1 ) f[st][ed][p][k] |= f[st][l][p][k-1];
                        else f[st][ed][p][k] |= f[st][l][p][k-1] && dp[l+1][ed-1];
                    }
                }
            }
            for(int mid=st;mid<ed;mid++)
                dp[st][ed] |= ( dp[st][mid] && dp[mid+1][ed] );
            for(int p=1;p<=n;p++)
                dp[st][ed] |= f[st][ed][p][lt[p]];
        }
    for(int i=0;i<=li;i++) { // g[i] is proccessed
        if( i ) g[i] = std::max( g[i] , g[i-1] );
        for(int ed=i+1;ed<=li;ed++)
            if( dp[i+1][ed] ) g[ed] = std::max( g[ed] , g[i] + sum[ed] - sum[i] );
    }
}
inline void readin() {
    static int k,p;
    static char s[maxl];
    scanf("%d",&k);
    while( k-- ) {
        scanf("%s%d",s,&p);
        val[(int)*s-'a'] = p;
    }
    scanf("%s",in+1) , li = strlen(in+1);
    for(int i=1;i<=li;i++) sum[i] = sum[i-1] + val[(int)in[i]-'a'];
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%s",tar[i]+1);
        lt[i] = strlen(tar[i]+1);
        for(int j=1;j<=li;j++)
            for(int k=1;k<=li;k++) {
                f[j][k][i] = new bool [lt[i]+1];
                for(int p=0;p<=lt[i];p++)
                    f[j][k][i][p] = 0;
            }
    }
}

int main() {
    readin();
    getans();
    printf("%d\n",g[li]);
    return 0;
}
