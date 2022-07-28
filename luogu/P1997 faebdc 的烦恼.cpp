#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, a[N], b[N];
int block;
struct query{
    int l, r, id;
    bool operator<(const query b)const{
        return (l / block ^ b.l / block) ? l < b.l : ((l / block) & 1 ? r < b.r : r > b.r);
    }
}q[N];
int res, cnt[N], sum[N], ans[N];
void add(int x){
    sum[cnt[a[x]]]--;
    cnt[a[x]]++;
    sum[cnt[a[x]]]++;
    res = max(res, cnt[a[x]]);
}
void del(int x){
    sum[cnt[a[x]]]--;
    cnt[a[x]]--;
    sum[cnt[a[x]]]++;
    if(sum[res] == 0) res--;
}
int main(){
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + len, a[i]) - b;
    for(int i = 1; i <= m; ++i) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + m);
    int l = 1, r = 0;
    for(int i = 1; i <= m; ++i){
        while(l > q[i].l) add(--l);
        while(r < q[i].r) add(++r);
        while(l < q[i].l) del(l++);
        while(r > q[i].r) del(r--);
        ans[q[i].id] = res;
    }
    for(int i = 1; i <= m; ++i){
        printf("%d\n", ans[i]);
    }
    return 0;
}