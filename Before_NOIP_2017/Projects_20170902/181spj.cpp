#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int wi[210], ci[210];

int main (int argc, char *args[])
{
    FILE *fsin = fopen(args[1],"r");
    FILE *fsout = fopen(args[2],"r");
    FILE *fans = fopen(args[3],"r");
    int n, k; fscanf(fsin, "%d", &n);
    for (int i = 0; i < n; i++) fscanf(fsin, "%d", &wi[i]);
    for (int i = 0; i < n; i++) fscanf(fsin, "%d", &ci[i]);
    fscanf(fsin, "%d", &k);
    int stdt, anst;
    fscanf(fsout, "%d", &stdt);
    fscanf(fans, "%d", &anst);
    if (stdt != anst)
    {
    	return 1;
    }
    else
    {
        int tt = 0, ss = 0;
        for (int i = 0; i < n; i++)
        {
            int x; fscanf(fans, "%d", &x);
            if (x < 0 || x > ci[i]) { tt = -1; break; }
            tt += x * wi[i];
            ss += x;
        }
        if (tt != k || ss != anst)
        {
        	return 1;
        } 
        else
        {
            return 0;
        }
    }
    return 1;
}
