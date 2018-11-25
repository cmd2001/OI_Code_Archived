#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
const int maxn=1e3+1e1,maxe=5e3+1e2;
const int mod=1e9+7;

char s[maxe];
int app[maxe],n,m,q;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

struct Node {
    char dat[maxn];
    int val,id;
    char& operator [] (const int &x) { return dat[x]; }
    const char& operator [] (const int &x) const { return dat[x]; }
    friend bool operator < (const Node &a,const Node &b) {
        for(int i=1;i<=n;i++) if( a[i] != b[i] ) return a[i] < b[i];
        return 0;
    }
    inline void getval() {
        for(int i=1;i<=n;i++) adde(val,val) , adde(val,dat[i]);
    }
}in[maxe];

inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline void getstr(char* s) {
    char ch;
    while( !isdigit(ch=nextchar()) );
    do *s++ = ch; while( isdigit(ch=nextchar()) );
}

int main() {
    n = getint() , m = getint() , q = getint();
    for(int i=1;i<=n;i++) {
        getstr(s+1);
        for(int j=1;j<=m;j++) in[j][n-i+1] = s[j] - '0';
    }
    for(int j=1;j<=m;j++) in[j].id = j , in[j].getval();
    std::sort(in+1,in+1+m);
    for(int j=1;j<=m;j++) app[in[j].id] = j;
    in[m+1].val = 1; for(int i=1;i<=n;i++) adde(in[m+1].val,in[m+1].val);
    for(int i=1;i<=q;i++) {
        getstr(s+1);
        int l = 0 , r = m + 1;
        for(int i=1;i<=m;i++) ( s[i] - '0' ) ?  r = std::min( r , app[i] ) : l = std::max( l , app[i] );
        if( l >= r ) puts("0");
        else printf("%d\n",sub(in[r].val,in[l].val));
    }
    return 0;
}
