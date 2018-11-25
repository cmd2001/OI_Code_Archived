#include<cstdio>
#include<cstring>
#include<queue>
#include<utility>
#include<cctype>
const int maxn=1e3+1e2;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

char in[maxn][maxn];
int dis[maxn][maxn];
int n,m;

inline void bfs() {
    std::queue<std::pair<int,int> > q; memset(dis,-1,sizeof(dis));
    #define legal(x,y) (0<x&&x<=n&&0<y&&y<=m)
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(in[i][j]-'0') dis[i][j] = 0 , q.push(std::make_pair(i,j));
    while( q.size() ) {
        const int x = q.front().first , y = q.front().second; q.pop();
        for(int i=0;i<4;i++) {
            const int tx = x + dx[i] , ty = y + dy[i];
            if( legal(tx,ty) && !~dis[tx][ty] ) dis[tx][ty] = dis[x][y] + 1 , q.push(std::make_pair(tx,ty));
        }
    }
    #undef legal
}

namespace FastIO {
    static const int BS = 1 << 21;
    char ibuf[BS],*ist,*ied,obuf[BS],*oed=obuf;
    inline char nextchar() {
        if( ist == ied ) ied = ibuf + fread(ist=ibuf,1,BS,stdin);
        return ist == ied ? -1 : *ist++;
    }
    inline int getint() {   
        int ret = 0 , ch;
        while( !isdigit(ch=nextchar()) );
        do ret = ret * 10 + ch - '0'; while( isdigit(ch=nextchar()) );
        return ret;
    }
    inline void getstr(char* s) {
        char ch;
        while( !isdigit(ch=nextchar()) );
        do *s++ = ch; while( isdigit(ch=nextchar()) );
    }
    inline void flush() {
        fwrite(obuf,1,oed-obuf,stdout) , oed = obuf;
    }
    inline void printchar(const char &c) {
        *oed++ = c;
        if( oed == obuf + BS ) flush();
    }
    inline void printint(int x) {
        static int stk[20],top;
        if( !x ) printchar('0');
        while(x) stk[++top] = x % 10 , x /= 10;
        while(top) printchar(stk[top--]+'0');
    }
}

int main() {
    n = FastIO::getint() , m = FastIO::getint();
    for(int i=1;i<=n;i++) FastIO::getstr(in[i]+1);
    bfs();
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) FastIO::printint(dis[i][j]) , FastIO::printchar(' ');
        FastIO::printchar('\n');
    }
    return FastIO::flush() , 0;
}

