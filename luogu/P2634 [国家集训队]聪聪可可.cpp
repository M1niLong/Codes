#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 20005;
int n, sum, rt, ans, dis[N], siz[N], maxn[N], vis[N], rem[N], cnt, head[N];
void write(int t){
    if(t < 0){
        putchar('-');
        t = -t;
    }
    if(t >= 10) write(t / 10);
    putchar(t % 10 + '0');
}
struct edge{
    int v, w, nxt;
}e[N << 1];
void add(int u, int v, int w){
    e[++cnt] = edge{v, w, head[u]};
    head[u] = cnt;
}
void find(int u, int fa){
    siz[u] = 1, maxn[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt){
        if(e[i].v == fa || vis[e[i].v]) continue;
        find(e[i].v, u);
        siz[u] += siz[e[i].v];
        maxn[u] = max(maxn[u], siz[e[i].v]);
    }
    maxn[u] = max(maxn[u], sum - siz[u]);
    if (maxn[u] < maxn[rt]) rt = u;
}
void getdis(int u, int fa){
    rem[dis[u] % 3]++;
    for(int i = head[u]; i; i = e[i].nxt){
        if (e[i].v == fa || vis[e[i].v]) continue;
        dis[e[i].v] = dis[u] + e[i].w;
        getdis(e[i].v, u);
    }
}
int calc(int u, int w){
    dis[u] = w, rem[0] = rem[1] = rem[2] = 0;
    getdis(u, 0);
    return (rem[0] * rem[0] + rem[1] * rem[2] * 2);
}
void solve(int u){
    ans += calc(u, 0);
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt){
        if (vis[e[i].v]) continue;
        ans -= calc(e[i].v, e[i].w);
        sum = siz[e[i].v], maxn[rt = 0] = n;
        find(e[i].v, u);
        solve(rt);
    }
}
signed main(){
    scanf("%lld", &n);
    for (int i = 1, u, v, w; i < n; ++i){
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w), add(v, u, w);
    }
    sum = maxn[rt] = n;
    find(1, 0);
    solve(rt);
    int tmp = __gcd(ans, n * n);
    write(ans / tmp);
    putchar('/');
    write(n * n / tmp);
    return 0;
}