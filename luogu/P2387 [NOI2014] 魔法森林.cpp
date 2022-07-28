#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, m;
struct Tree{
    int son[2], fa, val, maxn, rev;
    #define ls a[x].son[0]
    #define rs a[x].son[1]
}a[N << 1];
int top, st[N];
bool isroot(int x){
    return !(a[a[x].fa].son[0] == x || a[a[x].fa].son[1] == x);
}
void update(int x){
    a[x].maxn = x;
    if(a[a[ls].maxn].val > a[a[x].maxn].val) a[x].maxn = a[ls].maxn;
    if(a[a[rs].maxn].val > a[a[x].maxn].val) a[x].maxn = a[rs].maxn;
}
void pushr(int x){
    swap(ls, rs);
    a[x].rev ^= 1;
}
void pushdown(int x){
    if(a[x].rev){
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        a[x].rev = 0;
    }
}
void rotate(int x){
    int y = a[x].fa, z = a[y].fa, k = a[y].son[1] == x;
    if(!isroot(y)) a[z].son[a[z].son[1] == y] = x;
    a[x].fa = z;
    a[y].son[k] = a[x].son[k ^ 1], a[a[x].son[k ^ 1]].fa = y;
    a[x].son[k ^ 1] = y, a[y].fa = x;
    update(y), update(x);
}
void splay(int x){
    int t = x;
    st[++top] = t;
    while(!isroot(t)) st[++top] = t = a[t].fa;
    while(top) pushdown(st[top--]);
    while(!isroot(x)){
        int y = a[x].fa, z = a[y].fa;
        if(!isroot(y)) rotate((a[z].son[1] == y) ^ (a[y].son[1] == x) ? x : y);
        rotate(x);
    }
}
void access(int x){
    for(int son = 0; x; x = a[son = x].fa){
        splay(x), a[x].son[1] = son, update(x);
    }
}
void makeroot(int x){
    access(x), splay(x), pushr(x);
}
int findroot(int x){
    access(x), splay(x);
    pushdown(x);
    while(a[x].son[0]) x = a[x].son[0], pushdown(x);
    splay(x);
    return x;
}
void split(int x, int y){
    makeroot(x), access(y), splay(y);
}
void link(int x, int y){
    makeroot(x);
    a[x].fa = y;
}
void cut(int x, int y){
    makeroot(x);
    if(findroot(y) == x && a[y].fa == x && !a[y].son[0]) {
        a[x].son[1] = a[y].fa = 0;
        update(x);        
    }
}
bool islink(int x, int y){
    return (findroot(x) == findroot(y));
}
struct edge{
    int x, y, a, b;
    bool operator<(const edge b)const{
        return a < b.a;
    }
}e[N];
int ans = 2e9;
signed main(){
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i <= m; ++i) scanf("%lld%lld%lld%lld", &e[i].x, &e[i].y, &e[i].a, &e[i].b);
    sort(e + 1, e + 1 + m);
    for(int i = 1; i <= m; ++i){
        int x = e[i].x, y = e[i].y;
        if(x == y) continue;
        if(islink(x, y)){
            split(x, y);
            int z = a[y].maxn;
            if(a[z].val > e[i].b) cut(e[z - n].x, z), cut(z, e[z - n].y);
            else continue;
        }
        a[i + n].val = e[i].b, a[i + n].maxn = i + n;
        link(x, i + n), link(i + n, y);
        if(islink(1, n)) {
            split(1, n);
            ans = min(ans, a[a[n].maxn].val + e[i].a);
        }
    }
    printf("%lld\n", ans == 2e9 ? -1 : ans);
    return 0;
}