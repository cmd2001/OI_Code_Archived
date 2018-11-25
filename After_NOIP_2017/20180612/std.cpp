#include<bits/stdc++.h>  
#define debug cout
using namespace std;  
const int MAXN = 65536 + 5;  
const int nxt[3] = {1, 2, 0};  
const double INF = 5e4;  
const double eps = 1e-5;  
template <typename T> void read(T &x) {  
    x = 0; int f = 1;  
    char c = getchar();  
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;  
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';  
    x *= f;  
}  
template <typename T> void write(T x) {  
    if (x < 0) x = -x, putchar('-');  
    if (x > 9) write(x / 10);  
    putchar(x % 10 + '0');  
}  
template <typename T> void writeln(T x) {  
    write(x);  
    puts("");  
}  
struct point {double x, y, z; };  
int mode, n, m;  
bool operator < (point a, point b) {  
    if (mode == 0) return a.x < b.x;  
    else if (mode == 1) return a.y < b.y;  
    else return a.z < b.z;  
}  
void chkmin(point &a, point b) {  
    a.x = min(a.x, b.x);  
    a.y = min(a.y, b.y);  
    a.z = min(a.z, b.z);  
}  
void chkmax(point &a, point b) {  
    a.x = max(a.x, b.x);  
    a.y = max(a.y, b.y);  
    a.z = max(a.z, b.z);  
}  
struct Info {  
    int home;  
    bool use;  
    point pos;  
};  
bool operator < (Info a, Info b) {  
    return a.pos < b.pos;  
}  
double dist(point a, point b) {  
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));  
}  
struct KDTree {  
    struct Node {  
        Info info;  
        point l, r;  
        int mode, fa, lc, rc;  
    } a[MAXN * 2];  
    Info tmp[MAXN];  
    int n, root, size, home[MAXN];  
    void update(int root) {  
        if (a[root].info.use) a[root].l = a[root].r = a[root].info.pos;  
        else {  
            a[root].l = (point) {INF, INF, INF};  
            a[root].r = (point) {-INF, -INF, -INF};  
        }  
        if (a[root].lc) {  
            chkmin(a[root].l, a[a[root].lc].l);  
            chkmax(a[root].r, a[a[root].lc].r);  
        }  
        if (a[root].rc) {  
            chkmin(a[root].l, a[a[root].rc].l);  
            chkmax(a[root].r, a[a[root].rc].r);  
        }  
    }  
    void build(int &root, int l, int r, int Mode) {  
        root = ++size;  
        mode = a[root].mode = Mode;  
        int mid = (l + r) / 2;  
        nth_element(tmp + l, tmp + mid, tmp + r + 1);  
        a[root].info = tmp[mid];  
        home[a[root].info.home] = root;  
        if (l < mid) {  
            build(a[root].lc, l, mid - 1, nxt[Mode]);  
            a[a[root].lc].fa = root;  
        }  
        if (mid < r) {  
            build(a[root].rc, mid + 1, r, nxt[Mode]);  
            a[a[root].rc].fa = root;  
        }  
        update(root);  
    }  
    void init(int x) {  
        n = x;  
        size = root = 0;  
        for (int i = 1; i <= n; i++) {  
            scanf("%lf%lf%lf", &tmp[i].pos.x, &tmp[i].pos.y, &tmp[i].pos.z);  
            tmp[i].use = true; tmp[i].home = i;  
        }  
        build(root, 1, n, 0);  
    }  
    void normalize(int root) {  
        if (root == 0) return;  
        update(root);  
        normalize(a[root].fa);  
    }  
    void insert(int &root, int Mode, Info val) { 
        if (root == 0) {  
            root = ++size;  
            a[root].mode = Mode;  
            a[root].info = val;  
            home[a[root].info.home] = root;  
            update(root);  
            return;  
        }  
        mode = Mode;  
        if (val < a[root].info) {  
            insert(a[root].lc, nxt[Mode], val);  
            a[a[root].lc].fa = root;  
        } else {  
            insert(a[root].rc, nxt[Mode], val);  
            a[a[root].rc].fa = root;  
        }  
        update(root);  
    }  
    void modify(int x, point pos) {  
        a[home[x]].info.use = false;  
        normalize(home[x]);  
        insert(root, 0, (Info) {x, true, pos});  
    }  
    double nearest(int root, point pos) {  
        double x;  
        if (pos.x < a[root].l.x) x = a[root].l.x - pos.x;  
        else if (pos.x > a[root].r.x) x = pos.x - a[root].r.x;  
        else x = 0;  
        double y;  
        if (pos.y < a[root].l.y) y = a[root].l.y - pos.y;  
        else if (pos.y > a[root].r.y) y = pos.y - a[root].r.y;  
        else y = 0;  
        double z;  
        if (pos.z < a[root].l.z) z = a[root].l.z - pos.z;  
        else if (pos.z > a[root].r.z) z = pos.z - a[root].r.z;  
        else z = 0;  
        return sqrt(x * x + y * y + z * z);  
    }  
    double farthest(int root, point pos) {  
        double x;  
        x = max(fabs(a[root].l.x - pos.x), fabs(a[root].r.x - pos.x));  
        double y;  
        y = max(fabs(a[root].l.y - pos.y), fabs(a[root].r.y - pos.y));  
        double z;  
        z = max(fabs(a[root].l.z - pos.z), fabs(a[root].r.z - pos.z));  
        return sqrt(x * x + y * y + z * z);  
    }  
    int query(int root, point pos, double d) {  
        if (root == 0 || nearest(root, pos) > d + eps || farthest(root, pos) < d - eps) return 0;  
        if (a[root].info.use && fabs(dist(a[root].info.pos, pos) - d) <= eps) return a[root].info.home;  
        int tmp = 0;  
        tmp = query(a[root].lc, pos, d);  
        if (tmp) return tmp;  
        tmp = query(a[root].rc, pos, d);  
        return tmp;  
    }  
    int query(point pos, double d) {  
        return query(root, pos, d);  
    }  
} KDT;  
double a, b;  
double f(double x) {  
    return a * x - b * sin(x);  
}  
double decode(double l, double r, double x, double last) {  
    while (r - l >= 1e-9) {  
        double mid = (l + r) / 2;  
        if (f(mid * last + 1) > x) r = mid;  
        else l = mid;  
    }  
    return (l + r) / 2;  
}  
int main() {  
    int n, m;  
    scanf("%d%d", &n, &m);  
    double lastans = 0.1;  
    scanf("%lf%lf", &a, &b);  
    KDT.init(n);  
    for (int i = 1; i <= m; i++) {  
        int opt; read(opt);  
        if (opt == 0) {  
            double t, x, y, z;  
            scanf("%lf%lf%lf%lf", &t, &x, &y, &z);  
            int pos = decode(1, n, t, lastans) + 0.5;  
            x = decode(-100, 100, x, lastans);  
            y = decode(-100, 100, y, lastans);  
            z = decode(-100, 100, z, lastans); 
            KDT.modify(pos, (point) {x, y, z});  
        } else {  
            double x, y, z, t;  
            scanf("%lf%lf%lf%lf", &x, &y, &z, &t);  
            x = decode(-100, 100, x, lastans);  
            y = decode(-100, 100, y, lastans);  
            z = decode(-100, 100, z, lastans);  
            t = decode(0, 400, t, lastans);  
            lastans = KDT.query((point) {x, y, z}, t);  
            printf("%.0lf\n", lastans);  
        }
    }  
    return 0;  
}