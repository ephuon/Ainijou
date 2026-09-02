//无向图每条边定向后成为DAG,使得s可达所有点可达t
//topo为定向后DAG的拓扑序,u->v：拓扑序中u在v的前面.
int n, dfn[N], low[N], stp, p[N], ord[N], topo[N];
bool fail = 0, sign[N]; vector<int> e[N];
void dfs(int x, int fa, int s, int t){
	dfn[x] = low[x] = ++stp;
	ord[stp] = x, p[x] = fa;
	if (x == s) dfs(t, x, s, t);
	for (int y : e[x]){
		if (x == s && y == t) continue;
		if (!dfn[y]){
			if (x == s) fail = true;
			dfs(y, x, s, t);
			low[x] = min(low[x], low[y]); }
		else if (dfn[y] < dfn[x] && y != fa)
			low[x] = min(low[x], dfn[y]); } }
bool bipolar_orientation(int s, int t){
	e[s].push_back(t), e[t].push_back(s);
	stp = fail = 0, dfs(s, s, s, t);
	for (int i = 1; i <= n; i++)
		if (i != s && (!dfn[i] || low[i] >= dfn[i]))
			fail = true;
	if (fail) return false;
	sign[s] = 0;//memset sign[] is not necessary
	int pre[n + 5], suf[n + 5]; // list
	suf[0] = s; pre[s] = 0, suf[s] = t;
	pre[t] = s, suf[t] = n + 1; pre[n + 1] = t;
	for (int i = 3; i <= n; i++){
		int v = ord[i];
		if (!sign[ord[low[v]]]){ // insert before p[v]
			int P = pre[p[v]];
			pre[v] = P, suf[v] = p[v];
			suf[P] = pre[p[v]] = v; }
		else{ // insert after p[v]
			int S = suf[p[v]];
			pre[v] = p[v], suf[v] = S;
			suf[p[v]] = pre[S] = v; }
		sign[p[v]] = !sign[ord[low[v]]]; }
	for (int x = s, cnt = 0; x != n + 1; x = suf[x])
		topo[++cnt] = x;
	return true; }