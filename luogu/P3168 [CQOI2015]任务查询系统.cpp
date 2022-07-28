#include <bits/stdc++.h>
#define int long long
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
};
using namespace fastio;
const int N = 100005;
int n, m, rt[N], cnt, c[N], b[N];
struct CMT{
    int ls, rs, sum, s;
}a[N << 6];
int New(int x){
    a[++cnt] = a[x];
    return cnt;
}
void update(int &x, int pre, int l, int r, int p, int v){
    x = New(pre), a[x].sum += v, a[x].s += b[p] * v;
    if(l == r) return;
    int mid = l + r >> 1;
    if(p <= mid) update(a[x].ls, a[pre].ls, l, mid, p, v);
    else update(a[x].rs, a[pre].rs, mid + 1, r, p, v);
}
int query(int x, int l, int r, int k){
    if(l == r) return a[x].s / a[x].sum * k;
    int mid = l + r >> 1;
    if(k <= a[a[x].ls].sum) return query(a[x].ls, l, mid, k);
    else return a[a[x].ls].s + query(a[x].rs, mid + 1, r, k - a[a[x].ls].sum); 
}
vector<int> vs[N], vt[N];
int pr = 1;
signed main(){
    read(m, n);
    for(int i = 1, s, e; i <= m; ++i){
        read(s, e, c[i]);
        vs[s].push_back(i), vt[e+1].push_back(i);
        b[i] = c[i];
    }
    sort(b + 1, b + 1 + m);
    int len = unique(b + 1, b + 1 + m) - b - 1;
    for(int i = 1; i <= m; ++i) c[i] = lower_bound(b + 1, b + 1 + len, c[i]) - b;
    for(int i = 1; i <= n; ++i){
        rt[i] = rt[i-1];
        for(int j = 0; j < vs[i].size(); ++j){
            update(rt[i], rt[i], 1, len, c[vs[i][j]], 1);
        }
        for(int j = 0; j < vt[i].size(); ++j){
            update(rt[i], rt[i], 1, len, c[vt[i][j]], -1);
        }
    }
    for(int i = 1; i <= n; ++i){
        int x, ta, tb, tc, k;
        read(x, ta, tb, tc), k = 1 + (ta * pr + tb) % tc;
        if(a[rt[x]].sum < k) pr = a[rt[x]].s;
        else pr = query(rt[x], 1, len, k);
        printf("%lld\n", pr);
    }
    return 0;
}