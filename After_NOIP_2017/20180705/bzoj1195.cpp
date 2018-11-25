#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<utility>
#define debug cout
using namespace std;
const int maxn=6e2+1e1,maxs=(1<<12)+5;

int root,fs;

struct ACautomatic {
    int ch[maxn][26],fail[maxn],isend[maxn],cnt;
    int vis[maxn][maxs],fa[maxn*maxs],way[maxn*maxs],siz;
    inline void insert(int &pos,int cur,char* s,const int &li,const int &id) {
        if( !pos ) pos = ++cnt;
        if( cur > li ) return void( isend[pos] |= 1 << ( id - 1 ) );
        insert(ch[pos][(int)s[cur]-'A'],cur+1,s,li,id);
    }
    inline void getfail() {
        queue<int> q;
        for(int i=0;i<26;i++) ( ch[root][i] ? q.push(ch[root][i]) , fail[ch[root][i]] : ch[root][i] ) = root;
        while( q.size() ) {
            const int pos = q.front(); q.pop() , isend[pos] |= isend[fail[pos]];
            for(int i=0;i<26;i++) ( ch[pos][i] ? q.push(ch[pos][i]) , fail[ch[pos][i]]  : ch[pos][i] ) = ch[fail[pos]][i];
        }
    }
    inline void print(int pos) {
        if( pos == 1 ) return;
        print(fa[pos]) , putchar('A'+way[pos]);
    }
    inline void bfs() {
        queue<pair<int,int> > q; q.push(make_pair(root,0)) , vis[root][0] = ++siz;
        while( q.size() ) {
            const int pos = q.front().first , sta = q.front().second; q.pop();
            for(int i=0;i<26;i++) {
                const int tarp = ch[pos][i] , tars = sta | isend[tarp];
                if( !vis[tarp][tars] ) {
                    fa[vis[tarp][tars]=++siz] = vis[pos][sta] , way[siz] = i;
                    if( tars == fs ) return print(siz);
                    q.push(make_pair(tarp,tars));
                }
            }
        }
    }
}acm;

int main() {
    static char o[maxn];
    static int n,li;
    scanf("%d",&n) , fs = ( 1 << n ) - 1;
    for(int i=1;i<=n;i++) scanf("%s",o+1) , acm.insert(root,1,o,li=strlen(o+1),i);
    acm.getfail() , acm.bfs() , putchar('\n');
    return 0;
}
