void getRt(int x, int fa){
	siz[x] = 1; son[x] = 0;
	for(int i=head[x];i;i=e[i].next){
		int v = e[i].to;
		if(v == fa || vis[v]) continue;
		getRt(v, x);
		siz[x] += siz[v];
		son[x] = max(son[x], siz[v]);
	}
	son[x] = max(son[x], totsiz - siz[x]);
	if(son[x] < minn) minn = son[x], root = x;
}
void solve(int x){
	for(int i=head[x];i;i=e[i].next){
		int v = e[i].to;
		if(vis[v]) continue;
		// 统计子树贡献
		// 回答询问
	}
	// 清空子树贡献
}
void divide(int x){
	vis[x] = 1;
	solve(x);
	for(int i=head[x];i;i=e[i].next){
		int v = e[i].to;
		if(vis[v]) continue;
		totsiz = siz[v], minn = inf, root = 0;
		getRoot(v, x); divide(root);
	}
}
