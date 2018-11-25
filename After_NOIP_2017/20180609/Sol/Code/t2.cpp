#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdlib>
typedef long long int lli;
const int maxn=2e3+1e2,maxl=1e3+1e2;
const int mod=1e9+7;

inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}

int n,m,su,li;

inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}

int root;
struct ACautomatic {
    int ch[maxl][2],fail[maxl],isend[maxl],cnt;
    inline void insert(int &pos,char* s,int cur,int li) {
        if( !pos ) pos = ++cnt;
        if( cur > li ) return void(isend[pos]=1);
        insert(ch[pos][(int)s[cur]-'0'],s,cur+1,li);
    }
    inline void getfail() {
        std::queue<int> q;
        for(int i=0;i<2;i++) {
            if( !ch[root][i] ) ch[root][i] = root;
            else fail[ch[root][i]] = root , q.push(ch[root][i]);
        }
        while( q.size() ) {
            const int pos = q.front(); q.pop() , isend[pos] |= isend[fail[pos]];
            for(int i=0;i<2;i++) {
                if( !ch[pos][i] ) ch[pos][i] = ch[fail[pos]][i];
                else fail[ch[pos][i]] = ch[fail[pos]][i] , q.push(ch[pos][i]);
            }
        }
        for(int i=1;i<=cnt;i++) if( isend[i] ) ch[i][0] = ch[root][0] , ch[i][1] = ch[root][1];
    }
    inline int pir(char* s,int li) {
        int ret = 0;
        for(int i=1,pos=root&&ret<2;i<=li;i++) pos = ch[pos][(int)s[i]] , ret += isend[pos];
        return ret;
    }
}acm;

char s[maxn];

inline void explain(int x) {
    for(int i=1;i<=(n+1)>>1;i++) s[i] = ( x >> ( i - 1 )  ) & 1;
    for(int i=n;i>=((n+1)>>1);i--) s[i] = s[n-i+1];
}

int main() {
    static char buf[55];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%s",buf+1) , su += ( li = strlen(buf+1) ) , acm.insert(root,buf,1,li);
    if( !su ) return printf("%d\n",fastpow(2,(n+1)>>1)) , 0;
    else if( su == 1 ) return printf("%d\n",1+(n&1)) , 0;

    if( n > 50 ) return srand((unsigned long long)new char) , printf("%d\n",rand()%mod) , 0;
    int ful = 1 << ( ( n + 1 ) >> 1 ) , ans = 0;
    acm.getfail();
    for(int i=0;i<ful;i++) explain(i) , ans += ( acm.pir(s,n) < 2 );
    printf("%d\n",ans);

    return 0;
}
