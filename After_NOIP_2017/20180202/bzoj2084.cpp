#include<cstdio>
#include<algorithm>
const int maxn=5e5+1e2;

char in[maxn];
char s[maxn<<1],p[maxn<<1];
int f[maxn<<1],mx,id,n;
long long ans;

inline void covstr(char* dst,char* sou) {
    *dst = '$' , dst[1] = '#';
    for(int i=1;i<=n;i++)
        dst[i<<1] = sou[i] , dst[i<<1|1] = '#';
}
inline void revstr(char* dst) {
    for(int i=1;i<=n;i++)
        dst[i] = '1' - ( dst[i] - '0' );
}
inline void manacher() {
    int len = n << 1 | 1;
    for(int i=1;i<=len;i++) {
        if( i <= mx ) f[i] = std::min( mx - i , f[id*2-i] );
        while( s[i-f[i]] == p[i+f[i]] ) ++f[i];
        if( i + f[i] > mx ) mx = f[i] + i , id = i;
        ans += f[i] >> 1;
    }
}

int main() {
    scanf("%d%s",&n,in+1);
    covstr(s,in) , revstr(in) , covstr(p,in);
    manacher();
    printf("%lld\n",ans);
    return 0;
}
