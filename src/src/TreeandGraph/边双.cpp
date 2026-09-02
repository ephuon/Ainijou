int dfn[MAXN], low[MAXN], bel[MAXN], num[MAXN], cnt, tot;
int S[MAXN], top;
void tar(int x, int fa) {
	dfn[x] = low[x] = ++tot;
	S[++top] = x;
	for(auto v : e[x]) {
		if(!dfn[v]) tar(v, x), low[x] = min(low[x], low[v]);
		else if(v != fa) {
			low[x] = min(low[x], dfn[v]);
			if(low[v] > dfn[x]) // 该边是割边
		}
	}
	if(low[x] == dfn[x]) {
		cnt++;
		while(S[top] != x) bel[S[top--]] = cnt, num[cnt]++;
		top--; num[cnt]++; bel[x] = cnt;
	}
}