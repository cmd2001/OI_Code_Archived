#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e2+1e1,maxe=1e2+1e1,maxt=1e2+1e1;
const int mod=1e9+9;

struct ACautomatic {
    int ch[maxt][26],fail[maxt],fa[maxt],way[maxt],isend[maxt],root,cnt;
    ACautomatic() { root = ++cnt; }
    inline int insert(int &pos,int cur,char* s,int li) {
        if( !pos ) pos = ++cnt , way[pos] = s[cur-1];
        if( cur > li ) return isend[pos] = 1 , pos;
        return fa[insert(ch[pos][(int)s[cur]-'a'],cur+1,s,li)] = pos;
    }
    inline void getfail() {
        queue<int> q;
        for(int i=0;i<26;i++) ( ch[root][i] ? q.push(ch[root][i]) , fail[ch[root][i]] : ch[root][i] ) = root;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , isend[pos] |= isend[fail[pos]];
            for(int i=0;i<26;i++) ( ch[pos][i] ? q.push(ch[pos][i]) , fail[ch[pos][i]] : ch[pos][i] ) = ch[fail[pos]][i];
        }
        for(int i=1;i<=cnt;i++) if( isend[i] ) for(int j=0;j<26;j++) ch[i][j] = ch[root][j];
    }
}str;

char dat[maxn][maxe],in[maxe];
int n,m,row,ans;

inline void dfs2(int x,int y,int sta,int val) {
    val += str.isend[str.ch[sta][dat[x][y]-'a']];
    if( x == n && y == m ) return void( ans += val );
    if( x != n ) dfs2(x+1,y,str.ch[sta][dat[x][y]-'a'],val);
    if( y != m ) dfs2(x,y+1,str.ch[sta][dat[x][y]-'a'],val);
}
inline void dfs1(int x,int y) {
    if( x > n ) {
        return dfs2(1,1,str.root,0);
    }
    const int tx = x + ( y == m ) , ty = y == m ? 1 : y + 1;
    if( x == row ) dat[x][y] = in[y] , dfs1(tx,ty);
    else {
        for(int i='a';i<='z';i++) dat[x][y] = i , dfs1(tx,ty);
    }
}

namespace IO {
    inline char nextchar() {
        static const int BS = 1 << 21;
        static char buf[BS],*st,*ed;
        if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
        return st == ed ? -1 : *st++;
    }
    inline int getint() {
        int ret = 0; char ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
    inline void getstr(char* s) {
        char ch;
        while( !isalpha(ch=nextchar()) );
        do *s++ = ch; while( isalpha(ch=nextchar()) );
        *s++ = '\0';
    }
}
using IO::getint;
using IO::getstr;


int k;
inline void input() {
    static string in[maxt];
    static bool marked[maxt];
    static char s[maxt];
    static int li;
    for(int i=1;i<=k;i++) getstr(s) , in[i] = s;
    for(int i=1;i<=k;i++) for(int j=1;j<=k;j++) if( i != j && ~in[i].find(in[j])  ) marked[i] = 1;
    for(int i=1;i<=k;i++) if( !marked[i] ) {
        memcpy(s+1,in[i].c_str(),in[i].length()) , s[in[i].length()+1] = '\0';
        str.insert(str.root,1,s,li=strlen(s+1));
    }
}

int main() {
    static char s[maxt];
    static int li,qs;
    n = getint() , m = getint() , k = getint();
    input() , str.getfail() , qs = getint();
    while(qs--) row = getint() , getstr(in+1) , ans = 0 , dfs1(1,1) , printf("%d\n",ans);
    return 0;
}