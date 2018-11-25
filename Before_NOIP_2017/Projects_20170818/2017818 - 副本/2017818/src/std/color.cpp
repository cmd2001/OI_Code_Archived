#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int kN = 18;

int f[1 << kN];
bool is_ok[1 << kN];
int N, g[kN];

unsigned power(unsigned d, unsigned k) {
    if (!k) return 1;
    unsigned tmp = power(d, k / 2);
    tmp = tmp * tmp;
    if (k % 2) tmp = tmp * d;
    return tmp;
}

void work() {
    scanf("%d", &N);
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(is_ok, 0, sizeof(is_ok));

    for (int i = 0; i < N; i++) {
        char tmp[20]; scanf("%s", &tmp);
        for (int j = 0; j < N; j++) {
            if (tmp[j] == '1') g[i] |= 1 << j;
        }
    }

    unsigned int ans = 0;

    for (int ss = 1; ss < (1 << N); ss++) {
        bool ok = true;
        for (int i = 0; i < N; i++) if (ss & (1 << i)) {
            if (ss & g[i]) {
                ok = false;
                break;
            }
        }
        is_ok[ss] = ok;
    }

    for (int s = 1; s < (1 << N); s++) {
        int tmp = 10000;
        for (int ss = s; ss > 0; ss = (ss - 1) & s) {
            if (is_ok[ss]) {
                tmp = min(tmp, 1 + f[s ^ ss]);
            }
        }
        f[s] = tmp;
        printf("f[%d] = %d\n", s, tmp);
        ans += (unsigned) tmp * power(233, s);
    }

    printf("%u\n", ans);
}

int main() {
     freopen("color.in", "r", stdin);
     freopen("color.out", "w", stdout);
    int t=1;
    //scanf("%d", &t);
    while (t--) {
        work();
    }
    return 0;
}
