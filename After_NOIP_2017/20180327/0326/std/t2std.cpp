#include <queue>
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
 
inline int getch() {
    static int size = 0, pt = 0;
    static char buf[1048576];
    if(size == pt) {
        pt = buf[size = fread(buf, sizeof(char), 1048575, stdin)] = '\0';
        if(size == 0)
            return EOF;
    }
    return buf[pt++];
}
 
inline int get_int() {
    register int ch, flag = 1, x;
    for(ch = getch(); ch != EOF && !isdigit(ch); ch = getch())
        if(ch == '-') flag = -1;
    if(ch == EOF) return EOF;
    for(x = ch ^ '0', ch = getch(); isdigit(ch); ch = getch())
        x = (x << 3) + (x << 1) + (ch ^ '0');
    return x * flag;
}
 
inline int get_str(char *str) {
    int len = 0;
    int ch = getch();
    while(!islower(ch)) ch = getch();
    do *str++ = ch, ++len, ch = getch(); while(islower(ch));
    *str = '\0';
    return len;
}
 
struct IN {
    const IN& operator >> (char *st) const { return get_str(st), *this; }
    const IN& operator >> (char &ch) const { return ch = getch(), *this; }
    const IN& operator >> (int  &x) const { return x = get_int(), *this; }
} in;
 
namespace OUTBUFFER {
    char buf[1048576];
    int pt;
    inline void putch(register char ch) { buf[pt++] = ch; }
    inline void flush() { if(pt) fwrite(buf,sizeof(char),pt,stdout), pt = 0; }
    inline void check() { if(pt > 1000000) flush(); }
}
 
template <class T>
inline void put_int(register T x) {
    char temp[23];
    register int top;
    if(x == 0) return OUTBUFFER::putch('0');
    if(x < 0) OUTBUFFER::putch('-'), x = -x;
    for(top = 0; x; temp[++top] = x % 10, x /= 10);
    do OUTBUFFER::putch(temp[top] ^ '0'); while(--top);
    OUTBUFFER::check();
}
 
struct OUT {
    OUT() { OUTBUFFER::pt = 0; }
    ~OUT() { OUTBUFFER::flush(); }
    const OUT &operator << (const char *str) const {
        while(*str) OUTBUFFER::putch(*str++);
        OUTBUFFER::check();
        return *this;
    }
    const OUT &operator << (register char ch) const {
        return OUTBUFFER::putch(ch), *this;
    }
    const OUT &operator << (register int x) const {
        return put_int<int>(x), *this;
    }
    const OUT &operator << (register long long x) const {
        return put_int<long long>(x), *this;
    }
} out;
 
struct Graph {
std::vector<std::pair<int, int> > E[2005];
bool reachable[2005];
void clear(int N) {
    for(int i = 1; i <= N; ++i) E[i].clear();
    memset(reachable, 0, sizeof(bool) * (N + 1));
}
void push_back(int f, int t, int len) {
    E[f].push_back(std::make_pair(t, len));
}
void bfs(register int f) {
    static std::queue<int> Que;
    reachable[f] = true;
    Que.push(f);
    while(!Que.empty()) {
        register int u = Que.front();
        Que.pop();
        for(std::vector<std::pair<int, int> >::iterator it = E[u].begin(), _end = E[u].end();
            it != _end; ++it) {
            if(!reachable[it->first]) {
                reachable[it->first] = true;
                Que.push(it->first);
            }
        }
    }
}
} G, I;
 
struct MaxFlow {
typedef long long ll;
const static int MAXN = 2005, MAXM = 8005;
const static ll INFINITY=0x3FFFFFFFFFFFFFFFLL;
 
int N, src, dtn, Head[MAXN], Cur[MAXN], Dep[MAXN],
    Next[MAXM], To[MAXM], gIndex;
ll Cap[MAXM];
 
void init(int n, int f, int t) {
    N = n, src = f, dtn = t, gIndex = 1;
    memset(Head, 0, sizeof(Head[0]) * (N + 2));
}
 
void addEdge(int f, int t, ll cap) {
    Next[++gIndex] = Head[f]; Head[f] = gIndex; To[gIndex] = t; Cap[gIndex] = cap;
    Next[++gIndex] = Head[t]; Head[t] = gIndex; To[gIndex] = f; Cap[gIndex] = 0;
}
 
inline static ll Min(ll a, ll b) { return a < b ? a : b; }
 
inline bool BFS() {
    static int Que[MAXN], Top;
    register int i, u, v, e;
    for(i = 1; i <= N; ++i)
        Cur[i] = Head[i], Dep[i] = -1;
    Dep[Que[Top = 1] = src] = 0;
    for(i = 1; i <= Top; ++i) {
        u = Que[i];
        for(e = Head[u]; e; e = Next[e]) {
            if(Cap[e] && Dep[v = To[e]] == -1) {
                Dep[v] = Dep[u] + 1;
                if(v == dtn) return true;
                Que[++Top] = v;
            }
        }
    }
    return false;
}
inline ll DFS(const int u, const ll flow) {
    register ll delta, res = 0;
    if(u == dtn) return flow;
    for(register int &e = Cur[u], v; e; e = Next[e]) {
        if(Cap[e] && Dep[v = To[e]] == Dep[u] + 1 && (delta = DFS(v, Min(flow - res, Cap[e])))) {
            res += delta;
            Cap[e] -= delta;
            Cap[e ^ 1] += delta;
            if(res == flow) break;
        }
    }
    if(res != flow) Dep[u] = -1;
    return res;
}
 
ll maxFlow() {
    ll ret = 0;
    while(BFS()) {
        ll delta = DFS(src, INFINITY);
        if(delta == INFINITY) return -1;
        ret += delta;
    }
    return ret;
}
 
} MF;
 
int N, M;
 
inline void init() {
    N = get_int(), M = get_int();
    G.clear(N), I.clear(N);
    for(int i = 1; i <= M; ++i) {
        int u = get_int(), v = get_int(), w = get_int();
        G.push_back(u, v, w);
        I.push_back(v, u, w);
    }
    G.bfs(1), I.bfs(N);
    MF.init(N, 1, N);
    for(register int i = 1; i <= N; ++i) {
        if(!G.reachable[i]) continue;
        for(std::vector<std::pair<int, int> >::iterator it = G.E[i].begin(), _end = G.E[i].end();
            it != _end; ++it) {
            if(!I.reachable[it->first]) continue;
            MF.addEdge(i, it->first, it->second);
            MF.addEdge(it->first, i, MaxFlow::INFINITY);
        }
    }
}
 
inline void solve() {
    out <<MF.maxFlow() <<'\n';
}
 
int main() {
    int T = get_int();
    while(T--) {
        init();
        solve();
    }
    return 0;
}