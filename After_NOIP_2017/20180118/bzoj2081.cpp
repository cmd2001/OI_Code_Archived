#include<cstdio>
#include<set>
#define ulli unsigned long long int
#define ui unsigned int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
const ulli base=200019;

ulli in[maxn];
ulli pows[maxn],hsh1[maxn],hsh2[maxn];
ui ans,anss[maxn],anslen;
int n;
set<ulli> ss;

inline void gethsh(ulli* sou,ulli* dst,int st,int delta) {
    for(int i=st;i&&i<=n;i+=delta)
        dst[i] = dst[i-delta] * base + sou[i];
}
inline ulli segment(ui st,ui ed) {
    ulli h1 = hsh1[ed] - hsh1[st-1] * pows[ed-st+1];
    ulli h2 = hsh2[st] - hsh2[ed+1] * pows[ed-st+1];
    return h1 < h2 ? h1 : h2;
}
inline void initpow() {
    *pows = 1;
    for(int i=1;i<=n;i++)
        pows[i] = pows[i-1] * base;
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%llu",in+i);
    gethsh(in,hsh1,1,1) , gethsh(in,hsh2,n,-1) , initpow();
    for(int step=1;step<=n;step++) {
        ss.clear();
        for(int st=1,ed;st<=n;st=ed+1) {
            ed = st + step - 1;
            if( ed > n ) break;
            ss.insert(segment(st,ed));
        }
        if( ss.size() < ans ) continue;
        if( ss.size() > ans ) ans = ss.size() , anslen = 0;
        anss[++anslen] = step;
    }
    printf("%u %u\n",ans,anslen);
    for(ui i=1;i<=anslen;i++)
        printf("%u%c",anss[i],i!=anslen?' ':'\n');
    
    return 0;
}