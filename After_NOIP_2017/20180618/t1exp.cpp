#include<bits/stdc++.h>
using namespace std;
const int maxn=10;

int siz[maxn],way;

inline void judge() {
    int su = 0;
    for(int i=1;i<=8;i++) su += siz[i];
    if( su == 4 ) ++way;
}
inline void dfs(int pos) {
    if( pos > 8 ) return judge();
    int st;
    if( pos % 4 == 1 || pos % 4 == 2 ) st = 0;
    else st = siz[pos-1];
    for(int i=st;i<=7;i++) siz[pos] = i , dfs(pos+1);
}

int main() {
    dfs(1) , cout << way << endl;
    return 0;
}