#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include<ctime>
using namespace std;

inline int put(int x)
{
    int y = x & 1, z = x >> 1;
    if (z) putchar('.');
    else putchar('#');
    if (y) putchar('.');
    else putchar('#');
    puts ("");
}

int main(void)
{
    srand(time(0));
    //freopen("dat.txt","w",stdout);
    int n = 30000, m = 80000;

    printf ("%d %d\n", n, m);
    for (int i = 2; i <= n; i++)
        printf ("%d %d\n", rand() % (i - 1) + 1, i);
    for (int i = 1; i <= n; i++)
        put(rand() % 4);
    for (int i = 1; i <= m; i++)
    {
        int x = rand() % (n - 1) + 2, y;
        y = rand() % (x - 1) + 1;
        if ( i < (m / 2) ) swap(x, y);
        /*if ( i < (m / 2) ) printf ("C %d ", x), put(rand() % 4);
        else printf ("Q %d %d\n", x, y);*/
        if ( rand()%32768 > 20000 ) printf ("C %d ", x), put(rand() % 4);
        else printf ("Q %d %d\n", x, y);
    }
    return 0;
}