#include<cstdio>
#include<cstring>
#define ulli unsigned long long
using namespace std;
const int maxn=1e3+1e2;
const ulli base = 233;
const ulli mod = 2013265921;

char s[maxn];
ulli in[maxn],hsh1[maxn],hsh2[maxn],pows[maxn],ans;
int n;

inline void inithsh() {
    for(int i=1;i<=n;i++)
        in[i] = s[i] - 'a' + 1;
    for(int i=1;i<=n;i++)
        hsh1[i] = hsh1[i-1] * base + in[i];
    for(int i=n;i;i--)
        hsh2[i] = hsh2[i+1] * base + in[i];
    *pows = 1;
    for(int i=1;i<=n;i++)
        pows[i] = pows[i-1] * base;
}
inline ulli segment1(int st,int ed) {
    --st;
    return hsh1[ed] - hsh1[st] * pows[ed-st];
}
inline ulli segment2(int st,int ed) {
    ++ed;
    return hsh2[st] - hsh2[ed] * pows[ed-st];
}
inline ulli merge1(int sx,int tx,int sy,int ty) {
    return segment1(sx,tx) * pows[ty-sy+1] + segment1(sy,ty);
}
inline ulli merge2(int sx,int tx,int sy,int ty) {
    return segment2(sy,ty) * pows[tx-sx+1] + segment2(sx,tx);
}
inline bool judge(int sx,int tx,int sy,int ty) {
    return merge1(sx,tx,sy,ty) == merge2(sx,tx,sy,ty);
}

int main() {
    scanf("%s",s+1);
    n = strlen(s+1);
    inithsh();
    for(int sx=1;sx<=n;++sx) {
        for(int tx=sx;tx<=n;++tx)
            for(int sy=1;sy<=n;++sy)
                for(int ty=sy;ty<=n;++ty)
                    if( judge(sx,tx,sy,ty) )
                        ans += tx - sx + ty - sy + 2;
        ans %= mod;
    }
    
    printf("%llu\n",ans);
    
    return 0;
}
