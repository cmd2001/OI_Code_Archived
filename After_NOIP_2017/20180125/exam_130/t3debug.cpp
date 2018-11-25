#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ulli unsigned long long int
#define debug cerr
using namespace std;
const int maxn=1e6+1e2; // maxn doubled
const int mod = 2013265921;

char in[maxn>>1];
int ch[maxn][26],fa[maxn],deg[maxn];
ulli len[maxn],sizr[maxn],sizra[maxn],dp[maxn],dpa[maxn],ans;
int root,last,cnt,li;

inline int NewNode(int ll) {
    len[++cnt] = ll;
    return cnt;
}
inline void extend(int x,int ra) {
    int p = last;
    int np = NewNode(len[p]+1);
    sizr[np] = 1 , sizra[np] = ra;
    while( p && !ch[p][x] )
        ch[p][x] = np , p = fa[p];
    if( !p ) fa[np] = root;
    else {
        int q = ch[p][x];
        if( len[q] == len[p] + 1 ) fa[np] = q;
        else {
            int nq = NewNode(len[p]+1);
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            fa[nq] = fa[q];
            fa[q] = fa[np] = nq;
            while( p && ch[p][x] == q )
                ch[p][x] = nq , p = fa[p];
        }
    }
    last = np;
}

inline void pretopo() {
    for(int i=1;i<=cnt;i++)
        if( fa[i] )
            ++deg[fa[i]];
    queue<int> q;
    for(int i=1;i<=cnt;i++)
        if( !deg[i] )
            q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        if( pos == root ) break;
        sizr[fa[pos]] += sizr[pos] , sizra[fa[pos]] += sizra[pos];
        if( !--deg[fa[pos]] )
            q.push(fa[pos]);
    }
}

inline ulli linesum(ulli x) {
    return x * ( x + 1 ) >> 1;
}
inline ulli linesum(ulli st,ulli ed) {
    return ( linesum(ed) - linesum(st) + mod ) % mod;
}

inline void pir(char* s,int li) {
    int now = root;
    ulli le = 0;
    for(int i=1;i<=li;i++) {
        const int t = s[i] - 'a';
        debug<<"i = "<<i<<"t = "<<t<<endl;
        if( ch[now][t] ) {
            now = ch[now][t] ,
            ++le;
        } else {
            while( now && !ch[now][t] )
                now = fa[now];
            if( !now ) {
                now = root , le = 0;
            } else {
                le = len[now] + 1 ,
                now = ch[now][t];
            }
        }
        if( now != root ) {
            ulli deltal = linesum( len[fa[now]] , le ) * 2 % mod;
            ulli deltall = ( deltal + le - len[fa[now]] ) % mod;
            if( le > len[now] || deltal < 0 ) debug<<"Length Error"<<endl;
            debug<<"i = "<<i<<"le = "<<le<<"half deltalen = "<<le - len[fa[now]]<<endl;
            debug<<"sizr = "<<sizr[now]<<endl;
            debug<<"now = "<<now<<endl;
            debug<<"fa = "<<fa[now]<<endl;
            ++dp[fa[now]];
            if( i != li ) ++dpa[fa[now]];
            ans += sizr[now] * deltal % mod , ans %= mod;
            ans += sizra[now] * deltall % mod , ans %= mod;
            if( i != li ) ans += sizr[now] * deltall % mod , ans %= mod;
            debug<<"inital add = "<<sizr[now] * deltal<<endl;
        }
    }
}
inline void topo() {
    memset(deg,0,sizeof(deg));
    for(int i=1;i<=cnt;i++)
        if( fa[i] )
            ++deg[fa[i]];
    queue<int> q;
    for(int i=1;i<=cnt;i++)
        if( !deg[i] )
            q.push(i);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        if( pos == root ) return;
        ulli deltal = linesum( len[fa[pos]] , len[pos] ) * 2 % mod;
        ulli deltall = ( deltal + len[pos] - len[fa[pos]] ) % mod;
        ans += sizr[pos] * dp[pos] % mod * deltal % mod , ans %= mod ,
        ans += sizra[pos] * dp[pos] % mod * deltall % mod , ans %= mod ,
        ans += sizr[pos] * dpa[pos] % mod * deltall % mod , ans %= mod ,
        dp[fa[pos]] += dp[pos] , dpa[fa[pos]] += dpa[pos];
        if( !--deg[fa[pos]] )
            q.push(fa[pos]);
    }
}

int main() {
    scanf("%s",in+1);
    li = strlen(in+1);
    
    last = root = NewNode(0);
    for(int i=1;i<=li;i++)
        extend(in[i]-'a',(i!=li));
    pretopo();
    reverse(in+1,in+1+li);
    pir(in,li);
    debug<<"inital ans = "<<ans<<endl;
    topo();
    
    printf("%lld\n",ans);
    return 0;
}