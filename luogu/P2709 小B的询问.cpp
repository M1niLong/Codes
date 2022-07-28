#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e4 + 5;
int n, m, k, a[N], block;
struct Query{
    int l, r, num;
    bool operator<(const Query b)const{
        return (l / block ^ b.l / block) ? l < b.l : ((l / block) & 1 ? r < b.r : r > b.r) ;
    }
}q[N];
int cnt[N], res, ans[N];
void add(int x){
    res -= cnt[a[x]] * cnt[a[x]];
    cnt[a[x]]++;
    res += cnt[a[x]] * cnt[a[x]];
}
void del(int x){
    res -= cnt[a[x]] * cnt[a[x]];
    cnt[a[x]]--;
    res += cnt[a[x]] * cnt[a[x]];   
}
signed main(){
    scanf("%lld%lld%lld", &n, &m, &k);
    block = sqrt(n);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= m; ++i) scanf("%lld%lld", &q[i].l, &q[i].r), q[i].num = i;
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i){
        int ql = q[i].l, qr = q[i].r;
        while(l > ql) add(--l);
        while(l < ql) del(l++);
        while(r < qr) add(++r);
        while(r > qr) del(r--);
        ans[q[i].num] = res;
    }
    for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}