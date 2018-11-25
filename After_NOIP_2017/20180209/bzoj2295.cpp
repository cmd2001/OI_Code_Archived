#include<cstdio>
#include<cstring>
const int maxn=1e5+1e2;
char in[maxn];
const char tar[]="luvletter";

int main() {
    static int T,len,now,ans;
    scanf("%d",&T);
    while(T--) {
        fgets(in,maxn,stdin) , len = strlen(in);
        while( *in == '\n' || *in == '\r' ) fgets(in,maxn,stdin) , len = strlen(in);
        ans = now = 0;
        for(int i=0;i<len;i++)
            if( in[i] == tar[now] ) {
                ans += ( now == 8 ), now = ( now + 1 ) % 9;
            }
        printf("%d\n",ans);
    }
    return 0;
}
