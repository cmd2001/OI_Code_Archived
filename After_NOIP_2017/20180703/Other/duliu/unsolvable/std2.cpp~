#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
typedef long long int lli;
using namespace std;
const int maxn=1e3+1e2,maxl=3,maxt=33,maxs=941;
const int mod=1e9+9;

int n,m;

struct ACautomatic {
    int ch[maxt][26],fail[maxt],isend[maxt],dat[maxn],fa[maxn],root,cnt;
    ACautomatic() { root = ++cnt; }
    inline void insert(int &pos,int cur,const char* s,const int &len) {
        if( !pos ) pos = ++cnt , dat[pos] = s[cur-1];
        if( cur > len ) return isend[pos] = 1 , pos;
        return fa[insert(ch[pos][(int)s[cur]-'a'],cur+1,s,len)] = pos;
    }
    inline void getfail() {
        queue<int> q;
        for(int i=0;i<26;i++) ch[root][i] ? q.push(ch[root][i]) , fail[ch[root][i]] = root : ch[root][i] = root;
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int i=0;i<26;i++) ch[pos][i] ? q.push(ch[pos][i]) , fail[ch[pos][i]] = ch[fail[pos]][i] : ch[pos][i] = ch[fail[pos]][i];
        }
        for(int i=1;i<=cnt;i++) if( isend[i] ) for(int j=0;j<26;j++) ch[i][j] = ch[root][j];
    }
    inline void getpath(int pos,char* s,int &li) {
        for(;pos!=root;pos=fa[pos]) s[++li] = dat[pos];
    }
    inline int step(int pos,char * s,int li) {
        int ret = 0;
        for(int i=1;i<=li;i++) {
            pos = ch[pos][(int)s[i]-'a'];
            if( isend[pos] ) ++ret;
        }
        return ret;
    }
}str,rev;

inline int add(const int &x,.const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

struct Node {
    int ways,sum;
    friend Node operator + (const Node &x,const Node &y) {
        return (Node){a.ways+b.ways,a.sum+b.sum};
    }
    friend Node operator += (Node &x,const Node &y) {
        return x = x + y;
    }
}f[maxn][maxl][maxs],g[maxn][maxl][maxs]; // f[i][j][statement]  , g[i][j][statement] .

int sta[3],su,fs,ini; // sumlen , fullsize .

inline void zip() {
    int ret = 0;
    for(int i=1;i<=m;i++) ret *= sumlen + 1 , ret += sta[i];
    return ret;
}
inline void unzip(int* sta,int ss) {
    for(int i=m;i;i--) sta[i] = ss % ( sumlen + 1 ) , ss /= sumlen + 1;
}

inline void trans_f() {
    for(int i=1;i<=m;i++) sta[i] = 1;
    f[0][0][zip()] = (Node){1,0};
    if( m == 1 ) {
        for(int i=0;i<n;i++) for(int ss=ini;ss<=fs;ss++) 
    } else {
    }
}

inline int merge(const Node &up,const Node &down,const int &us,const int &ds,char* deal) {
    static char ss[maxt];
    static int su[3],sd[3];
    int ret = add(up.sum,down.sum) , li;
    unzip(su,us) , unzip(sd,ds);
    for(int i=1;i<=m;i++) {
        li = 0 , rev.getpath(sd[i],ss,li);
        if( str.step(su[i],ss,li) ) adde(ret,mul(up.way,down.way));
    }
    if( m == 2 ) {
        li = 0; for(int i=1;i<=m;i++) ss[++li] = deal[i];
        rev.getpath(li,sd[m]) , adde(ret,mul(str.step(su[1],ss,li),mul(up.way,down.way)));
    }
    return ret;
}
inline int query(int line) {
    int ret = 0;
    for(int i=ini;i<=fs;i++) for(int j=ini;j<=fs;j++) adde(ret,merge(f[line-1][m][i],g[line+1][1][j],i,j));
    return ret;
}


