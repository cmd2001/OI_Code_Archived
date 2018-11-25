#include<cstdio>
#include<string> 
#include<map>
const int mod=2014;

std::map<std::string,int> mp;

inline int dfs(const std::string &s) {
    if( mp.find(s) != mp.end() ) return mp[s];
    int ret = 1 , l = s.length();
    for(int i=1;(i<<1)<l;i++) {
        if( s.substr(0,i) == s.substr(l-i,i) ) ret += dfs(s.substr(0,l-i)) + dfs(s.substr(i,l-i));
        if( s.substr(0,i) == s.substr(i,i) ) ret += dfs(s.substr(i,l-i));
        if( s.substr(l-2*i,i) == s.substr(l-i,i) ) ret += dfs(s.substr(0,l-i));
    }
    return mp[s] = ret % mod;
}

int main() {
    char in[mod];
    static std::string ss;
    scanf("%s",in) , ss = in;
    dfs(in);
    printf("%d\n",(mp[ss]-1+mod)%mod);
    return 0;
}