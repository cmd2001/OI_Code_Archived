//Cv6108_By_Cmd2001
#include<bits/stdc++.h>
using namespace std;
int main()
{
    char ch,nxt=getchar();
    bool del=0;
    while(nxt=='0'||nxt=='1')
    {
        ch=nxt;
        nxt=getchar();
        if(ch=='0'&&!del) del=1;
        else if((nxt=='0'||nxt=='1')||del) putchar(ch);
    }
    return 0;
}
