#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3e5 + 5;
int n, m;
struct Tree{
    #define ls a[x].son[0]
    #define rs a[x].son[1]
    int son[2], fa, rev;
}a[N];
int st[N], top;
bool isroot(int x){
    return !(a[a[x].fa].son[0] == x || a[a[x].fa].son[1] == x);
}
void pushr(int x){
    swap(ls, rs);
    a[x].rev ^= 1;
}
void pushdown(int x){
    if(a[x].rev){
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        a[x].rev ^= 1;
    }
}
void rotate(int x){
    int y = a[x].fa, z = a[y].fa, k = a[y].son[1] == x;
    if(!isroot(y)) a[z].son[a[z].son[1] == y] = x;
    a[x].fa = z;
    a[y].son[k] = a[x].son[k ^ 1], a[a[x].son[k ^ 1]].fa = y;
    a[x].son[k ^ 1] = y, a[y].fa = x;
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
        splay(x), a[x].son[1] = son;
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
    split(x, y);
    a[y].son[0] = a[x].fa = 0;
}
bool islink(int x, int y){
    return (findroot(x) == findroot(y));
}
int num;
struct que{
    int x, y;
}q[N];
signed main(){
    scanf("%lld%lld", &n, &m);
    for(int i = 1; i < n; ++i){
        int u, v;
        scanf("%lld%lld", &u, &v);
        link(u, v);
    }
    while(m--){
        char opt[2];
        int x, y;
        scanf("%s%lld", opt, &x);
        if(opt[0] == 'Q') {
            scanf("%lld", &y);
            puts(islink(x, y) ? "Yes" : "No");
        }
        if(opt[0] == 'C'){
            scanf("%lld", &y);
            q[++num] = que{x, y};
            cut(x, y);
        }
        if(opt[0] == 'U'){
            int u = q[x].x, v = q[x].y;
            link(u, v);
        }
    }
    return 0;
}