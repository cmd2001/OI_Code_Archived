#include<cstdio>
#include<algorithm>
#include<cctype>
const int maxn=26,inf=0x3f3f3f3f;

int su[maxn],ans=inf;

inline void gsu() {
    char ch;
    while( !isalpha(ch=getchar()) );
    do ++su[(int)ch-'a']; while( isalpha(ch=getchar()) );
}

int main() {
    gsu(); for(int i=0;i<26;i++) ans = std::min( ans , su[i] );
    printf("%d\n",ans);
    return 0;
}
