#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int, int> pii;
set<pii> connector[50010];

int main (int argc, char *args[])
{
	int ret=0;
    FILE *fsin = fopen(args[1],"r");
    FILE *fstd = fopen(args[2],"r");
    FILE *fusr = fopen(args[3],"r");
    int maxscore;
    int n, std, usr;
    fscanf(fsin, "%d", &n);
    fscanf(fstd, "%d", &std);
    fscanf(fusr, "%d", &usr);
    if (std != usr)
    {
    	return 1;
    }
    else
    {
        bool valid = true;
        for (int i = 0; i < n && valid; i++)
        {
            int x, y; fscanf(fsin, "%d %d", &x, &y);
            int pl; fscanf(fusr, "%d", &pl);
            if (pl < 1 || pl > std)
            {
            	return 1;
            }
            else
            {
                connector[pl - 1].insert(pii(x, y));
            }
        }
        if (valid)
        {
            for (int i = 0; i < std && valid; i++)
            {
                int last = 0;
                for (set<pii>::iterator ite = connector[i].begin(); ite != connector[i].end() && valid; ++ite)
                {
                    if (ite->first <= last)
                    {
                    	return 1;
                    }
                    else
                    {
                        last = ite->second;
                    }
                }
            }
        }
        return 0;
    }
}
