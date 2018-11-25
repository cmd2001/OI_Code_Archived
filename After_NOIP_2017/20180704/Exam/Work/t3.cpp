#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#define debug cout
typedef long long int lli;
using namespace std;

const string dat[9][6] = {
{"1","2","3","7","127"},
{"1","3","5","17","13121"},
{"1","4","7","31","2097151"},
{"1","5","9","49","488281249"},
{"1","6","11","71","156728328191"},
{"1","7","13","97","66465861139201"},
{"1","8","15","127","36028797018963967"},
{"1","9","17","161","24315330918113857601"},
{"1","10","19","199","19999999999999999999999"}
};

inline lli string_to_lli(const string &s,lli mod) {
    lli ret = 0;
    for(unsigned i=0;i<s.length();i++) ret = ( ret * 10 + s[i] - '0' ) % mod;
    return ret;
}

int main() {
    static int n,m,l,T;
    while( scanf("%d%d%d",&n,&m,&l) == 3 && ( n || m || l ) ) {
        printf("Case %d: ",T);
        if(!n) puts("1");
        else printf("%lld\n",string_to_lli(dat[l-2][n],m));
    }
    return 0;
}

