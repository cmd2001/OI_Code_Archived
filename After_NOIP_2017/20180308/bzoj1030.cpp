#include<cstdio>
#include<cstring>
#include<queue>
const int maxn=1e4+1e2,maxl=1e2+1e1;
const int mod=10007;

char in[maxl];
int ch[maxn][26],fail[maxn],isend[maxn],f[maxn][maxl],root,cnt;
int n,m;

inline void insert(char* s,int li) {
    int now = root;
    for(int i=1;i<=li;i++) {
        const int t = s[i] - 'A';
        if( !ch[now][t] ) ch[now][t] = ++cnt;
        now = ch[now][t];
    }
    isend[now] = 1;
}
inline void buildfail() {
    std::queue<int> q;
    for(int i=0;i<26;i++)
        if( ch[root][i] ) fail[ch[root][i]] = root , q.push(ch[root][i]);
        else ch[root][i] = root;
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        for(int i=0;i<26;i++)
            if( ch[pos][i] ) fail[ch[pos][i]] = ch[fail[pos]][i] , q.push(ch[pos][i]);
            else ch[pos][i] = ch[fail[pos]][i];
    }
}
inline void dp() {
    f[root][0] = 1;
    for(int i=0;i<=m;i++) for(int j=1;j<=cnt;j++) if( f[j][i] ) {
        for(int k=0;k<26;k++) {
            int can = 1;
            for(int p=j;p;p=fail[p]) if( isend[ch[p][k]] ) can = 0;
            if( can ) ( f[ch[j][k]][i+1] += f[j][i] ) %= mod;
        }
    }
}
inline int count() {
    int ret = 0;
    for(int i=1;i<=cnt;i++)
        ret += f[i][m] , ret %= mod;
    return ret;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}

int main() {
    static int li,ans;
    scanf("%d%d",&n,&m) , root = cnt = 1;
    for(int i=1;i<=n;i++) {
        scanf("%s",in+1) , li = strlen(in+1);
        insert(in,li);
    }
    buildfail() , dp();
    ans = ( fastpow(26,m) - count() + mod ) % mod;
    printf("%d\n",ans);
    return 0;
}
