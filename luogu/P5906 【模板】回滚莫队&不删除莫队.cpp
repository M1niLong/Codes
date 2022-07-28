#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -1;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t), read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
}
using namespace fastio;
const int N = 1e6 + 5;
int n, m, num, pos[N], block, R[N], L[N], a[N], b[N], ans[N];
struct query{
    int l, r, id;
    bool operator<(const query b)const{
        return (pos[l] == pos[b.l]) ? r < b.r : pos[l] < pos[b.l];
    }
}q[N];
int st[N], td[N], td2[N];
void work(){
    int last = 0, l = 0, r = 0, ans1 = 0;
    for(int i = 1; i <= m; ++i){
        if(pos[q[i].l] == pos[q[i].r]){
            ans1 = 0;
            for(int j = q[i].l; j <= q[i].r; ++j) st[a[j]] = 0;
            for(int j = q[i].l; j <= q[i].r; ++j){
                if(!st[a[j]]) st[a[j]] = j;
                ans1 = max(ans1, j - st[a[j]]);
            }
            for(int j = q[i].l; j <= q[i].r; ++j) st[a[j]] = 0;
            ans[q[i].id] = ans1;
            continue;
        }
        int now = pos[q[i].l];
        if(last != now){
            ans1 = 0;
            for(int j = l; j <= r; ++j) st[a[j]] = td[a[j]] = 0;
            l = R[now];
            r = l - 1;
            last = now;
        }
        while(r < q[i].r){
            r++;
            if(!st[a[r]]) st[a[r]] = r;
            td[a[r]] = r;
            ans1 = max(ans1, r - st[a[r]]);
        }
        int p = l, ans2 = 0;
        while(q[i].l < p){
            p--;
            if(!td2[a[p]]) td2[a[p]] = p;
            ans2 = max(ans2, max(td[a[p]], td2[a[p]]) - p);
        }
        while(p < l){
            td2[a[p]] = 0;
            p++;
        }
        ans[q[i].id] = max(ans2, ans1);
    }
}

signed main(){
    scanf("%lld", &n), block = sqrt(n), num = (n - 1) / block + 1;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]), b[i] = a[i], pos[i] = (i - 1) / block + 1;
    for(int i = 1; i <= num; ++i) R[i] = min(n, i * block);
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + len, a[i]) - b;
    read(m);
    for(int i = 1; i <= m; ++i) scanf("%lld%lld", &q[i].l, &q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + m);
    work();
    for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}