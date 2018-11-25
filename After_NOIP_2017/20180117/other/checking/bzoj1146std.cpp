#include <cstdio>
#include <vector>
#include <algorithm>

inline int nextChar(void)
{
    return getchar();
    const static int siz = 1024;
    
    static char buf[siz];
    static char *hd = buf + siz;
    static char *tl = buf + siz;
    
    if (hd == tl)
        fread(hd = buf, 1, siz, stdin);
        
    return *hd++;
}

inline int nextInt(void)
{
    register int ret = 0;
    register int neg = false;
    register int bit = nextChar();
    
    for (; bit < 48; bit = nextChar())
        if (bit == '-')neg ^= true;
        
    for (; bit > 47; bit = nextChar())
        ret = ret * 10 + bit - 48;
        
    return neg ? -ret : ret;
}

const int siz = 80005;

int N, M;

int tim[siz];

int map[siz << 1], tot;

int opt[siz], opx[siz], opy[siz];

int edges;
int hd[siz];
int to[siz << 1];
int nt[siz << 1];

inline void addEdge(int x, int y)
{
    nt[edges] = hd[x]; to[edges] = y; hd[x] = edges++;
    nt[edges] = hd[y]; to[edges] = x; hd[y] = edges++;
}

int dfn;
int arv[siz];
int lev[siz];
int dep[siz];
int fa[siz][17];

void preworkDFS(int u, int f)
{
    arv[u] = ++dfn;
    
    for (int i = 1; i <= 16; ++i)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        
    for (int i = hd[u], v; ~i; i = nt[i])
        if ((v = to[i]) != f)
        {
            fa[v][0] = u;
            dep[v] = dep[u] + 1;
            preworkDFS(v, u);
        }
        
    lev[u] = dfn + 1;
}

inline int lca(int a, int b)
{
    if (dep[a] < dep[b])
        a ^= b ^= a ^= b;
        
    for (int i = 16; i >= 0; --i)
        if (dep[fa[a][i]] >= dep[b])
            a = fa[a][i];
            
    if (a == b)return a;
    
    for (int i = 16; i >= 0; --i)
        if (fa[a][i] != fa[b][i])
            a = fa[a][i], b = fa[b][i];
            
    return fa[a][0];
}

int cnt;
int root[siz];
int ls[siz * 80];
int rs[siz * 80];
int sm[siz * 80];

std::vector<int> add;
std::vector<int> sub;

inline void clear(void)
{
    add.clear();
    sub.clear();
}

void insert(int l, int r, int &t, int f, int p, int v)
{
    t = ++cnt;
    
    ls[t] = ls[f];
    rs[t] = rs[f];
    
    sm[t] = sm[f] + v;
    
    if (l != r)
    {
        int mid = (l + r) >> 1;
        
        if (p <= mid)
            rs[t] = rs[f], insert(l, mid, ls[t], ls[f], p, v);
        else
            ls[t] = ls[f], insert(mid + 1, r, rs[t], rs[f], p, v);
    }
}

int query(int l, int r, int k)
{
    if (l == r)return l;
    
    int mid = (l + r) >> 1, sn = 0, sr = 0;
    
    for (int i = 0; i < add.size(); ++i)sr += sm[rs[add[i]]], sn += sm[add[i]];
    for (int i = 0; i < sub.size(); ++i)sr -= sm[rs[sub[i]]], sn -= sm[sub[i]];
    
    if (sn < k)
        return -1;
    if (sr < k)
    {
        for (int i = 0; i < add.size(); ++i)add[i] = ls[add[i]];
        for (int i = 0; i < sub.size(); ++i)sub[i] = ls[sub[i]];
        
        return query(l, mid, k - sr);
    }
    else
    {
        for (int i = 0; i < add.size(); ++i)add[i] = rs[add[i]];
        for (int i = 0; i < sub.size(); ++i)sub[i] = rs[sub[i]];
        
        return query(mid + 1, r, k);
    }
}

int bit[siz];

inline void modify(int t, int p, int d)
{
    for (int i = t; i <= dfn; i += i&-i)
        insert(1, tot, bit[i], bit[i], p, d);
}

inline void addQuery(int t)
{
    add.push_back(root[t]);
    
    for (int i = arv[t]; i; i -= i&-i)
        add.push_back(bit[i]);
}

inline void subQuery(int t)
{
    sub.push_back(root[t]);
    
    for (int i = arv[t]; i; i -= i&-i)
        sub.push_back(bit[i]);
}

void buildDFS(int u, int f)
{
    insert(1, tot, root[u], root[f], tim[u], 1);
    
    for (int i = hd[u]; ~i; i = nt[i])
        if (to[i] != f)buildDFS(to[i], u);
}

signed main(void)
{
    N = nextInt();
    M = nextInt();
    
    for (int i = 0; i <= N; ++i)
        hd[i] = -1;
    
    for (int i = 1; i <= N; ++i)
        tim[i] = map[++tot] = nextInt();
        
    for (int i = 1; i < N; ++i)
        addEdge(nextInt(), nextInt());
        
    for (int i = 1; i <= M; ++i)
    {
        opt[i] = nextInt();
        opx[i] = nextInt();
        opy[i] = nextInt();
        
        if (!opt[i])
            map[++tot] = opy[i];
    }
    
    std::sort(map + 1, map + tot + 1);
    
    tot = std::unique(map + 1, map + tot + 1) - map - 1;
    
    for (int i = 1; i <= N; ++i)
        tim[i] = std::lower_bound(map + 1, map + tot + 1, tim[i]) - map;
        
    for (int i = 1; i <= M; ++i)if (!opt[i])
        opy[i] = std::lower_bound(map + 1, map + tot + 1, opy[i]) - map;
            
    preworkDFS(1, 0); buildDFS(1, 0);
    
    for (int i = 1; i <= M; ++i)
        if (!opt[i])
        {
            int x = opx[i];
            int y = opy[i];
            
            modify(arv[x], tim[x], -1);
            modify(lev[x], tim[x], +1);
            
            tim[x] = y;
            
            modify(arv[x], tim[x], +1);
            modify(lev[x], tim[x], -1);
        }
        else
        {
            clear();

            int x = opx[i];
            int y = opy[i];
            int t = lca(x, y);
            
            addQuery(x);
            addQuery(y);
            subQuery(t);
            subQuery(fa[t][0]);
            
            int ans = query(1, tot, opt[i]);
            
            if (ans == -1)
                puts("invalid request!");
            else
                printf("%d\n", map[ans]);
        }
}