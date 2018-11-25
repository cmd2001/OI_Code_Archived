#include<bits/stdc++.h>
using namespace std;
int main()
{
    int cnt=0;
    double s,e;
    while(1)
    {
        system("make.exe");
        printf("Start mine\n");
        s=clock();
        system("my.exe");
        e=clock();
        printf("Time used = %lf s\n",(e-s)/CLOCKS_PER_SEC);
        printf("Start std\n");
        s=clock();
        system("yousiki.exe");
        e=clock();
        printf("Time used = %lf s\n",(e-s)/CLOCKS_PER_SEC);
        system("fc my.out yousiki.out");
        printf("Counter = %d\n",++cnt);
    }
    return 0;
}

