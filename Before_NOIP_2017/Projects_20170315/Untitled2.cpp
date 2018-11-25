#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn=1000100;

struct node
{
    int lson,rson;
    int data;
    friend bool operator < (const node &a,const node &b) {return a.data<b.data;}
    void swp() {int t=lson;lson=rson;rson=t;}
}
