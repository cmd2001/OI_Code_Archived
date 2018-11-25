#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e1+1e1,maxe=1e2+1e1,maxl=26,maxs=1<<10,maxa=45;

int l,n,siz,fs;

struct ACautomatic {
    int ch[maxe][26],fail[maxe],eid[maxe],root,cnt;
    lli f[maxl][maxe][maxs]; // f[length][node][statement]
    ACautomatic() { root = cnt = 1; }
    inline void insert(char* s,int li,int id) {
        int pos = root;
        for(int i=1;i<=li;i++) {
            if( !ch[pos][(int)s[i]-'a'] ) ch[pos][(int)s[i]-'a'] = ++cnt;
            pos = ch[pos][(int)s[i]-'a'];
        }
        eid[pos] = 1 << ( id - 1 );
    }
    inline void buildfail() {
        queue<int> q;
        for(int i=0;i<26;i++) ch[root][i] ? q.push(ch[root][i]) , fail[ch[root][i]] = root : ch[root][i] = root;
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int i=0;i<26;i++) ch[pos][i] ? q.push(ch[pos][i]) , fail[ch[pos][i]] = ch[fail[pos]][i] : ch[pos][i] = ch[fail[pos]][i];
        }
    }
    inline lli dp() {
        lli ret = 0; f[0][root][0] = 1;
        for(int len=0;len<l;len++) for(int pos=1;pos<=cnt;pos++) for(int sta=0;sta<fs;sta++) if( f[len][pos][sta] ) {
            for(int nxt=0;nxt<26;nxt++) f[len+1][ch[pos][nxt]][sta|eid[ch[pos][nxt]]] += f[len][pos][sta];
        }
        for(int i=1;i<=cnt;i++) ret += f[l][i][fs-1];
        return ret;
    }
}acm;

char buf[maxn],in[maxn][maxn];
int len[maxn],sme[maxn][maxn]; // same length of suffix of i and prefix of j .
bool ban[maxn];

string ans[maxa],tmp[maxn];
int prmu[maxn],rem,acnt;
lli ways;

inline bool included(char* a,char* b,int la,int lb) {
    for(int st=1;st+lb-1<=la;st++) if( !memcmp(a+st,b+1,lb) ) return 1;
    return 0;
}
inline int calcsme(char* fir,char* sec,int lf,int lc) {
    for(int st=max(1,lf-lc+1);st<=lf;st++) {
        const int len = lf - st + 1;
        if( !memcmp(fir+st,sec+1,len)) return len;
    }
    return 0;
}
inline void solveprmu() {
    int su = len[prmu[1]];
    for(int i=2;i<=rem;i++) su += len[prmu[i]] , su -= sme[prmu[i-1]][prmu[i]];
    if( su != l ) return;
    string ret = in[prmu[1]] + 1;
    for(int i=2;i<=rem;i++) for(int j=sme[prmu[i-1]][prmu[i]]+1;j<=len[prmu[i]];j++) ret = ret + in[prmu[i]][j];
    ans[++acnt] = ret;
}

int main() {
    scanf("%d%d",&l,&n);
    for(int i=1;i<=n;i++) scanf("%s",buf) , tmp[i] = buf;
    sort(tmp+1,tmp+1+n) , n = unique(tmp+1,tmp+1+n) - tmp - 1;
    for(int i=1;i<=n;i++) memcpy(in[i]+1,tmp[i].c_str(),len[i]=tmp[i].length());
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if( i != j && included(in[i],in[j],len[i],len[j]) ) ban[j] = 1;
    for(int i=1;i<=n;i++) if( !ban[i] ) acm.insert(in[i],len[i],++siz);
    acm.buildfail() , fs = 1 << siz , printf("%lld\n",ways = acm.dp());
    if( ways <= 42 ) {
        for(int i=1;i<=n;i++) if( !ban[i] ) prmu[++rem] = i;
        for(int i=1;i<=n;i++) if( !ban[i] ) for(int j=1;j<=n;j++) if( !ban[j] ) sme[i][j] = calcsme(in[i],in[j],len[i],len[j]);
        do solveprmu(); while( next_permutation(prmu+1,prmu+1+rem) );
        sort(ans+1,ans+1+acnt);
        for(int i=1;i<=acnt;i++) printf("%s\n",ans[i].c_str());
    }
    return 0;
}

