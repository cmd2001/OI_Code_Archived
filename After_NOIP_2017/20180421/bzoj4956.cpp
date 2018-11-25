#include<cstdio>
#include<cstring>
const int maxn=100;

char a[maxn],b[maxn];
bool can[maxn][maxn];

inline void floyd() {
    for(int k=0;k<26;k++)
        for(int i=0;i<26;i++)
            for(int j=0;j<26;j++)
                can[i][j] |= ( can[i][k] && can[k][j] );
}
inline bool judge() {
    int la = strlen(a) , lb = strlen(b);
    if( la != lb ) return 0;
    for(int i=0;i<la;i++) if( a[i] != b[i] && !can[a[i]-'a'][b[i]-'a'] ) return 0;
    return 1;
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s%s",a,b) , can[*a-'a'][*b-'a'] = 1;
    floyd();
    while(m--)  scanf("%s%s",a,b) , puts(judge()?"yes":"no");
    return 0;
}
