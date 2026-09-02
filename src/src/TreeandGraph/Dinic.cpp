bool bfs() { // 约定s=n+1, t=s+1
	for(int i=1;i<=t;i++) dep[i] = 0, cur[i] = head[i];
	queue<int> q; q.push(s); dep[s] = 1;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int i=head[x];i;i=e[i].next) {
			int v = e[i].to;
			if(dep[v] || !e[i].w) continue;
			dep[v] = dep[x] + 1; q.push(v);}}
	return dep[t];}
int dfs(int x, int in) {
	if(x == t) return in;
	int out = 0;
	for(int &i=cur[x];i;i=e[i].next) {
		int v = e[i].to;
		if(dep[v] != dep[x] + 1 || !e[i].w) continue;
		int res = dfs(v, min(in, e[i].w));
		in -= res, out += res;
		e[i].w -= res, e[i^1].w += res;
		if(!in) break;}
	if(!out) dep[x] = 0;
	return out;}
