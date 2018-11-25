#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2,maxb=1e6+1e2,maxq=1e2+1e1;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxn<<1],nxt[maxn<<1];
lli l[maxn<<1],tar[maxq];
int ans[maxq],cal[maxn],siz[maxn],ban[maxn],bel[maxn],cnt;
lli dep[maxn],dis[maxn];
set<lli> st;
int q;

inline void addedge(int from,int to,lli len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}

inline void getrt(int pos,int fa,const int &fs,int &rt) {
    siz[pos] = 1 , cal[pos] = 0;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) {
        getrt(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] ,
        cal[pos] = max( cal[pos] , siz[t[at]] );
    }
    cal[pos] = max( cal[pos] , fs - siz[pos] );
    if( cal[pos] <= cal[rt] ) rt = pos;
}
inline void getsubt(int pos,int fa,const int &bl) {
    dis[++cnt] = dep[pos] , bel[cnt] = bl;
    for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) {
        dep[t[at]] = dep[pos] + l[at] ,
        getsubt(t[at],pos,bl);
    }
}
inline void calc(int pos,int fs) {
    if( fs == 1 ) return;
    int rt = 0; cal[0] = inf;
    getrt(pos,-1,fs,rt);
    ban[rt] = 1 , cnt = 0 , st.clear();
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
        dep[t[at]] = l[at];
        getsubt(t[at],-1,t[at]);
    }
    st.insert(0);
    for(int l=1,r;l<=cnt;l=r+1) {
        for(r=l;r<cnt&&bel[r+1]==bel[l];r++) ;
        for(int k=l;k<=r;k++)
            for(int j=1;j<=q;j++) {
                if( st.find(tar[j]-dis[k]) != st.end() ) ans[j] = 1;
            }
        for(int k=l;k<=r;k++) st.insert(dis[k]);
    }
    for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) {
        calc(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt]);
    }
}

int main() {
    static int n;
    scanf("%d%d",&n,&q);
    for(int i=1,a,b,l;i<n;i++) scanf("%d%d%d",&a,&b,&l) , addedge(a,b,l) , addedge(b,a,l);
    for(int i=1;i<=q;i++) {
        scanf("%lld",tar+i);
        if( !tar[i] ) ans[i] = 1;
    }
    calc(1,n);
    for(int i=1;i<=q;i++) puts(ans[i]?"Yes":"No");
    return 0;
}
