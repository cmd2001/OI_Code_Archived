#include<iostream>
#include<algorithm>
const int maxn=1e4+1e2;

std::string in[maxn];
int n;

int main() {
    std::cin >> n;
    for(int i=1;i<=n;i++) std::cin >> in[i];
    std::reverse(in+1,in+1+n);
    for(int i=1;i<=n;i++) std::cout << in[i] << ( i != n ? ' ' : '\n' );
    return 0;
}

