namespace Leftist{
	int a[MAXN], ls[MAXN], rs[MAXN], dis[MAXN], fa[MAXN]; 
	bool vis[MAXN]; // dis[0] = -1;
	void init() {for(int i=1;i<=n;i++) fa[i] = i;}
	int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
	int _merge(int x, int y){
		if(!x || !y) return x + y;
		if(a[y] < a[x]) swap(x, y);
		rs[x] = _merge(rs[x], y);
		if(dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);
		dis[x] = dis[rs[x]] + 1;
		return x;
	}
	void merge(int x, int y){
		if(vis[x] ||vis[y]) return;
		x = find(x), y = find(y);
		if(x != y) fa[x] = fa[y] = _merge(x, y);
	}
	int del(int x){
		if(vis[x]) return -1; // deleted flag
		x = find(x); vis[x] = true;
		int ret = a[x].val;
		fa[ls[x]] = fa[rs[x]] = fa[x] = _merge(ls[x], rs[x]);
		ls[x] = rs[x] = dis[x] = 0;
		return ret;
	}
}