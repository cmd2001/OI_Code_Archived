#include<bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    unsigned int n=rand()*rand()%200000,m=rand()*rand()%200000;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=n;i++) cout<<rand()%1000<<endl;
    for(int i=1;i<=m;i++) cout<<rand()%1000<<endl;
    return 0;
}
