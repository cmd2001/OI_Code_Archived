#include<iostream>
#include<cmath>
using namespace std;
const int Max = 105;
const double eps = 1e-8;

struct Point{
    double x, y;
}s[Max], e[Max];
int n;

double mult(Point sp, Point ep, Point op){
    return (sp.x-op.x)*(ep.y-op.y) - (ep.x-op.x)*(sp.y-op.y);
}

bool fun(Point p1, Point p2){
    if(abs(p1.x-p2.x) < eps && abs(p1.y-p2.y) < eps)
        return false;
    for(int i = 0; i < n; i ++)
        if(mult(p1, p2, s[i])*mult(p1, p2, e[i]) > eps) return false;
    return true;
}

int main(){
    int t, i, j;
    cin >> t;
    while(t --){
        cin >> n;
        for(i = 0; i < n; i ++)
            cin >> s[i].x >> s[i].y >> e[i].x >> e[i].y;
        bool flag = false;
        if(n < 3) flag = true;
        for(i = 0; i < n && !flag; i ++)
            for(j = i + 1; j < n && !flag; j ++){    //  枚举线段的端点。
                if(fun(s[i], s[j])) flag = true;
                else if(fun(s[i], e[j])) flag = true;
                else if(fun(e[i], s[j])) flag = true;
                else if(fun(e[i], e[j])) flag = true;
            }
           if(flag) cout << "Yes!" << endl;
           else cout << "No!" << endl;
    }
    return 0;
}
