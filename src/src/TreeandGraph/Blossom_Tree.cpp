int mch[MAXN], pre[MAXN], fa[MAXN], col[MAXN];
int hscnt = 0, hs[MAXN]; queue<int> q;
int find(int x) {return fa[x]==x ? x : fa[x]=find(fa[x]);}
int lca(int x, int y) {
	for(++hscnt; x; y ? swap(x, y) : (void)0) {
		x = find(x);
		if(hs[x] == hscnt) return x;
		hs[x] = hscnt, x = pre[mch[x]]; } }
void blossom(int x, int y, int rt) {
	for(int z; find(x) != rt; y = z, x = pre[y]) {
		pre[x] = y, z = mch[x];
		if(col[z] == 1) q.push(z), col[z] = 0;
		if(find(x) == x) fa[x] = rt;
		if(find(z) == z) fa[z] = rt; } }
bool bfs(int st) {
	while(!q.empty()) q.pop();
	q.push(st), col[st] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(auto v : e[x]) {
			if(col[v] == -1) {
				pre[v] = x, col[v] = 1;
				if(!mch[v]) {
					for(int y; v; swap(mch[y], v)) 
						mch[v] = y = pre[v];
					return true; }
				q.push(mch[v]); col[mch[v]] = 0;
			}else if(col[v] == 0 && find(x) != find(v)) {
				int f = lca(x, v); blossom(x, v, f); 
				blossom(v, x, f);} } }
	return false;}
int solve() {
	int ans = 0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) col[j] = -1, fa[j] = j;
		if(!mch[i] && bfs(i)) ans++;}
	return ans;}