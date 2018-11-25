#include<bits/stdc++.h>
using namespace std;

int a,b,fix=0;
char in[5];

int main()
{
    while(scanf("%s",in)==1)
    {
        if(*in=='j') ++a;
        else ++b;
        if(a==10&&b==10) fix=1;
        if((a==11||b==11)&&!fix) break;
        if(fix&&abs(a-b)==2) break;
    }
    printf("%d:%d\n",b,a);
    if(a>b) puts("jxq");
    else puts("ztz");
    return 0;
}
