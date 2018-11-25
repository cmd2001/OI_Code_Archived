#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
const int maxn=5e6+1e2;

char in[maxn],cha[maxn];
int s[maxn],t[maxn],nxt[maxn],tim[maxn],cnt,root,n;
lli ans;

inline int findnxt(int pos,char c) {
    static int i,lst;
    if( !s[pos] ) return cha[s[pos]=++cnt] = c , cnt;
    for(i=s[pos],lst=0;i&&cha[i]!=c;lst=i,i=nxt[i]) ;
    if( !i ) return cha[nxt[lst]=++cnt] = c , cnt;
    else return i; 
}

inline void insert(int len) {
    if( !root ) root = cnt = 1;
    int pos = root;
    for(int i=1;i<=len;i++) pos = findnxt(pos,in[i]) , ans = std::max( ans , (lli) i * ++tim[pos] );
}

inline int readstr(char* s) {
    int len;
    while(1) {
        fgets(s+1,maxn-1,stdin);
        len = strlen(s+1);
        for(int i=1;i<=len;i++) if( s[i] == '\r' ) s[i] = '\n';
        while( len && s[len] == '\n' ) --len;
        if( len ) break;
    }
    return len;
}

int main() {
    scanf("%d",&n) , root = cnt = 1;
    while(n--) insert(readstr(in));
    printf("%lld\n",ans);
    return 0;
}
