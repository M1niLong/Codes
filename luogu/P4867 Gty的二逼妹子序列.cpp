#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1, M = 1e6 + 1;
int n, m, a[N];
int ans2[M];
int cnt[N], sum[N], typ[N];
int block, num, L[N], R[N], pos[N];
struct que{
	int l, r, id, a, b;
}q[M];
bool cmp(que a, que b){
	if(pos[a.l] == pos[b.l]) return a.r < b.r;
	return pos[a.l] < pos[b.l];
}
void add(int x){
	cnt[a[x]]++;
	sum[pos[a[x]]]++;
	if(cnt[a[x]] == 1) typ[pos[a[x]]]++;
}
void del(int x){
	cnt[a[x]]--;
	sum[pos[a[x]]]--;
	if(cnt[a[x]] == 0) typ[pos[a[x]]]--;
}
void getans(int l, int r, int p){
	if(pos[l] == pos[r]){
		for(int i = l; i <= r; ++i){
			if(cnt[i]) ans2[p]++;
		}
	}else{
		for(int i = l; i <= R[pos[l]]; ++i) if(cnt[i]) ans2[p]++;
		for(int i = L[pos[r]]; i <= r; ++i) if(cnt[i]) ans2[p]++;
		for(int i = pos[l] + 1; i < pos[r]; ++i) ans2[p] += typ[i];
	}
}
signed main(){
	scanf("%d%d", &n, &m);
	block = sqrt(n), num = n / block;
	if(n % block) num++;
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]), pos[i] = (i - 1) / block + 1;
	for(int i = 1; i <= m; ++i) scanf("%d%d%d%d", &q[i].l, &q[i].r, &q[i].a, &q[i].b), q[i].id = i;
	for(int i = 1; i <= num; ++i) L[i] = (i - 1) * block + 1, R[i] = i * block;
	R[num] = n;
	sort(q + 1, q + 1 + m, cmp);
	int l = 1, r = 0;
	for(int i = 1; i <= m; ++i){
		while(r < q[i].r) add(++r);
		while(r > q[i].r) del(r--);
		while(l > q[i].l) add(--l);
		while(l < q[i].l) del(l++);
		getans(q[i].a, q[i].b, q[i].id);
	}
	for(int i = 1; i <= m; ++i) printf("%d\n", ans2[i]);
	return 0;
}