#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e6+1e2;

char in[maxn];
int n,ans,mod;
int mxs[maxn],mis[maxn];

struct SubArray {
    int dat[2][2][3][3];
    int& operator () (int i,int ch,int mx,int mi) {
        return dat[i&1][ch][mx][mi+2];
    }
    inline void reset(int x) {
        memset(dat[x&1],0,sizeof(dat[1]));
    }
}f;

inline void adde(int& dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void dp() {
    int pmx = 0 , pmi = 0; adde(ans,1);
    for(int i=1;i<=n;i++) { // diffs at bit i .
        if( in[i] == 'L' ) pmx = max( pmx - 1 , 0 ) , pmi = pmi - 1;
        if( in[i] == 'P' ) pmx = pmx + 1 , pmi = min( pmi + 1 , 0 );
        mxs[i] = pmx , mis[i] = pmi;
    }
    f(1,0,0,-1) = f(1,1,1,0) = 1;
    for(int i=1;i<=n;i++) {
        f.reset(i+1);
        for(int ch=0;ch<2;ch++) for(int mx=0;mx<=2;mx++) for(int mi=-2;mi<=0;mi++) if( f(i,ch,mx,mi) ) {
            if( mi - 1 >= -2 ) adde(f(i+1,0,max(mx-1,0),mi-1),f(i,ch,mx,mi));
            if( mx + 1 <= 2 ) adde(f(i+1,1,mx+1,min(mi+1,0)),f(i,ch,mx,mi));
        }
        if( in[n-i+1] == 'P' ) {
            const int ned = i , pmx = mxs[n-i] , pmi = mis[n-i];
            for(int mx=0;mx<=2;mx++) for(int mi=-2;mi<=0;mi++) if( mx + pmx <= 2 && mi + pmi >= -2 ) adde(ans,f(ned,0,mx,mi));
        }
    }
}
inline void getans() {
}

int main() {
    scanf("%d%d%s",&n,&mod,in+1) , dp() , getans() , printf("%d\n",ans);
    return 0;
}

