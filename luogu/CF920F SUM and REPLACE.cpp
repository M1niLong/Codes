#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5, M = 600, A = 3e6 + 5;
int n, m, a[N];
int block, num, pos[N], L[N], R[N], sum[N], mx[N];
int fac[A];
void getfac(){
    for(int i = 1; i <= 1e6; ++i){
        for(int j = i; j <= 1e6; j += i) fac[j]++;
    }
}
void update(int l, int r){
    int x = pos[l];
    for(int i = l; i <= r; ++i){
        if(a[i] > 2) a[i] = fac[a[i]];
    }
    mx[x] = sum[x] = 0;
    for(int i = L[x]; i <= R[x]; ++i) mx[x] = max(mx[x], a[i]), sum[x] += a[i];    
}
void change(int l, int r){
    int x = pos[l], y = pos[r];
    if(x == y){
        update(l, r);
        return;
    }
    update(l, R[x]);
    update(L[y], r);
    for(int i = x + 1; i < y; ++i){
        if(mx[i] > 2) update(L[i], R[i]);
    }
}
int query(int l, int r){
    int x = pos[l], y = pos[r], ans = 0;
    if(x == y){
        for(int i = l; i <= r; ++i) ans += a[i];
        return ans;
    }
    for(int i = l; i <= R[x]; ++i) ans += a[i];
    for(int i = L[y]; i <= r; ++i) ans += a[i];
    for(int i = x + 1; i < y; ++i){
        ans += sum[i];
    }
    return ans;
}
signed main(){
    // freopen("in.in", "r", stdin);
    // freopen("out1.txt", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    block = sqrt(n), num = n / block;
    if(n % block) num++;
    getfac();
    for(int i = 1; i <= num; ++i){
        L[i] = (i - 1) * block + 1, R[i] = i * block;
        if(i == num) R[i] = n;
        for(int j = L[i]; j <= R[i]; ++j){
            pos[j] = i;
            sum[i] += a[j]; 
            mx[i] = max(mx[i], a[j]); 
        }
    }
    while(m--){
        int opt, l, r;
        scanf("%lld%lld%lld", &opt, &l, &r);
        if(opt == 1) change(l, r);
        else printf("%lld\n", query(l, r));
    }
    return 0;
}