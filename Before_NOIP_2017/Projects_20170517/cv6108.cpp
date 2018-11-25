#include<bits/stdc++.h>
using namespace std;
int main()
{
    char ch,nxt=getchar();
    bool del=0;
    while(nxt!=EOF)
    {
        ch=nxt;
        nxt=getchar();
        if(ch=='0'&&!del) del=1;
        else if(nxt!=EOF||del) putchar(ch);
    }
    return 0;
}

