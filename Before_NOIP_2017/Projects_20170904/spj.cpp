#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int n, m, k, c[55]; long long int a[55], b[55];
int r[55]; long long int v[55];

int main (int argc, char *argv[])
{
    FILE *fin  = fopen(argv[1],"r");
    FILE *fstd = fopen(argv[2],"r");
    FILE *fusr = fopen(argv[3],"r");
    int maxscore; sscanf(argv[1], "%d", &maxscore);
    char fg1[256], fg2[256];
    fscanf(fstd, "%s", fg1), fscanf(fusr, "%s", fg2);
    if (strcmp(fg1, fg2))
    {
    	return 1;
    }
    else if (strcmp(fg1, "NO") == 0)
    {
        return 0;
    }
    else
    {
        fscanf(fin, "%d %d %d", &n, &m, &k);
        for (int i = 0; i < m; i++) fscanf(fin, "%lld %lld %d", &a[i], &b[i], &c[i]);
        long long int maxsum = 0, usrsum = 0;
        for (int i = 0; i < n; i++)
        {
            fscanf(fusr, "%d %lld", &r[i], &v[i]);
            int tr; long long int tv; fscanf(fstd, "%d %lld", &tr, &tv);
            maxsum += tv, usrsum += v[i];
        }
        bool valid = true;
        for (int i = 0; i < n && valid; i++)
        {
            if (r[i] < 1 || r[i] > m)
            {
                valid = false;
                return 1;
            }
            --r[i];
        }
        for (int i = 1; i < n && valid; i++)
        {
            if (c[r[i]] <= c[r[i - 1]])
            {
                valid = false;
                return 1;
            }
        }
        for (int i = 0; i < n && valid; i++)
        {
            if (v[i] < a[r[i]] || v[i] > b[r[i]])
            {
                valid = false;
                return 1;
            }
        }
        for (int i = 1; i < n && valid; i++)
        {
            if (v[i] != v[i - 1] + k && v[i] != v[i - 1] * k)
            {
                valid = false;
                return 1;
            }
        }
        if (valid)
        {
            if (usrsum != maxsum)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}
