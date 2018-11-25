#include<bits/stdc++.h>
using namespace std;
int main()
{
    unsigned long long int a=1,b=0;
    for(int i=1;i<=1000000000;i++) b+=a,a*=2;
    cout<<b<<endl;
    return 0;
}
