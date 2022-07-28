#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, q;
struct Link_Cut_Tree{
	#define ls a[x].son[0]
	#define rs a[x].son[1]
	struct Tree{
		int son[2], fa, siz, rev, siz_v;
	}a[N];
	int top, st[N];
	bool isroot(int x){
		return !(a[a[x].fa].son[0] == x || a[a[x].fa].son[1] == x);
	}
	void update(int x){
		a[x].siz = a[ls].siz + a[rs].siz + 1 + a[x].siz_v;
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
			splay(x), a[x].siz_v += a[a[x].son[1]].siz - a[son].siz, a[x].son[1] = son, update(x);
		}
	}
	void makeroot(int x){
		access(x), splay(x), pushr(x);
	}
	void split(int x, int y){
		makeroot(x), access(y), splay(y);
	}
	void link(int x, int y){
		split(x, y);
		a[x].fa = y, a[y].siz_v += a[x].siz;
		update(y);
	}
	int query(int x, int y){
		split(x, y);
		int res = (a[x].siz_v + 1) * (a[y].siz_v + 1);
		return res;
	} 
}lct;
signed main(){
	scanf("%lld%lld", &n, &q);
	for(int i = 1; i <= n; ++i) lct.a[i].siz = 1;
	while(q--){
		char opt[2];
		int x, y;
		scanf("%s%lld%lld", opt, &x, &y);
		if(opt[0] == 'A') {
			lct.link(x, y);
		}
		if(opt[0] == 'Q'){
			printf("%lld\n", lct.query(x, y));
		}
	}
	return 0;
}
