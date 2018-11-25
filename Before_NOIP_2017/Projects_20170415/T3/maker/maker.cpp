#include<bits/stdc++.h>
using namespace std;
const int maxn=2e7,len=1e3;
char in[len],out[len],cmd[len];
int main()
{
    srand(time(NULL));
    unsigned int n;
    for(int i=1;i<=20;i++)
    {
        if(i<=10) while(n<(10*(i-1)))n=rand()*rand()%(10*i);
        else n=rand()*rand()%maxn;
        sprintf(in,"cp%d.in",i);
        sprintf(out,"cp%d.ans",i);
        sprintf(cmd,"std.exe < %s > %s",in,out);
        freopen(in,"w",stdout);
        printf("%u\n",n);
        fclose(stdout);
        system(cmd);
    }
    return 0;
}
