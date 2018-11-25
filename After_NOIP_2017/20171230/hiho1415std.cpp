#include<iostream>  
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
const int maxn = 3e5+5;  
int t1[maxn], t2[maxn], c[maxn];  
int ra[maxn], height[maxn];  
int sa[maxn];  
char str[maxn], str1[maxn], str2[maxn];  
  
bool cmp(int *r, int a, int b, int l)  
{  
    return r[a]==r[b]&&r[a+l]==r[b+l];  
}  
  
void da(char str[], int sa[], int ra[], int height[], int n, int m)  
{  
    n++;  
    int i, j, p, *x = t1, *y = t2;  
    for(i = 0; i < m; i++) c[i] = 0;  
    for(i = 0; i < n; i++) c[x[i]=str[i]]++;  
    for(i = 1; i < m; i++) c[i] += c[i-1];  
    for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;  
    for(j = 1; j <= n; j<<=1)  
    {  
        p = 0;  
        for(i = n-j; i < n; i++) y[p++] = i;  
        for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i]-j;  
        for(i = 0; i < m; i++) c[i] = 0;  
        for(i = 0; i < n; i++) c[x[y[i]]]++;  
        for(i = 1; i < m; i++) c[i] += c[i-1];  
        for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];  
        swap(x, y);  
        p = 1; x[sa[0]] = 0;  
        for(i = 1; i < n; i++)  
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1 : p++;  
        if(p >= n) break;  
        m = p;  
    }  
    int k = 0;  
    n--;  
    for(i = 0; i <= n; i++) ra[sa[i]] = i;  
    for(i = 0; i < n; i++)  
    {  
        if(k) k--;  
        j = sa[ra[i]-1];  
        while(str[i+k]==str[j+k]) k++;  
        height[ra[i]] = k;  
    }  
}  
  
int solve(int n, int len)  
{  
    int ans = 0;  
    for(int i = 2; i <= n; i++)  
    {  
        if(sa[i-1] < len && sa[i] > len || sa[i] < len && sa[i-1] > len)  
            ans = max(ans, height[i]);  
    }  
    return ans;  
}  
  
int main(void)  
{  
    
    freopen("dat.txt","r",stdin);
    while(~scanf(" %s %s", str1, str2))  
    {  
        int len1 = strlen(str1);  
        int len2 = strlen(str2);  
        for(int i = 0; i < len1; i++)  
            str[i] = str1[i];  
        str[len1] = '#';  
        for(int i = 0; i < len2; i++)  
            str[len1+i+1] = str2[i];  
        int len = len1+len2+1;  
        str[len] = 0;  
        da(str, sa, ra, height, len, 127);  
        int ans = solve(len, len1);  
        printf("%d\n", ans);  
    }  
    return 0;  
}  