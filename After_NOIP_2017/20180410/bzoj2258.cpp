#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned long long int ulli;
const int maxn=5e4+1e3;
const ulli base=29;

int rec[maxn],cov[maxn];
char in[maxn];
ulli h[maxn],pows[maxn];
int len;

inline void rebuild() {
    for(int i=1;i<=len;i++) h[i] = h[i-1] * base + ( in[i] - 'a' + 1 ) , cov[rec[i]] = i;
}
inline void initpows() {
    *pows = 1;
    for(int i=1;i<=len;i++) pows[i] = pows[i-1] * base , rec[i] = i;
}
inline void insert(const int &pos,const char &c) {
    for(int i=++len;i>pos;i--) in[i] = in[i-1] , rec[i] = rec[i-1];
    in[pos] = c;
    pows[len] = pows[len-1] * base , rebuild();
}
inline ulli seg(const int &l,const int &r) {
    return h[r] - h[l-1] * pows[r-l+1];
}
inline bool judge(const int &x,const int &y,const int &len) {
    return seg(x,x+len-1) == seg(y,y+len-1);
}
inline int bin(const int &x,const int &y) {
    int l = 0 , r = len - std::max( x , y ) + 1 , mid;
    if( judge(x,y,r) ) return r;
    while( r > l + 1 ) {
        mid = ( l + r ) >> 1;
        if( judge(x,y,mid) ) l = mid;
        else r = mid;
    }
    return l;
}

int main() {
    static char o[10],c[10];
    static int n;
    scanf("%s",in+1) , len = strlen(in+1) , initpows() , rebuild();
    scanf("%d",&n);
    for(int i=1,x,y,p;i<=n;i++) {
        scanf("%s",o);
        if( *o == 'Q' ) scanf("%d%d",&x,&y) , printf("%d\n",bin(cov[x],cov[y]));
        else if( *o == 'I' ) scanf("%s%d",c,&p) , insert(p,*c);
    }
    return 0;
}

