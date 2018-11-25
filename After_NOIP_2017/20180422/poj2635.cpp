#include<cstdio>
#include<cstring>
#define bool unsigned char
typedef long long int lli;
const int maxn=1e6+1e2,maxl=1e2+1e1,lim=1e6;

char in[maxn];
int cov[maxn],len;
int prime[maxn],cnt,li;

inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
}
inline void getcov() {
    len = ( li + 2 ) / 3;
    memset(cov+1,0,sizeof(int)*len);
    for(int i=1,id;i<=li;i++) {
        id = len - ( li - i ) / 3;
        cov[id] = cov[id] * 10 + in[i] - '0';
    }
    //for(int i=1;i<=len;i++) printf("%d ",cov[i]);
    //puts("");
}
inline bool mod(int x) {
    int ret = 0;
    for(int i=1;i<=len;i++) ret = ( ret * 1000 + cov[i] ) % x;
    //printf("x = %d , ret = %d\n",x,ret);
    return !ret;
}

int main() {
    static int k,fail;
    sieve();
    while( scanf("%s%d",in+1,&k) == 2 && ( in[1]-'0' || k ) ) {
        li = strlen(in+1) , getcov() , fail = 0;
        for(int i=1;i<=cnt&&prime[i]<k&&!fail;i++) if( mod(prime[i]) ) printf("BAD %d\n",prime[i]) , fail = 1;
        if( !fail ) puts("GOOD");
    }
    return 0;
}
