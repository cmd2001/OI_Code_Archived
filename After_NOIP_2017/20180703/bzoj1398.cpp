#include<cstdio>
#include<cstring>
const int maxn=2e6+1e2;

char in[maxn>>1];

struct SuffixAutomatic {
    int ch[maxn][10],len[maxn],fa[maxn],cnt,root,last;
    inline int NewNode(int x) {
        return len[++cnt] = x , cnt;
    }
    SuffixAutomatic() { last = root = NewNode(0); }
    inline void extend(int x) {
        int p = last , np = NewNode(len[p]+1);
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            const int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                const int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(ch[q])) , fa[nq] = fa[q] , fa[np] = fa[q] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline bool pir(char* s,int li) {
        int pos = root;
        for(int i=1;i<=li;i++) {
            if( !ch[pos][(int)s[i]-'0'] ) return 0;
            pos = ch[pos][(int)s[i]-'0'];
        }
        return 1;
    }
    inline void dfs(int len) {
        int pos = root;
        for(int i=1;i<=len;i++) {
            int t = -1;
            for(int j=0;j<10&&!~t;j++) if( ch[pos][j] ) t = j;
            putchar('0'+t) , pos = ch[pos][t];
        }puts("");
    }
}sam;

int main() {
    static int li;
    scanf("%s",in+1) , li = strlen(in+1);
    for(int i=1;i<=li;i++) sam.extend(in[i]-'0');
    for(int i=1;i<=li;i++) sam.extend(in[i]-'0');
    scanf("%s",in+1) , li = strlen(in+1);
    if( sam.pir(in,li) ) {
        puts("Yes") , sam.dfs(li);
    } else puts("No");
    return 0;
}

