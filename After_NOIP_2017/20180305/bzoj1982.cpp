#include<string>
#include<cstdio>
#include<algorithm>
const int maxn=1e5+1e2;

char buf[maxn];
std::string in[maxn];
int n;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%s",buf+1) , in[i] = buf+1;
    if( n & 1 ) return puts("first player"),0;
    std::sort(in+1,in+1+n);
    for(int i=2;i<=n;i+=2) if( in[i] != in[i-1] ) return puts("first player"),0;
    puts("second player");
    return 0;
}
