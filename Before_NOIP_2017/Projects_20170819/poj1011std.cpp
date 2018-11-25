#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int Max = 65;
 
int n, len, stick[Max];
bool flag, vis[Max];
 
bool cmp(int a, int b){
    return a > b;
}
 
void dfs(int dep, int now_len, int u){   // dep???????????,u??????????
    if(flag) return;
    if(now_len == 0){                    //  ?????0,????????????
        int k = 0;
        while(vis[k]) k ++;              //  ????????????
        vis[k] = true;
        dfs(dep + 1, stick[k], k + 1);
        vis[k] = false;
        return;
    }
    if(now_len == len){                  //  ?????len,???????????
        if(dep == n) flag = true;        //  ?????:???n?????????
        else dfs(dep, 0, 0);
        return;
    }
    for(int i = u; i < n; i ++)
        if(!vis[i] && now_len + stick[i] <= len){
            if(!vis[i-1] && stick[i] == stick[i-1]) continue;      //  ?????:???????
            vis[i] = true;
            dfs(dep + 1, now_len + stick[i], i + 1);
            vis[i] = false;
        }
}
 
int main(){
    while(scanf("%d", &n) && n != 0){
        int sum = 0;
        flag = false;
        for(int i = 0; i < n; i ++){
            scanf("%d", &stick[i]);
            sum += stick[i];
        }
        sort(stick, stick + n, cmp);     //  ???????
        for(len = stick[0]; len < sum; len ++)
            if(sum % len == 0){          //  ????sum??????
                memset(vis, 0, sizeof(vis));
                dfs(0, 0, 0);
                if(flag) break;
            }
        printf("%d\n", len);
    }
    return 0;
}
