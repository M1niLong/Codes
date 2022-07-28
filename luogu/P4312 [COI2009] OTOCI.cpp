#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
int n;
struct Link_Cut_Tree{
    struct Tree{
        int son[2], fa, val, sum, rev;
    }a[N];
    int st[N], top;
    bool isroot(int x){
        return !(a[a[x].fa].son[0] == x || a[a[x].fa].son[1] == x);
    }
    void update(int x){
        a[x].sum = a[a[x].son[0]].sum + a[a[x].son[1]].sum + a[x].val;
    }
    void pushr(int x){
        swap(a[x].son[0], a[x].son[1]);
        a[x].rev ^= 1;
    }
    void pushdown(int x){
        if(a[x].rev){
            if(a[x].son[0]) pushr(a[x].son[0]);
            if(a[x].son[1]) pushr(a[x].son[1]);
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
        if(findroot(y) != x) a[x].fa = y;
    }
    int Sum(int x, int y){
        split(x, y);
        return a[y].sum;
    }
}lct;
int q;
signed main(){
    scanf("%lld", &n);
    for(int i = 1; i <= n; ++i) scanf("%lld", &lct.a[i].val);
    scanf("%lld", &q);
    while(q--){
        char opt[20];
        int x, y;
        scanf("%s%lld%lld", opt, &x, &y);
        if(opt[0] == 'b') {
            if(lct.findroot(x) == lct.findroot(y)) puts("no");
            else puts("yes"), lct.link(x, y);
        }
        if(opt[0] == 'p'){
            lct.splay(x);
            lct.a[x].val = y, lct.update(x);
        }
        if(opt[0] == 'e'){
            if(lct.findroot(x) != lct.findroot(y)) puts("impossible");
            else printf("%lld\n", lct.Sum(x, y));
        }
    }
    return 0;
}