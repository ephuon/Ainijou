void dij() { // reversed: from t to s
	for (int i = 1; i <= t; i++) dis[i] = inf;
	for (int i = 1; i <= t; i++) vis[i] = 0;
	dis[t] = 0;
	priority_queue<Node> q; q.push({t, 0});
	while(!q.empty()){
		auto [x, t] = q.top(); q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(int i=head[x];i;i=e[i].next){
			int v = e[i].to;
			if(vis[v] || !e[i^1].w) continue;
			ll cost = -e[i].cost + h[x] - h[v];
			if(dis[v] > dis[x] + cost) {
				dis[v] = dis[x] + cost;
				q.push({v, dis[v]});
} } } }
bool bfs(){
	for(int i=1;i<=t;i++) dep[i] = 0, cur[i] = head[i];
	queue<int> q; q.push(s); dep[s] = 1;
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i=head[x];i;i=e[i].next){
			int v = e[i].to;
			ll cost = e[i].cost + h[v] - h[x];
			if(dep[v] || !e[i].w || dis[v] != dis[x] - cost) continue;
			dep[v] = dep[x] + 1;
			q.push(v);
	} } return dep[t]; }
ll dfs(int x, ll in){
	if(x == t) return in;
	ll out = 0;
	for(int &i=cur[x];i;i=e[i].next){
		int v = e[i].to;
		ll cost = e[i].cost + h[v] - h[x];
		if(dep[v] != dep[x] + 1 ||
		   dis[v] != dis[x] - cost || !e[i].w) continue;
		ll res = dfs(v, min(in, e[i].w));
		in -= res, out += res;
		e[i].w -= res, e[i^1].w += res;
		if(!in) break; }
	if(!out) dep[x] = 0;
	return out; }
pair<ll, ll> solve(){ // first_sssp: DAG最短路或SPFA
	ll flow = 0, cost = 0;
	for (first_sssp(); dis[s] != inf; dij()) {
		while (bfs()) {
			ll tmp = dfs(s, inf);
			flow += tmp, cost += tmp * (dis[s] + h[s]); }
		for(int i=1;i<=t;i++) h[i] += min(dis[i], dis[s]);
	} return {flow, cost}; }