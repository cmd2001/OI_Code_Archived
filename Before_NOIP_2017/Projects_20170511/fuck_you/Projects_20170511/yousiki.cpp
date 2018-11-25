/**************************************************************
    Problem: 4869
    User: YOUSIKI
    Language: C++
    Result: Accepted
    Time:10864 ms
    Memory:46528 kb
****************************************************************/
 
#include <cstdio>
 
__inline int nextChr(void)
{
    /*static const int siz = 1 << 22;
     
    static char buf[siz];
    static char *hd = buf + siz;
    static char *tl = buf + siz;
     
    if (hd == tl)fread(hd = buf, 1, siz, stdin);
     
    return int(*hd++);*/
    return getchar();
}
 
__inline int nextInt(void)
{
    register int r = 0;
    register int f = 0;
    register int c = nextChr();
     
    for (; c < 48; c = nextChr())
        if (c == '-')f = 1;
         
    for (; c > 47; c = nextChr())
        r = r * 10 + c - 48;
         
    return f ? -r : r;
}
 
__inline int calcPhi(int num)
{
    int ret = num;
     
    for (int i = 2; i * i <= num; ++i)
        if (num % i == 0)
        {
            ret = ret / i * (i - 1);
             
            do
                num /= i;
            while (num % i == 0);
        }
     
    if (num > 1)
        ret = ret / num * (num - 1);
         
    return ret;
}
 
__inline int pow(int a, int b, int c)
{
    int r = 1;
         
    a = (a % c + c) % c;
     
    for (; b; b >>= 1, a = 1LL * a * a % c)
        if (b & 1)r = 1LL * r * a % c;
         
    return r;
}
 
const int mxn = 50005;
const int mxm = 105;
 
int n, m, p, q;
 
int fat[mxn];
int bit[mxn];
 
int num[mxn][mxm];
int vis[mxn][mxm];
 
int fac[mxm], cnt;
 
__inline int find(int u)
{
    static int stk[mxn], top;
     
    while (fat[u] != u)
        stk[++top] = u, u = fat[u];
         
    while (top)fat[stk[top--]] = u;
     
    return u;
}
 
__inline void add(int x, int y)
{
    y = (y % p + p) % p;
     
    for (; x <= n; x += x & -x)
        bit[x] = (bit[x] + y) % p;
}
 
__inline int ask(int x, int y)
{
    int r = 0; --x;
     
    for (; x; x -= x & -x)
        r = (r - bit[x]) % p;
         
    for (; y; y -= y & -y)
        r = (r + bit[y]) % p;
         
    return (r + p) % p;
}
 
namespace case1
{
    __inline void main(void)
    {
        for (int i = 1; i <= m; ++i)
        {
            int k = nextInt();
            int l = nextInt();
            int r = nextInt();
             
            if (k)
                printf("%d\n", ask(l, r));
            else
            {
                for (int j = find(l); j <= r; j = find(j + 1))
                    add(j, 1 - num[j][0]), fat[j] = j + 1;
            }
        }
    }
}
 
namespace case2
{
    __inline bool exd(int a, int b, int c)
    {
        int r = 1;
         
        for (; b; b >>= 1, a = a * a)
        {
            if (b & 1)
            {
                if (1LL * r * a >= c)
                    return true;
                 
                r = 1LL * r * a;
            }
             
            if (1LL * a * a >= c && b >> 1)
                return true;
        }
         
        return false;
    }
     
    __inline void update(int t)
    {
        bool flag = true;
         
        for (int j = 0; j < cnt; ++j)
        {
            int rec = num[t][j];
             
            if (vis[t][j])
                num[t][j] = pow(q, num[t][j + 1] + fac[j + 1], fac[j]);
            else
            {
                vis[t][j] = exd(q, num[t][j], fac[j + 1]);
                num[t][j] = pow(q, num[t][j], fac[j]);
            }
             
            if (rec != num[t][j])flag = false;
        }
         
        if (flag)fat[t] = t + 1;
    }
     
    __inline void main(void)
    {
        fac[cnt = 0] = p;
         
        for (int t = p; t != 1; )
            fac[++cnt] = t = calcPhi(t); 
         
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= cnt; ++j)
                num[i][j] = num[i][0] % fac[j];
             
            for (int j = 0; j < cnt; ++j)
                vis[i][j] = (num[i][0] >= fac[j + 1]);
        }
         
        for (int i = 1; i <= m; ++i)
        {
            int k = nextInt();
            int l = nextInt();
            int r = nextInt();
             
            if (k)
                printf("%d\n", ask(l, r));
            else
            {
                for (int j = find(l); j <= r; j = find(j + 1))
                    add(j, -num[j][0]), update(j), add(j, +num[j][0]);
            }
        }
    }
}
 
signed main(void)
{

    freopen("data.in", "r", stdin);
    freopen("yousiki.out", "w", stdout);

     
    n = nextInt();
    m = nextInt();
    p = nextInt();
    q = nextInt();
         
    for (int i = 1; i <= n + 1; ++i)fat[i] = i;
     
    for (int i = 1; i <= n; ++i)
        num[i][0] = nextInt(), add(i, num[i][0]);
     
    if (q == 1)
        case1::main();
    else
        case2::main();
         
    fclose(stdin);
    fclose(stdout);
     
    return 0;
}
