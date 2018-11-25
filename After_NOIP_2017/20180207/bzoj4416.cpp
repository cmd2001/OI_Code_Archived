#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e2+1e1,maxp=1<<22;

char in[maxn];
int f[maxp],nxt[maxn][27],lst[27];
int n,len,full;

int main() {
    static int T;
    scanf("%d",&T);
    while( T-- ) {
        scanf("%d%s",&n,in+1) , len = strlen(in+1);
        if( n > 21 ) {
            puts("NO");
            continue;
        }
        memset(f,0,sizeof(f)) , full = ( 1 << n );
        for(int i=0;i<n;i++) lst[i] = len + 1;
        memcpy(nxt[len+1],lst,sizeof(lst));
        for(int i=len;~i;i--) {
            memcpy(nxt[i],lst,sizeof(lst));
            if(i) lst[in[i]-'a'] = i;
        }
        for(int i=1;i<full;i++)
            for(int t=0;t<n;t++)
                if( i & ( 1 << t ) )
                    f[i] = max( f[i] , nxt[f[i^(1<<t)]][t] );
        puts(f[full-1]!=len+1?"YES":"NO");
    }
    return 0;
}
