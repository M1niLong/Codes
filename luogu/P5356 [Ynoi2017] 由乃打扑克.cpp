#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5, M = 500;
int n, m;
int block, num, pos[N], L[M], R[M], add[M], a[N], b[N];
void Add(int l, int r, int val){
    int x = pos[l], y = pos[r];
    if(x == y){
        for(int i = l; i <= r; ++i) a[i] += val;
        for(int i = L[x]; i <= R[x]; ++i) b[i] = a[i];
        sort(b + L[x], b + R[x] + 1);
        return;
    }
    for(int i = l; i <= R[x]; ++i) a[i] += val;
    for(int i = L[y]; i <= r; ++i) a[i] += val;
    for(int i = x + 1; i < y; ++i) add[i] += val;
    for(int i = L[x]; i <= R[x]; ++i) b[i] = a[i];
    for(int i = L[y]; i <= R[y]; ++i) b[i] = a[i];
    sort(b + L[x], b + R[x] + 1);
    sort(b + L[y], b + R[y] + 1);
}
int Minx(int l, int r){
    int x = pos[l], y = pos[r], ans = 2e9;
    if(x == y){
        for(int i = l; i <= r; ++i) ans = min(ans, a[i] + add[x]);
        return ans;
    }
    for(int i = l; i <= R[x]; ++i) ans = min(ans, a[i] + add[x]);
    for(int i = L[y]; i <= r; ++i) ans = min(ans, a[i] + add[y]);
    for(int i = x + 1; i < y; ++i) ans = min(ans, b[L[i]] + add[i]);
    return ans;
}
int Maxn(int l, int r){
    int x = pos[l], y = pos[r], ans = -2e9;
    if(x == y){
        for(int i = l; i <= r; ++i) ans = max(ans, a[i] + add[x]);
        return ans;
    }
    for(int i = l; i <= R[x]; ++i) ans = max(ans, a[i] + add[x]);
    for(int i = L[y]; i <= r; ++i) ans = max(ans, a[i] + add[y]);
    for(int i = x + 1; i < y; ++i) ans = max(ans, b[R[i]] + add[i]);
    return ans;
}
int Qle(int l, int r, int k){
    int x = pos[l], y = pos[r], cnt = 0;
    if(x == y){
        for(int i = l; i <= r; ++i) if(a[i] + add[x] <= k) cnt++;
        return cnt;
    }
    for(int i = l; i <= R[x]; ++i) if(a[i] + add[x] <= k) cnt++;
    for(int i = L[y]; i <= r; ++i) if(a[i] + add[y] <= k) cnt++;
    for(int i = x + 1; i < y; ++i){
        if(b[L[i]] + add[i] > k) continue;
        if(b[R[i]] + add[i] <= k){
            cnt += R[i] - L[i] + 1;
            continue;
        }
        int t = upper_bound(b + L[i], b + R[i] + 1, k - add[i]) - b - L[i];
        cnt += t;
    }
    return cnt;
}
int query(int l, int r, int k){
    int L = Minx(l, r), R = Maxn(l, r);
    L--;
    while(R - L > 1){
        int mid = L + R >> 1;
        if(Qle(l, r, mid) < k) L = mid;
        else R = mid;
    }
    return R;
}
signed main(){
    scanf("%lld%lld", &n, &m);
    block = sqrt(n), num = (n - 1) / block + 1;
    for(int i = 1; i <= n; ++i){
        scanf("%lld", &a[i]), b[i] = a[i];
        pos[i] = (i - 1) / block + 1; 
    }
    for(int i = 1; i <= num; ++i) {
        L[i] = (i - 1) * block + 1, R[i] = i * block;
        if(i == num) R[i] = n;
        sort(b + L[i], b + R[i] + 1);
    }
    while(m--){
        int opt, l, r, k;
        scanf("%lld%lld%lld%lld", &opt, &l, &r, &k);
        if(opt == 1){
            printf("%lld\n", query(l, r, k));//m * log(4e4) * sqrt(1e5) * log(1e5)
        }else{
            Add(l, r, k);
        }
    }
    return 0;
}