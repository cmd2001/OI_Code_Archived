#include<bits/stdc++.h>
using namespace std;
const double eps=1e-7;
double a,b,c,d;
int main()
{
    cin>>a>>b>>c>>d;
    if(abs(a*b-c*d)<=eps) puts("YES");
    else puts("NO");
    return 0;
}
