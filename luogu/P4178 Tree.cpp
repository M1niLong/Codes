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
const int N = 4e4 + 5;
int n, k;
int cnt, head[N];
struct edge{
    int v, w, nxt;
}e[N << 1];
void add(int u, int v, int w){
    e[++cnt] = edge{v, w, head[u]};
    head[u] = cnt;
}
bool vis[N];
int ans, rt, maxn[N], siz[N], sum;
void find(int u, int fa){
    siz[u] = 1, maxn[u] = 0;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(!vis[v] && v != fa){
            find(v, u);
            siz[u] += siz[v];
            maxn[u] = max(maxn[u], siz[v]);
        }
    }
    maxn[u] = max(maxn[u], sum - siz[u]);
    if(maxn[u] < maxn[rt]) rt = u;
}
int rem[N], cntr, dis[N];
void getdis(int u, int fa){
    rem[++cntr] = dis[u];
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(!vis[v] && v != fa){
            dis[v] = dis[u] + w;
            getdis(v, u);
        }
    }
}
int calc(int u, int w){
    dis[u] = w, cntr = 0, getdis(u, -1);
    sort(rem + 1, rem + 1 + cntr);
    int l = 1, r = cntr, res = 0;
    while(l <= r){
        if(rem[r] + rem[l] <= k) res += (r - l), l++;
        else r--;
    }
    return res;
}
void solve(int u){
    vis[u] = 1, ans += calc(u, 0);
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v, w = e[i].w;
        if(!vis[v]){
            ans -= calc(v, w);
            sum = siz[v], rt = 0, maxn[rt] = n;
            find(v, u), solve(rt);
        }
    }
}
signed main(){
    read(n);
    for(int i = 1, u, v, w; i < n; ++i) read(u, v, w), add(u, v, w), add(v, u, w);
    read(k);
    sum = maxn[rt] = n, find(1, -1), solve(rt);
    write(ans);
    return 0;
}