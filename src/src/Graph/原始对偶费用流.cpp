bool dij(){
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[t] = 0;
	priority_queue<Node> q;
	q.push({t, 0});
	while(!q.empty()){
		auto [x, t] = q.top();
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(int i=head[x];i;i=e[i].next){
			int v = e[i].to;
			if(vis[v] || !e[i^1].w) continue;
			ll cost = -e[i].cost + h[x] - h[v];
			if(dis[v] > dis[x] + cost) {
				dis[v] = dis[x] + cost;
				q.push({v, dis[v]});
			}
		}
	}
	return dis[s] != inf;
}
void bfs(){
	for(int i=1;i<=t;i++) dep[i] = 0, cur[i] = head[i];
	queue<int> q;
	q.push(s);
	dep[s] = 1;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int i=head[x];i;i=e[i].next){
			int v = e[i].to;
			ll cost = e[i].cost + h[v] - h[x];
			if(dep[v] || !e[i].w || dis[v] != dis[x] - cost) continue;
			dep[v] = dep[x] + 1;
			q.push(v);
		}
	}
}
ll dfs(int x, ll in){
	if(x == t) return in;
	ll out = 0;
	for(int i=cur[x];i;i=e[i].next){
		cur[x] = i;
		int v = e[i].to;
		ll cost = e[i].cost + h[v] - h[x];
		if(dep[v] != dep[x] + 1 || dis[v] != dis[x] - cost || !e[i].w) continue;
		ll res = dfs(v, min(in, e[i].w));
		in -= res, out += res;
		e[i].w -= res, e[i^1].w += res;
		if(!in) break;
	}
	if(!out) dep[x] = 0;
	return out;
}
pair<ll, ll> solve(){
	ll flow = 0, cost = 0;
	while(dij()){
		bfs();
		ll tmp = dfs(s, inf);
		flow += tmp, cost += tmp * (dis[s] + h[s]);
		for(int i=1;i<=t;i++) h[i] += dis[i];
	}
	return {flow, cost};
}
bool spfa(){ // 初始负权（如求最大费用）需要先跑一次spfa
	memset(dis, 0x3f, sizeof(dis));
	queue<int> q;
	q.push(t);
	dis[t] = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		inq[x] = false;
		for(int i=head[x];i;i=e[i].next){
			int v = e[i].to;
			if(!e[i^1].w || dis[v] <= dis[x] - e[i].cost) continue;
			dis[v] = dis[x] - e[i].cost;
			if(!inq[v]) q.push(v), inq[v] = true;
		}
	}
	for(int i=1;i<=t;i++) h[i] = dis[i];
	return dis[s] != inf;
}