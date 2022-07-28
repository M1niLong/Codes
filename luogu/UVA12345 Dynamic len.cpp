#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], block;
int cntq, cntz;
struct Query{
    int l, r, t, id;
    bool operator<(const Query b)const{
       if(l / block != b.l / block) return l < b.l;
       if(r / block != b.r / block) return r < b.r;
       return t < b.t;
    }
}q[N];
struct Change{
    int x, y; 
}cz[N];
int ans[N], cnt[N], res;
void add(int x){
    if(cnt[a[x]] == 0) res++;
    cnt[a[x]]++;
}
void del(int x){
    if(cnt[a[x]] == 1) res--;
    cnt[a[x]]--;
}
void work(int x, int y, int t){
    if(cz[t].x >= x && cz[t].x <= y){
        if(--cnt[a[cz[t].x]] == 0) res--;
        if(++cnt[cz[t].y] == 1) res++;
    }
    swap(a[cz[t].x], cz[t].y);
}
int main(){
    scanf("%d%d", &n, &m);
    block = pow(n, 0.6667);
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    for(int i = 1; i <= m; ++i){
        char ch[2];
        int x, y;
        scanf("%s%d%d", ch, &x, &y);
        if(ch[0] == 'Q'){
            q[++cntq] = Query{++x, y, cntz, cntq};
        }else{
            cz[++cntz] = Change{++x, y};
        }
    }
    sort(q + 1, q + 1 + cntq);
    // for(int i = 1; i <= cntq; ++i) printf("%d %d %d %d\n", q[i].l, q[i].r, q[i].t, q[i].id);
    int l = 1, r = 0, t = 0;
    for(int i = 1; i <= cntq; ++i){
        while(l > q[i].l) add(--l);
        while(r < q[i].r) add(++r);
        while(l < q[i].l) del(l++);
        while(r > q[i].r) del(r--);
        while(t < q[i].t) work(q[i].l, q[i].r, ++t);
        while(t > q[i].t) work(q[i].l, q[i].r, t--);
        ans[q[i].id] = res;
    }
    for(int i = 1; i <= cntq; ++i) printf("%lld\n", ans[i]);
    return 0;
}