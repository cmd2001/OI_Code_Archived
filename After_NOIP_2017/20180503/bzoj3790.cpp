#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=1e5+1e2;

char in[maxn],s[maxn];
int pir[maxn],f[maxn],n;

inline void manacher() {
    int li = 0 , pos = 0 , mxr = -1;
    s[li++] = '#';
    for(int i=1;i<=n;i++) s[li++] = in[i] , s[li++] = '#';
    pir[0] = 1;
    for(int i=0;i<li;i++) {
        if( i <= mxr ) pir[i] = std::min( mxr - i , pir[pos*2-i] );
        while( i - pir[i] >= 0 && s[i-pir[i]] == s[i+pir[i]] ) ++pir[i];
        if( i + pir[i] > mxr ) mxr = i + pir[i] , pos = i;
        f[i-pir[i]+1] = i + pir[i] - 1;
    }
    //for(int i=0;i<li;i++) printf("%d ",f[i]); puts("");
}

int main() {
    while( scanf("%s",in+1) == 1 ) {
        memset(s,0,sizeof(s)) , memset(pir,0,sizeof(pir)) , memset(f,0,sizeof(f)) , n = strlen(in+1);
        manacher();
        int ans = 0 , last = f[0] + 2 , mxr = f[0] + 2;
        for(int i=0;i<=n<<1;i+=2) {
            if( i == last ) ++ans , last = mxr;
            mxr = std::max( mxr , f[i] + 2 );
        }
        printf("%d\n",ans);
    }
    return 0;
}
