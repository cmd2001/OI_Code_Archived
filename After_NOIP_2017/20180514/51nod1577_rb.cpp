#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=5e5+1e2,maxl=31;
int in[maxn];
bool vis[maxn];

struct LinearBase {
    int dat[maxl],bel[maxl];
    inline void insert(int id,int val) {
        for(int i=30;~i;i--) if( val & ( 1 << i ) ) {
            if( !dat[i] ) {
                dat[i] = val , bel[i] = id;
                return;
            } else {
                if( bel[i] < id ) std::swap(bel[i],id) , std::swap(val,dat[i]);
                val ^= dat[i];
            }
        }
    }
    inline bool query(int val,int lim) {
        for(int i=30;~i;i--) if( val & ( 1 << i ) ) {
            if( !dat[i] || bel[i] < lim ) return 1;
            val ^= dat[i];
        }
        return 0;
    }
}lb[maxn],tp;

inline char nextchar() {
    static const int BS = 1 << 20;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? 0 : *st++;
}
inline int getint() {
    int ret = 0;
    char ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    static int n,q,l,r,w;
    n = getint();
    for(int i=1;i<=n;i++) lb[i] = lb[i-1] , lb[i].insert(i,in[i]=getint());
    q = getint();
    while(q--) {
        l = getint() , r = getint() , w = getint(), puts(lb[r].query(w,l)?"NO":"YES");
    }
    return 0;
}
