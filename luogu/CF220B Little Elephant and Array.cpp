#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], b[N], block;
struct query{
    int l, r, id;
    bool operator<(const query b)const{
        return (l / block ^ b.l / block) ? l < b.l : ((l / block) & 1 ? r < b.r : r > b.r);
    }
}q[N];
int cnt[N], res, ans[N];
void add(int x){
    if(a[x] > n) return;
    if(cnt[a[x]] == a[x]) res--;
    cnt[a[x]]++;
    if(cnt[a[x]] == a[x]) res++;
}
void del(int x){
    if(a[x] > n) return;
    if(cnt[a[x]] == a[x]) res--;
    cnt[a[x]]--;
    if(cnt[a[x]] == a[x]) res++;
}
signed main(){
    scanf("%lld%lld", &n, &m);
    block = sqrt(n);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= m; ++i) scanf("%lld%lld", &q[i].l, &q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i){
        int ql = q[i].l, qr = q[i].r;
        while(l > ql) add(--l);
        while(l < ql) del(l++);
        while(r < qr) add(++r);
        while(r > qr) del(r--);
        ans[q[i].id] = res;
    }
    
    for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}