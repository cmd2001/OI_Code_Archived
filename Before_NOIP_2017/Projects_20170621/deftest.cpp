#include<bits/stdc++.h>
#define debug cout

#define f1(a,b) (a<b?a:b)
#define f3(a,b) (_a=a,_b=b,_a<_b?_a:_b)

using namespace std;

int _a,_b;

int f2(int a,int b)
{
    return a<b?a:b;
}

int main()
{
    int a,b;
    a=10,b=1;
    debug<<"result of f1    =   "<<f1(a,++b)<<endl;
    a=10,b=1;
    debug<<"result of f2    =   "<<f2(a,++b)<<endl;
    a=10,b=1;
    debug<<"result of f3    =   "<<f3(a,++b)<<endl;
    return 0;
}
