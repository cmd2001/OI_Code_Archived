#include<bits/stdc++.h>
#define debug cout
using namespace std;

inline int getsum(int x,int l) {
    int ret = 0;
    while(x) ret += x % l , x /= l;
    return ret;
}
inline int getk(int x,int l) {
    int ret = 1;
    while(x >= l) {
        ++ret , x = getsum(x,l);
    }
    return ret;
}
inline int calc(int l,int k) {
    for(int i=1;i<=1e7;i++) if( getk(i,l) >= k ) return i;
}

inline void print(__int128 x) {
    int stk[101],top;
    for(top=0;x;x/=10) stk[++top] = x % 10;
    putchar('\"');
    for(int i=top;i;i--) putchar('0'+stk[i]);
    putchar('\"');
}


int main() {
    cout << sizeof(__int128) << endl;
    for(int l=2;l<=10;l++) {
        for(int k=1;k<=4;k++) putchar('\"') , printf("%d",calc(l,k)) , putchar('\"') , putchar(',');
        __int128 t = 2;
        for(int i=1;i<=2*l+2;i++) t *= l;
        --t;
        print(t);
        puts("");
    }
    return 0;
}

/*
16
1 1 2 3 7 127
1 1 3 5 17 13121
1 1 4 7 31 2097151
1 1 5 9 49 488281249
1 1 6 11 71 156728328191
1 1 7 13 97 66465861139201
1 1 8 15 127 36028797018963967
1 1 9 17 161 24315330918113857601
1 1 10 19 199 19999999999999999999999

string[][6] {
{"1","1","2","3","7","127"}
{"1","1","3","5","17","13121"}
{"1","1","4","7","31","2097151"}
{"1","1","5","9","49","488281249"}
{"1","1","6","11","71","156728328191"}
{"1","1","7","13","97","66465861139201"}
{"1","1","8","15","127","36028797018963967"}
{"1","1","9","17","161","24315330918113857601"}
{"1","1","10","19","199","19999999999999999999999"}
}
*/
