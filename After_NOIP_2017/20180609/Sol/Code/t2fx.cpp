#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<queue>
#define debug cout
using namespace std;
const int maxn=2e3+1e2,maxl=1e3+1e2;
const int mod=1e9+7;

inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
struct ACautomatic {
    int ch[maxl][2],fail[maxl],isend[maxl],fa[maxl],root,cnt;
    inline void insert(int &pos,char* s,int cur,int li) {
        if( !pos ) pos = ++cnt;
        if( cur > li ) return void( isend[pos] = 1 );
        insert(ch[pos][(int)s[cur]-'0'],s,cur+1,li) , fa[ch[pos][(int)s[cur]-'0']] = pos;
    }
    inline void getfail() {
        queue<int> q;
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
        for(int i=1;i<=cnt;i++) if( isend[i] ) for(int j=0;j<2;j++) ch[i][j] = ch[root][j];
    }
    inline int pir(int pos,char* s,int li) {
        int ret = 0;
        for(int i=1;i<=li;i++) pos = ch[pos][(int)s[i]-'0'] , ret += isend[pos];
        return ret;
    }
    inline void getstr(int pos,char* s,int &li) {
        if( isend[pos] ) pos = root;
        for(li=0;fa[pos];pos=fa[pos]) s[++li] = '0' + ( pos == ch[fa[pos]][1] );
        reverse(s+1,s+1+li);
    }
}prf,suf;

struct Node {
    int a,b,p;
    inline int h() {
        return p * maxl * maxl + a * maxl + b;
    }
    inline void fil(int t) {
        b = t % maxl , a = ( t / maxl ) % maxl , p = t / maxl / maxl;
    }
};

unordered_map<int,int> f[2];

inline void trans(unordered_map<int,int> &dst,const unordered_map<int,int> &sou) {
    Node cur; dst.clear();
    for(unordered_map<int,int>::const_iterator it=sou.begin();it!=sou.end();it++) {
        cur.fil(it->first);
        for(int i=0;i<2;i++) {
            const int ta = prf.ch[cur.a][i] , tb = suf.ch[cur.b][i] , tp = cur.p + prf.isend[ta] + suf.isend[tb];
            if( tp < 2 ) adde(dst[((Node){ta,tb,tp}).h()],it->second);
        }
    }
}

inline void trans_sig(unordered_map<int,int> &dst,const unordered_map<int,int> &sou) {
    Node cur; dst.clear();
    for(unordered_map<int,int>::const_iterator it=sou.begin();it!=sou.end();it++) {
        cur.fil(it->first);
        for(int i=0;i<2;i++) {
            const int ta = prf.ch[cur.a][i] , tb = cur.b , tp = cur.p + prf.isend[ta];
            if( tp < 2 ) adde(dst[((Node){ta,tb,tp}).h()],it->second);
        }
    }
}

inline int judge(int a,int b) {
    static char str[maxn];
    static int li;
    suf.getstr(b,str,li);
    if(li) {
        reverse(str+1,str+1+li);
        return prf.pir(a,str,li);
    } else return 0;
}

inline int getans(const unordered_map<int,int> &lst) {
    Node cur;
    int ret = 0;
    for(unordered_map<int,int>::const_iterator it=lst.begin();it!=lst.end();it++) {
        cur.fil(it->first);
        if( cur.p + judge(cur.a,cur.b) < 2 ) adde(ret,it->second);
    }
    return ret;
}

int main() {
    static int n,m,li,cur;
    static char buf[55];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) {
        scanf("%s",buf+1) , li = strlen(buf+1) , prf.insert(prf.root,buf,1,li);
        reverse(buf+1,buf+1+li) , suf.insert(suf.root,buf,1,li);
    }
    prf.getfail() , suf.getfail() , f[0][((Node){prf.root,suf.root,0}).h()] = 1;
    for(int i=1;i<=n>>1;i++) cur ^=1 , trans(f[cur],f[cur^1]);
    if( n & 1 ) cur ^= 1 , trans_sig(f[cur],f[cur^1]);
    printf("%d\n",getans(f[cur]));
    return 0;
}
