#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
const int maxn=6e6+1e2;

int ch[maxn][10],nv[maxn],root,cnt;
std::vector<int> v[maxn];

inline void insert(char* s,int li,int tim) {
    int now = root;
    for(int i=1;i<=li;i++) {
        const int t = s[i] - 'a';
        if( !ch[now][t] ) ch[now][t] = ++cnt;
        now = ch[now][t] , ++nv[now];
        if( (signed)v[now].size() < nv[now] ) v[now].push_back(tim);
    }
}
inline void remove(char* s,int li) {
    int now = root;
    for(int i=1;i<=li;i++) {
        const int t = s[i] - 'a';
        now = ch[now][t] , --nv[now];
    }
}
inline int find(char* s,int li) {
    int now = root;
    for(int i=1;i<=li;i++)
        now = ch[now][(int)s[i]-'a'];
    return now;
}
inline int query(char* s,int li,int tar) {
    int p = find(s,li);
    if( (signed) v[p].size() <= tar ) return -1;
    return v[p][tar];
}

int main() {
    static char s[100];
    static int n,li,ans;
    scanf("%d",&n) , root = cnt = 1;
    for(int i=1,o,a,b,c,tar;i<=n;i++) {
        scanf("%d%s",&o,s+1) , li = strlen(s+1);
        if( o == 1 ) insert(s,li,i);
        else if( o == 2 ) remove(s,li);
        else if( o == 3 ) {
            scanf("%d%d%d",&a,&b,&c);
            tar = ( (long long) a * abs(ans) + b ) % c;
            ans = query(s,li,tar);
            printf("%d\n",ans);
        }
    }
    return 0;
}

