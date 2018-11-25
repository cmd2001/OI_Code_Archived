#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
using namespace std;
const int maxn=8e5+1e2;

int in[maxn],sa[maxn],rnk[maxn],n,la,lb;

namespace SA {
    int tp[maxn],tex[maxn],m;
    
    inline void Resort() {
        memset(tex,0,sizeof(int)*(m+1));
        for(int i=1;i<=n;i++) ++tex[rnk[tp[i]]];
        for(int i=1;i<=m;i++) tex[i] += tex[i-1];
        for(int i=n;i;i--) sa[tex[rnk[tp[i]]]--] = tp[i];
    }
    inline bool cmp(int* sou,int a,int b,int len) {
        return sou[a] == sou[b] && sou[a+len] == sou[b+len];
    }
    inline void build(int stm) {
        m = stm;
        for(int i=1;i<=n;i++) rnk[i] = in[i] , tp[i] = i;
        Resort();
        for(int w=1,p=1;p<n;w<<=1,m=p) {
            p = 0;
            for(int i=n-w+1;i<=n;i++) tp[++p] = i;
            for(int i=1;i<=n;i++) if( sa[i] > w ) tp[++p] = sa[i] - w;
            Resort() , swap(rnk,tp) , rnk[sa[1]] = p = 1;
            for(int i=2;i<=n;i++)
                rnk[sa[i]] = cmp(tp,sa[i],sa[i-1],w) ? p : ++p;
        }
    }
}

inline char nextchar() {
    const int bs = 1 << 22;
    static char buf[bs],*st=buf+bs,*ed=buf+bs;
    if( st == ed ) ed = buf + fread(st=buf,1,bs,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    la = getint();
    for(int i=1;i<=la;i++) in[++n] = getint();
    in[++n] = 1e4 + 1;
    lb = getint();
    for(int i=1;i<=lb;i++) in[++n] = getint();
    in[++n] = 1e4 + 1;
    SA::build(1e4+1);
    int pl = 1 , pr = la + 2;
    while( pl <= la && pr < n ) {
        if( rnk[pl] < rnk[pr] ) printf("%d ",in[pl++]);
        else printf("%d ",in[pr++]);
    }
    while( pl <= la ) printf("%d ",in[pl++]);
    while( pr < n ) printf("%d ",in[pr++]);
    return 0;
}
