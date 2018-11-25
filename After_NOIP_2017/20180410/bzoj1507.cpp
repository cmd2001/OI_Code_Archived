#include<cstdio>
#include<cctype>
#include<ext/rope>
using namespace std;
using namespace __gnu_cxx;
const int maxn=2097162;

char in[maxn],o[15];
rope<char> s;

inline void getstr(char* s,int len) {
    char c;
    for(int i=0;i<len;i++) {
        while( (c=getchar()) == '\n' ) ;
        s[i] = c;
    }
    s[len] = '\0';
}
inline void printstr(int st,int len) {
    for(int i=0;i<len;i++) putchar(s[st+i]);
    putchar('\n');
}

int main() {
    static int n,now;
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++) {
        scanf("%s",o);
        switch(*o) {
            case 'M': scanf("%d",&now); break;
            case 'I': scanf("%d",&t) , getstr(in,t) , s.insert(now,in); break;
            case 'D': scanf("%d",&t) , s.erase(now,t); break;
            case 'G': scanf("%d",&t) , printstr(now,t); break;
            case 'P': --now; break;
            case 'N': ++now; break;
        }
    }
    return 0;
}

