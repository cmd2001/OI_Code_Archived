#include<bits/stdc++.h>
using namespace std;
multiset<int> s;
int main()
{
    int n=10;
    for(int i=1;i<=n;i++)
    {
        s.insert(i);s.insert(i);
    }
    for(int i=1;i<=n;i++) s.erase(s.find(i));
    cout<<*s.begin()<<endl;
    cout<<*s.rbegin()<<endl;
    cout<<s.empty()<<endl;
}
