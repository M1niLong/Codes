#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5000005;
int n, m;
struct Link_Cut_Tree{
	struct Tree{
		int son[2], fa, val, sum, rev, siz;
		bool cz;
	}a[N];
	#define ls a[x].son[0]
	#define rs a[x].son[1]
	int top, st[N];
	bool isroot(int x){
		return !(a[a[x].fa].son[0] == x || a[a[x].fa].son[1] == x);
	}
	void update(int x){
		a[x].sum = a[x].val + a[ls].sum + a[rs].sum;
		a[x].siz = a[ls].siz + a[rs].siz + 1;
	}
	void pushr(int x){
		swap(ls, rs);
		a[x].rev ^= 1;
	}
	void pushcz(int x){
		a[x].sum = a[x].val = 0;
		a[x].cz = 1;
	}
	void pushdown(int x){
		if(a[x].rev){
			if(ls) pushr(ls);
			if(rs) pushr(rs);
			a[x].rev = 0;
		}
		if(a[x].cz){
			if(ls) pushcz(ls);
			if(rs) pushcz(rs);
			a[x].cz = 0;
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
	int query(int x, int y){
		split(x, y);
		int res = a[y].sum;
		pushcz(y);
		return res;
	}
}lct;
int ans;
inline const void decode(int &x){
	x ^= ans % n;
	if(x > n) x %= n;
	if(!x) x = 1;
}
int stk[N], tp, point; 
void dfs(int x, int fa){
	if(!x) return;
	lct.a[x].fa = fa;
	lct.pushdown(x);
	dfs(lct.a[x].son[0], fa);
	dfs(lct.a[x].son[1], fa);
	lct.a[x].son[0] = lct.a[x].son[1] = 0;
	lct.update(x);
}
signed main(){
	scanf("%lld%lld", &n, &m);
	point = n;
	while(m--){
		int opt, x, y;
		scanf("%lld%lld%lld", &opt, &x, &y);
		decode(x), decode(y);
		// cout << x << ' ' << y << endl;
		if(opt == 1){
			if(x == y) continue;
			if(lct.findroot(x) == lct.findroot(y)) {
				lct.split(x, y);
				++point;
				dfs(y, point);
				continue;
			}
			lct.link(x, y);
		}
		if(opt == 2){
			lct.splay(x);
			lct.a[x].val += y, lct.update(x);
		}
		if(opt == 3){
			if(lct.findroot(x) != lct.findroot(y)) ans = 0;
			else ans = lct.query(x, y);
			printf("%lld\n", ans);
		}
	}
	// system("pause");
	return 0;
}
