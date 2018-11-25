#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
const int maxn=2e3+1e2;
const int inf=0x3f3f3f3f;

struct Automatic {
    int ch[maxn<<1][26],fa[maxn<<1],len[maxn<<1],cnt,root,last;
    
    inline int NewNode(int l) {
        len[++cnt] = l;
        return cnt;
    }
    inline void extend(int x) {
        int p = last;
        int np = NewNode(len[p]+1);
        while( p && !ch[p][x] ) ch[p][x] = np , p = fa[p];
        if( !p ) fa[np] = root;
        else {
            int q = ch[p][x];
            if( len[q] == len[p] + 1 ) fa[np] = q;
            else {
                int nq = NewNode(len[p]+1);
                memcpy(ch[nq],ch[q],sizeof(*ch)) , fa[nq] = fa[q];
                fa[q] = fa[np] = nq;
                while( p && ch[p][x] == q ) ch[p][x] = nq , p = fa[p];
            }
        }
        last = np;
    }
    inline void buildsam(char* sou,int li) {
        last = root = NewNode(0);
        for(int i=1;i<=li;i++) extend(sou[i]-'a');
    }
    inline void buildsqm(char* sou,int li) {
        last = root = 1;
        for(int i=0;i<=li;i++) {
            const int p = i + 1;
            for(int j=i+1;j<=li;j++) {
                const int t = sou[j] - 'a';
                if( !ch[p][t] ) ch[p][t] = j + 1;
            }
        }
    }
}a[2],b[2]; // 0 -> suffix automatic , 1 -> subsequence automatic .

char ina[maxn],inb[maxn];
bool vis[maxn<<1][maxn<<1];
int ans;
struct Node {
    int x,y,d;
};
std::queue<Node> q;

inline void core_bfs(const Automatic &a,const Automatic &b,const int &x,const int &y,const int &l) {
    for(int i=0;i<26;i++)
        if( a.ch[x][i] ) {
            if( !b.ch[y][i] ) ans = std::min(ans,l+1);
            else {
                const int tx = a.ch[x][i] , ty = b.ch[y][i];
                if( !vis[tx][ty] ) {
                    vis[tx][ty] = 1;
                    q.push((Node){tx,ty,l+1});
                }
            }
        }
}
inline void getans(const Automatic &a,const Automatic &b) {
    memset(vis,0,sizeof(vis)) , ans =  inf;
    q.push((Node){a.root,b.root,0}) , vis[a.root][b.root] = 1;
    while( q.size() ) {
        const Node pos = q.front(); q.pop();
        core_bfs(a,b,pos.x,pos.y,pos.d);
    }
}

int main() {
    static int la,lb;
    scanf("%s%s",ina+1,inb+1) , la = strlen(ina+1) , lb = strlen(inb+1);
    a[0].buildsam(ina,la) , a[1].buildsqm(ina,la) ,
    b[0].buildsam(inb,lb) , b[1].buildsqm(inb,lb) ;
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++) {
            getans(a[i],b[j]);
            if( ans != inf ) printf("%d\n",ans);
            else puts("-1");
        }
    return 0;
}

