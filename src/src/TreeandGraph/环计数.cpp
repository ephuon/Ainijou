// Time complexity: $O(m\sqrt{m})$
for(int i=1;i<=m;i++) {
	if(deg[x[i]] > deg[y[i]] || (deg[x[i]] == deg[y[i]] && x[i] > y[i])) swap(x[i], y[i]);
	e[x[i]].push_back(y[i]);}
// 四元环计数
for(int i=1;i<=n;i++) {
	for(auto x : e[i]) for(auto y : e[x]) 
		if(deg[i] < deg[y] || (deg[i] == deg[y] && i <= y)) 
			ans += cnt[y]++; // 注意判等
	for(auto x : e[i]) for(auto y : e[x]) cnt[y] = 0;}