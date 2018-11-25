#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=2e7+1e1,maxm=1e5+1e2;

int ch[maxn][4],len[maxn],fa[maxn];
char in[maxn>>1],tar[maxm];
int root,last;

inline int NewNode(int ll) {
    static int cnt = 0;
    len[++cnt] = ll;
    return cnt;
}
inline void extend(int x) {
    int p = last;
    int np = NewNode(len[p]+1);
    while( p && !ch[p][x] )
        ch[p][x] = np , p = fa[p];
    if( !p )
        fa[np] = root;
    else {
        int q = ch[p][x];
        if( len[q] == len[p] + 1 )
            fa[np] = q;
        else {
            int nq = NewNode(len[p]+1);
            fa[nq] = fa[q];
            memcpy(ch[nq],ch[q],sizeof(ch[q]));
            fa[q] = fa[np] = nq;
            while( p && ch[p][x] == q )
                ch[p][x] = nq , p = fa[p];
        }
    }
    last = np;
}

inline int getans(char* tar,int li) {
    int now = root , ret = 0;
    for(int i=1;i<=li;i++) {
        const int t = tar[i];
        if( !ch[now][t] ) return ret;
        now = ch[now][t] , ++ret;
    }
    return ret;
}

inline char trans(char x) {
    switch(x) {
        case 'E' : return 0;
        case 'S' : return 1;
        case 'W' : return 2;
        case 'N' : return 3;
    }
    return -1;
}

int main() {
    static int n,m,li;
    scanf("%d%d",&n,&m);
    scanf("%s",in+1);
    for(int i=1;i<=n;i++)
        in[i] = trans(in[i]);
    
    last = root = NewNode(0);
    for(int i=1;i<=n;i++)
        extend(in[i]);
    
    while( m-- ) {
        scanf("%s",tar+1);
        li = strlen(tar+1);
        for(int i=1;i<=li;i++)
            tar[i] = trans(tar[i]);
        printf("%d\n",getans(tar,li));
    }
    
    return 0;
}


