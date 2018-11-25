#include<cstdio>
#include<cstring>
#include<cctype>
#define bool unsigned char
const int maxn=22,maxm=1e6+1e2,maxd=maxn*10;

char in[maxm];
int ch[maxd][26],root,cnt;
bool isend[maxd],f[maxm];
int n,m,ans;

inline void insert(int pos,char* s,int len) {
    for(int i=1;i<=len;i++) {
        const int t = s[i] - 'a';
        if( !ch[pos][t] ) ch[pos][t] = ++cnt;
        pos = ch[pos][t];
    }
    isend[pos] = 1;
}
inline void getans(char* s,int len) {
    memset(f+1,0,sizeof(bool)*len);
    ans = 0 , f[0] = 1;
    for(int i=0;i<=len;i++) {
        if( f[i] ) {
            ans = i;
            int now = root;
            for(int j=i+1;j<=len;j++) {
                int t = s[j] - 'a';
                if( !ch[now][t] ) break;
                now = ch[now][t];
                f[j] |= isend[now];
            }
        }
    }
}

inline char nextchar() {
    static char buf[1<<25],*st=buf+(1<<25),*ed=buf+(1<<25);
    if( st == ed ) ed = buf + fread(st=buf,1,1<<25,stdin);
    return st != ed ? *st++ : -1;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
inline void getstr(char* dst,int &len) {
    char ch;
    len = 0;
    while( !isalpha(ch=nextchar()) );
    do dst[++len]=ch; while( isalpha(ch=nextchar()) );
}

int main() {
    static int n,m,len;
    n = getint() , m = getint();
    
    root = cnt = 1;
    for(int i=1;i<=n;i++) {
        getstr(in,len);
        insert(root,in,len);
    }
    
    for(int i=1;i<=m;i++) {
        getstr(in,len);
        getans(in,len);
        printf("%d\n",ans);
    }
    
    return 0;
}
