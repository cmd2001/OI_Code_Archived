#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define debug cout
typedef unsigned long long int ulli;
using namespace std;
const int maxn=2e5+1e2,maxs=1e7+1e2,maxe=2e7+1e2,lim=50;
const ulli base = 7,hash_mod=23333333;
const int mod=998244353;

struct Hash_Map {
    int st[hash_mod],nxt[maxe],val[maxe],cnt;
    ulli dat[maxe];
    inline void insert(const ulli &x,const int &delta) {
        int bel = x % hash_mod , i , lst;
        for(lst=0,i=st[bel];i&&dat[i]!=x;i=nxt[i],lst=i) ;
        if( !i ) {
            if(lst) nxt[lst] = ++cnt , dat[cnt] = x , val[cnt] = delta;
            else st[bel] = ++cnt , dat[cnt] = x , val[cnt] = delta;
        } else val[i] += delta;
    }
    inline int query(const ulli &x) {
        int bel = x % hash_mod , i;
        for(i=st[bel];i&&dat[i]!=x;i=nxt[i]) ;
        if( !i ) return 0;
        return val[i];
    }
}hmp;

int in[maxn],nxt[maxn],prv[maxn];
ulli pows[maxs];

inline void merge(int i,int j) {
    nxt[i] = j , prv[j] = i;
}
inline void split(int i,int j) {
    nxt[i] = prv[j] = 0;
}
inline int get_nxt_len(int t) {
    int ret = 0;
    while( t && ret < lim ) ++ret , t = nxt[t];
    return ret;
}
inline int get_prv_len(int t) {
    int ret = 0;
    while( t && ret < lim ) ++ ret , t = prv[t];
    return ret;
}
inline void get_nxt_in(int t,int len,int* dst) {
    while(len) *dst++ = in[t] , t = nxt[t] , --len;
}
inline void get_prv_in(int t,int len,int* dst) {
    while(len) *dst-- = in[t] , t = prv[t] , --len;
}
inline ulli segment(ulli* h,int l,int r) {
    return h[r] - h[l-1] * pows[r-l+1];
}
inline void solve(int i,int j,const int &delta) {
    static int tpin[maxn];
    static ulli tph[maxn];
    int plen = get_prv_len(i) , nlen = get_nxt_len(j) , su = plen + nlen;
    //debug<<"plen = "<<plen<<"nlen = "<<nlen<<endl;
    get_prv_in(i,plen,tpin+plen) , get_nxt_in(j,nlen,tpin+plen+1);
    //debug<<"prv and nxt got"<<endl;
    for(int i=1;i<=su;i++) tph[i] = tph[i-1] * base + tpin[i];
    for(int tot=2;tot<=lim&&tot<=su;tot++) {
        for(int st=std::max(1,plen-tot+2);st<=plen&&st+tot-1<=su;st++) {
            const ulli seg = segment(tph,st,st+tot-1);
            //debug<<"seg = "<<seg<<endl;
            hmp.insert(seg,delta);
        }
    }
}
inline int query(char* in,int li,int seg) {
    static ulli h[maxs];
    for(int i=1;i<=li;i++) h[i] = h[i-1] * base + in[i] - '0';
    ulli ret = 1;
    for(int st=1;st+seg-1<=li;st++) {
        ulli hsh = segment(h,st,st+seg-1);
        ret = ret * hmp.query(hsh) % mod;
    }
    return (int) ret;
}

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
inline void getstr(char* dst,int &len) {
    char ch; len = 0;
    while( !isdigit(ch=nextchar()) );
    do dst[++len] = ch; while( isdigit(ch=nextchar()) );
}

int main() {
    static int n,m;
    static char qin[maxs];
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint() , hmp.insert(in[i],1);
    *pows = 1; for(int i=1;i<maxs;i++) pows[i] = pows[i-1] * base;
    for(int i=1,o,x,y,li,k;i<=m;i++) {
        o = getint();
        if( o == 1 ) x = getint() , y = getint() , solve(x,y,1) , merge(x,y);
        else if( o == 2 ) y = nxt[x=getint()] , solve(x,y,-1) , split(x,y);
        else if( o == 3 ) getstr(qin,li) , k = getint() , printf("%d\n",query(qin,li,k));
    }
    return 0;
}
