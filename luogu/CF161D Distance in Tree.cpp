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
const int N = 50005, K = 505;
int n, k;
int head[N], cnt;
struct edge{
    int v, nxt;
}e[N << 1];
void add(int u, int v){
    e[++cnt] = edge{v, head[u]};
    head[u] = cnt;
}
bool vis[N];
int dis[N], maxn[N], siz[N], rem[N], rt, sum, ans, cntr;
void find(int u, int fa){
    maxn[u] = 0, siz[u] = 1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(!vis[v] && v != fa){
            find(v, u);
            siz[u] += siz[v];
            maxn[u] = max(maxn[u], siz[v]);
        }
    }
    maxn[u] = max(maxn[u], sum - siz[u]);
    if(maxn[u] < maxn[rt]) rt = u;
}
void getdis(int u, int fa){
    rem[++cntr] = dis[u];
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = 1;
        if(!vis[v] && v != fa){
            dis[v] = dis[u] + w;
            getdis(v, u);
        }
    }
}
int calc(int u, int w){
    dis[u] = w, cntr = 0, getdis(u, 0);
    sort(rem + 1, rem + 1 + cntr);
    int l = 1, r = cntr, x = 0, y = 0;
    while(l <= r){
        if(rem[l] + rem[r] <= k) x += r - l, l++;
        else r--;
    }
    l = 1, r = cntr;
    while(l <= r){
        if(rem[l] + rem[r] < k) y += r - l, l++;
        else r--;
    }
    return x - y;
}
void solve(int u){
    vis[u] = 1, ans += calc(u, 0);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = 1;
        if(!vis[v]){
            ans -= calc(v, w);
            sum = siz[v], rt = 0, maxn[rt] = 2e9;
            find(v, u), solve(rt);

        }
    }
}
signed main(){
    read(n, k);
    for(int i = 1, u, v; i < n; ++i) read(u, v), add(u, v), add(v, u);
    maxn[rt] = sum = n;
    find(1, 0), solve(rt);
    write(ans);
    return 0;
}