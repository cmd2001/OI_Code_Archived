#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>
#define debug cout
using namespace std;
const int MAXN = 100000;
const int MAXT = 20000;
bool notprime[MAXN+10];
int prime[MAXN+10], mu[MAXN+10], sum[MAXN+10], Max;
struct Fs{int val, fval;}F[MAXN+10];
bool cmpv(Fs a, Fs b){return a.val < b.val;}
void Init(){
    mu[1] = 1;
    int tmp;
    for(int i=2;i<=Max;i++){
        if(!notprime[i]){
            mu[i] = -1;
            prime[++prime[0]] = i;
        }
        for(int j=1;j<=prime[0]&&(tmp=prime[j]*i)<=Max;j++){
            notprime[tmp] = true;
            if(i%prime[j] == 0){
                mu[tmp] = 0;
                break;
            }
            mu[tmp] = -mu[i];
        }
    }
    for(int i=1;i<=Max;i++){
        F[i].fval = i;
        for(int j=i;j<=Max;j+=i)
            F[j].val += i;
    }
}
int lowbit(int u){return (u&(-u));}
void add(int p, int v){
    while(p<=Max){
        sum[p] += v;
        p+=lowbit(p);
    }
}
int query(int p){
    int ret = 0;
    while(p > 0){
        ret += sum[p];
        p -= lowbit(p);
    }
    return ret;
}
void solve(int n, int m, int &ans){
    ans = 0;
    for(int i=1;i<=n;i++){
        int last = min((n/(n/i)), (m/(m/i)));
        ans += (n/i) * (m/i) * (query(last) - query(i-1));
        ans &= INT_MAX;
        i = last;
    }
}
struct Task{int n, m, a, ans, id;}Ts[MAXT+10];
bool cmpt(Task a, Task b){return a.a < b.a;}
bool cmpid(Task a, Task b){return a.id < b.id;}
int main(){
    int T;
    scanf("%d", &T);
    for(int i=1;i<=T;i++){
        scanf("%d%d%d", &Ts[i].n, &Ts[i].m, &Ts[i].a);
        if(Ts[i].n > Ts[i].m) swap(Ts[i].n, Ts[i].m);
        Max = max(Max, Ts[i].n);
        Ts[i].id = i;
    }
    Init();
    sort(F+1, F+1+Max, cmpv);
    sort(Ts+1, Ts+1+T, cmpt);
    int pos = 0;
    for(int i=1;i<=T;i++){
        while(F[pos+1].val <= Ts[i].a && pos+1 <= Max){
            pos++;
            for(int j=F[pos].fval;j<=Max;j+=F[pos].fval)
                add(j, F[pos].val * mu[j/F[pos].fval]);
        }
        //debug<<"i = "<<i<<"pos = "<<pos<<endl;
        solve(Ts[i].n, Ts[i].m, Ts[i].ans);
    }
    sort(Ts+1, Ts+1+T, cmpid);
    for(int i=1;i<=T;i++)
        printf("%d\n", Ts[i].ans);

    return 0;
}
