// 强联通分量
void tar(int x) {
	dfn[x] = low[x] = ++tot;
	S[++top] = x, vis[x] = 1;
	for(auto v : e[x]) {
		if(!dfn[v]) tar(v), low[x] = min(low[x], low[v]);
		else if(vis[v]) low[x] = min(low[x], dfn[v]);}
	if(dfn[x] == low[x]) {
		++bcnt;
		while(S[top] != x) {
			int v = S[top--];
			vis[v] = 0;
			bel[v] = bcnt;}
		top--, vis[x] = 0, bel[x] = bcnt;}}
/*边双*/
// 注意！建立边双树或者圆方树后【边表大小】是否开够
// 求边双：无视掉 bri 后搜出每个连通块，记得多测
int dfn[N], low[N], dfscnt; // clear dfn low bri dfscnt
bool bri[M << 1]; // 注意此处是边数
void tarjan(int x, int last) { // last 是边
	dfn[x] = low[x] = ++dfscnt;
	for (int i = head[x]; i; i = e[i].next) {
		int v = e[i].to;
		if (!dfn[v]) {
			tarjan(v, i);
			low[x] = min(low[x], low[v]);
			if (low[v] > dfn[x]) bri[i] = bri[i ^ 1] = 1;
		} else if (dfn[v] < dfn[x] && ((i ^ 1) != last))
			low[x] = min(low[x], dfn[v]); } }
/** 建立圆方树+求割点 **/
int is_cut[N], dfn[N], low[N], dfscnt, pcnt;
int stk[N], dep; // clear dfn low is_cut dfscnt, let pcnt=n
void tarjan(int x, int fa) {
	int child = 0;
	dfn[x] = low[x] = ++dfscnt; stk[++dep] = x;
	for (auto v : e[x]) {
		if (!dfn[v]) {
			++child; tarjan(v, x);
			low[x] = min(low[x], low[v]);
			if (low[v] >= dfn[x]) {
				is_cut[x] = true;
				++pcnt; // square node index
				int j = 0, sz = 1;
				do {
					j = stk[dep--];
					addedge(pcnt, j);
					++sz;
				} while (j != v);
				addedge(pcnt, x); }
		} else if low[x] = min(low[x], dfn[v]); }
	if (!fa && child == 1) is_cut[x] = false; }