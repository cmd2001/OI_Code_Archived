#include<iostream>
#include<ext/rope>
const int maxn=2.5e5+1e2;

char in[maxn];
__gnu_cxx::rope<char> str,ans;

int main() {
    static char com[10];
    static int k,len;
    std::ios::sync_with_stdio(0) , std::cin.tie(0) , std::cout.tie(0);
    std::cin >> in , str = in;
    while( ( std::cin >> com ) && *com != 'E' ) {
        if( *com == 'I' ) {
            std::cin >> in >> k;
            str.insert(k,in);
        } else if( *com == 'P' ) {
            std::cin >> k >> len;
            ans = str.substr(k,len-k+1);
            std::cout << ans << std::endl;
        }
    }
    return 0;
}

