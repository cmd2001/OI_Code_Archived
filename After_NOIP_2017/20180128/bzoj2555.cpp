#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1.2e6+1e2,maxl=3e6+1e2;

char t[maxl],in[maxl];
int li,mask;

struct LCT {
    int ch[maxn][2],fa[maxn],sum[maxn],lazy[maxn];
    int stk[maxn],top;
    
    inline void add(int pos,int x) {
        if( !pos ) return;
        sum[pos] += x , lazy[pos] += x;
    }
    inline void push(int pos) {
        if( lazy[pos] ) {
            add(ch[pos][0],lazy[pos]) ,
            add(ch[pos][1],lazy[pos]) ,
            lazy[pos] = 0;
        }
    }
    inline bool isrt(int pos) {
        return pos != ch[fa[pos]][0] && pos != ch[fa[pos]][1];
    }
    inline int getid(int pos) {
        return pos == ch[fa[pos]][1];
    }
    inline void rotate(int pos) { // pos is the son .
        int f = fa[pos] , id = getid(pos);
        fa[pos] = fa[f];
        if( !isrt(f) ) ch[fa[pos]][getid(f)] = pos;
        ch[f][id] = ch[pos][id^1];
        if( ch[pos][id^1] ) fa[ch[pos][id^1]] = f;
        ch[pos][id^1] = f , fa[f] = pos;
    }
    inline void splay(int pos) {
        int i;
        for(i=pos;;i=fa[i]) {
            stk[++top] = i;
            if( isrt(i) ) break;
        }
        while( top )
            push(stk[top--]);
        while( !isrt(pos) ) {
            if( !isrt(fa[pos]) )
                rotate(fa[pos]);
            rotate(pos);
        }
    }
    inline void access(int pos) {
        int lst = 0;
        while( pos ) {
            splay(pos);
            ch[pos][1] = lst ,
            lst = pos ,
            pos = fa[pos];
        }
    }
    inline void link(int pos,int f) {
        fa[pos] = f;
        access(f) , splay(f) ;
        add(f,sum[pos]);
    }
    inline void cut(int pos) {
        access(pos) , splay(pos);
        add(ch[pos][0],-sum[pos]);
        fa[ch[pos][0]] = 0 , ch[pos][0] = 0;
    }
    inline int query(int pos) {
        splay(pos);
        return sum[pos];
    }
}lct;

struct SAM {
    int ch[maxn][26],fa[maxn],len[maxn],cnt,root,last;
    
    inline int NewNode(int ll) {
        len[++cnt] = ll;
        return cnt;
    }
    inline void fillfa(int s,int f) {
        fa[s] = f , lct.link(s,f);
    }
    inline void extend(int x) {
        int p = last;
        int np = NewNode(len[p]+1); lct.sum[np] = 1;
        while( p && !ch[p][x] )
            ch[p][x] = np , p = fa[p];
        if( !p ) fillfa(np,root);
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fillfa(np,q);
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q]));
                lct.cut(q);
                fillfa(nq,fa[q]);
                fillfa(q,nq) , fillfa(np,nq);
                while( p && ch[p][x] == q )
                    ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void init() {
        last = root = NewNode(0);
        insert();
    }
    inline void insert() {
        for(int i=1;i<=li;i++) {
            extend(in[i]-'A');
        }
    }
    inline int query() {
        int now = 1;
        for(int i=1;i<=li;i++) {
            const int t = in[i] - 'A';
            if( !ch[now][t] ) return 0;
            now = ch[now][t];
        }
        return lct.query(now);
    }
}sam;

inline void decode() {
    int len = strlen(t) , mm = mask;
    for(int i=0;i<len;i++) {
        mm = ( mm * 131 + i ) % len;
        swap(t[i],t[mm]);
    }
    li = len;
    memcpy(in+1,t,len+1);
}

int main() {
    static int m,ans;
    static char ope[10];
    scanf("%d",&m);
    scanf("%s",in+1) , li = strlen(in+1);
    sam.init();
    while( m-- ) {
        scanf("%s%s",ope,t) , decode();
        if( *ope == 'Q' ) {
            ans = sam.query();
            mask ^= ans;
            printf("%d\n",ans);
        } else sam.insert();
    }
    return 0;
}
