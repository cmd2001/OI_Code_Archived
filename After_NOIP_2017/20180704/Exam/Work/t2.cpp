#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+1e2;

int in[maxn],n,m;
char o[maxn];

namespace SubTask1 {
    inline void work() {
        for(int i=1;i<=m;i++) {
            if( o[i] == 'A' ) {
                for(int j=1;j<=n;j++) if( in[j-1] > in[j] ) ++in[j];
            } else {
                for(int j=n;j;j--) if( in[j+1] > in[j] ) ++in[j];
            }
        }
    }
}
namespace SubTask2 {
    inline void work() {
        for(int i=1;i<=n;i++) if( in[i] < in[i-1] ) in[i] += min( in[i-1] - in[i] , m );
        for(int i=1;i<=n;i++) printf("%d%c",in[i],i!=n?' ':'\n');
    }
}

inline int getint() {
    int ret = 0; char ch;
    while( !isdigit(ch=getchar()) ) ;
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
    scanf("%s",o+1);
    if( n <= 1000 && m <= 1000 ) SubTask1::work();
    else SubTask2::work();
    for(int i=1;i<=n;i++) printf("%d%c",in[i],i!=n?' ':'\n');
    return 0;
}

