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
const int N = 1e5 + 5;
int n, num;
int ecnt, head[N];
struct edge{
    int v, nxt;
}e[N << 1];
void add(int u, int v){
    e[++ecnt] = edge{v, head[u]};
    head[u] = ecnt;
}
int rt[N], siz[N], son[N], f[N][21], lg[N], dep[N];
void dfs1(int u, int fa){
    siz[u] = 1, dep[u] = dep[fa] + 1;
    for(int i = 1; i <= lg[dep[u]]; ++i) f[u][i] = f[f[u][i-1]][i-1];
    int maxson = -1;
    for(int i = head[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > maxson) maxson = siz[v], son[u] = v;
    }
}

signed main(){
    read(n), lg[0] = -1;
    for(int i = 1, r; i <= n; ++i){
        lg[i] = lg[i >> 1] + 1;
        read(r);
        if(!r) rt[++num] = i, f[i][0] = r; 
        else add(i, r), add(r, i), f[i][0] = r;
    }
    for(int i = 1; i <= n; ++i) if(!f[i][0]) dfs1(rt[i], 0);

    return 0;
}