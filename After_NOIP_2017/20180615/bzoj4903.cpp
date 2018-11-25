#include<cstdio>
const int maxn=262145;
const int mod=1e9+7;

int f[maxn];

inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

int main() {
    static int n,x,ans,t;
    scanf("%d",&n);
    while(n--) {
        scanf("%d",&x) , adde(ans,t=f[x]) , adde(t,1);
        for(int ss=(x-1)&x;ss;ss=(ss-1)&x) adde(f[ss],t);
    }
    printf("%d\n",ans);
    return 0;
}