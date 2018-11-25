#include<cstdio>
#include<utility>
#include<algorithm>
const int maxn=5e5+1e2;

char in[maxn],ans[maxn];
int n,icnt[2],acnt[2];
std::pair<char,int> dat[maxn];

int main() {
    scanf("%d%s",&n,in+1);
    for(int i=1;i<=n;i++) dat[i] = std::make_pair(in[i],i) , ++icnt[in[i]-'0'];
    std::sort(dat+1,dat+1+n);
    for(int i=1,cur=1;i<=n;i++) ++acnt[(ans[i]=dat[cur].first)-'0'] , cur = dat[cur].second;
    for(int i=0;i<2;i++) if( icnt[i] != acnt[i] ) return puts("No Solution"),0;
    puts(ans+1);
    return 0;
}
