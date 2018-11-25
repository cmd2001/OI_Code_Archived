#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define mid ((ll+rr)>>1)
#define debug cout
using namespace std;
const int maxl=1e2+1e2;

struct segmeng_tree
{
    int l[maxn<<2],r[maxn<<2],lson[maxn<<2],rson[maxn<<2];
    int dat[maxn<<2],uni[maxn<<2],cnt;

    void build(int ll,int rr,int pos)
    {
        l[pos]=ll,r[pos]=rr;
        if(ll==rr)
        {
            dat[]

