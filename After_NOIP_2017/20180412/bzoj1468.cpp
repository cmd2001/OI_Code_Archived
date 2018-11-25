#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=4e4+1e2;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
int siz[maxn],mx[maxn],ban[maxn],dis[maxn];
int lst[maxn],nw[maxn],tp[maxn],lstlen,nwlen;
int n,lim,ans;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}

inline void getroot(int pos,int fa,const int &fs,int& rt) {
    siz[pos] = 1 , mx[pos] = 0;
    for(int at=s[pos];at;at=nxt[at])
        if( !ban[t[at]] && t[at] != fa ) {
            getroot(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] ,
            mx[pos] = max( mx[pos] , siz[t[at]] );
        }
    mx[pos] = max( mx[pos] , fs - siz[pos] );
    if( mx[pos] < mx[rt] ) rt = pos;
}
inline void getdis(int pos,int fa,int* ret,int& retlen) {
    ret[++retlen] = dis[pos];
    for(int at=s[pos];at;at=nxt[at])
        if( !ban[t[at]] && t[at] != fa ) {
            dis[t[at]] = dis[pos] + l[at] ,
            getdis(t[at],pos,ret,retlen);
        }
}
inline int calc(int* dst,int len) {
    int rit = len;
    long long ret = 0;
    for(int i=1;i<=len;i++) {
        while( rit && dst[rit] + dst[i] > lim ) --rit;
        ret += rit - ( i <= rit );
    }
    return ret >> 1;
}

inline void solve(int pos,const int &blksiz) {
    int rt = 0; *mx = inf;
    getroot(pos,-1,blksiz,rt);
    lstlen = 0 , ban[rt] = 1;
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) dis[t[at]] = l[at] , getdis(t[at],rt,lst,lstlen);
    sort(lst+1,lst+1+lstlen) , ans += calc(lst,lstlen);
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
        nwlen = 0 , dis[t[at]] = l[at];
        getdis(t[at],rt,nw,nwlen);
        sort(nw+1,nw+1+nwlen) , ans -= calc(nw,nwlen);
    }
    for(int i=1;i<=lstlen;i++) if( lst[i] <= lim ) ++ans;
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
        const int ss = siz[t[at]] < siz[rt] ? siz[t[at]] : blksiz - siz[rt];
        solve(t[at],ss);
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    scanf("%d",&lim);
    solve(1,n);
    printf("%d\n",ans);
    return 0;
}
