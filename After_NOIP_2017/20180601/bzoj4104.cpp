#include<cstdio>
#include<utility>
#include<algorithm>
#include<cctype>
const int maxn=2e5+1e2;

int in[maxn],ans[maxn],n;
std::pair<int,int> dat[maxn];

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() + 1 , getint();
    for(int i=1;i<=n;i++) dat[i] = std::make_pair(in[i]=getint(),i);
    std::sort(dat+1,dat+1+n);
    for(int i=1,cur=1;i<=n;i++) ans[i] = dat[cur].first , cur = dat[cur].second;
    for(int i=2;i<=n;i++) printf("%d ",ans[i]);
    putchar('\n');
    return 0;
}
