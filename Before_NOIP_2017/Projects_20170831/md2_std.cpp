#include <cstdio>
#include <cstdlib>
#include <cstring>
#include<iostream>
using namespace std;

struct graphnode { int to, next; } graph[4000010]; int grapmr, n;
int deg[1000010];
void ginit (void)
{
    grapmr = n;
    for (int i = 0; i < n; i++) graph[i].next = -1;
}
void glink (int a, int b)
{
    int p = grapmr++;
    graph[p].to = b, graph[p].next = graph[a].next;
    graph[a].next = p; ++deg[a];
}
int set[1000010];
void sinit (void)
{
    for (int i = 0; i < n; i++) set[i] = i;
}
int sget (int a)
{
    return set[a] == a ? a : set[a] = sget(set[a]);
}
void schn (int a, int b)
{
    set[sget(a)] = sget(b);
}
int queue[1000010], now, add;
int pere[1000010], dist[1000010];
int mod, fact[1000010];
int proc (int ent)
{
    now = add = 0; int rt = ent, ed;
    dist[ent] = 0, queue[add++] = ent;
    while (now != add)
    {
        int cur = queue[now++];
        for (int p = graph[cur].next; p != -1; p = graph[p].next)
        {
            int tar = graph[p].to;
            if (dist[tar] < 0)
            {
                dist[tar] = dist[cur] + 1, queue[add++] = tar;
                if (dist[tar] > dist[rt]) rt = tar;
            }
        }
    }
    if (rt == ent) return -1; // 1 vertex
    now = add = 0; dist[rt] = 0, queue[add++] = rt, ed = rt;
    while (now != add)
    {
        int cur = queue[now++];
        for (int p = graph[cur].next; p != -1; p = graph[p].next)
        {
            int tar = graph[p].to;
            if (tar != pere[cur])
            {
                pere[tar] = cur, dist[tar] = dist[cur] + 1, queue[add++] = tar;
                if (dist[tar] > dist[ed]) ed = tar;
            }
        }
    }
    if (dist[ed] <= 2) // 2 or 3 vertices
    {
        int mid = pere[ed];
        return 2 * fact[deg[mid]] % mod;
    }
    int res = 4, lst = ed; // more vertices
    for (int s = pere[ed]; s >= 0; lst = s, s = pere[s])
    {
        int ch = 0;
        for (int p = graph[s].next; p != -1; p = graph[p].next)
        {
            int tar = graph[p].to;
            if (tar != pere[s] && tar != lst)
            {
                if (deg[tar] >= 2) return -2; // Invalid
                else ++ch;
            }
        }
        if (s == pere[ed]) ++ch;
        if (pere[s] == rt) ++ch;
        res = res * fact[ch] % mod;
    } return res;
}
int main ()
{
    //freopen("md2.in", "r", stdin);
    //freopen("md2.out", "w", stdout);
    int m, ans = 0;
    int single = 0, part = 0;
    scanf("%d %d %d", &n, &m, &mod);
    if (m >= n) goto byebye;
    fact[0] = 1; for (int i = 1; i <= n; i++) fact[i] = (__int64)fact[i - 1] * i % mod;
    ginit(), sinit();
    memset(deg, 0, sizeof deg);
    for (int i = 0; i < m; i++)
    {
        int a, b; scanf("%d %d", &a, &b); --a, --b;
        if (sget(a) == sget(b)) goto byebye;
        glink(a, b), glink(b, a), schn(a, b);
    }
    memset(dist, -1, sizeof dist);
    memset(pere, -1, sizeof pere);
    ans = 1;
	#define debug cout
    for (int i = 0; i < n; i++) if (dist[i] == -1)
    {
        int ret = proc(i);
        if (ret == -2) { ans = 0; goto byebye; }
        else if (ret == -1) ++single;
        else
        {
        	debug<<"ret = "<<ret<<endl;
            ++part;
            ans = (__int64)ans * ret % mod;
        }
    }
    debug<<"part = "<<part<<endl;
    ans = (__int64)ans * fact[part] % mod;
    
    debug<<"before single ans = "<<ans<<endl;
    for (int i = n - single + 2; i <= n + 1; i++)
	{
		debug<<"multied "<<i<<endl;
		ans = (__int64)ans * i % mod;
	}
byebye:
    printf("%d\n", ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
