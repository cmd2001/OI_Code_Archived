#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=4e3+1e2;

char in[maxn>>1];
int n,cnt,ans;

struct Node {
    Node *fa,*ch[26];
    int len,f[110];
}ns[maxn],*last,*root;

inline Node* NewNode(int ll) {
    ns[++cnt].len = ll;
    return ns+cnt;
}

inline void extend(int x) {
    Node* p = last;
}