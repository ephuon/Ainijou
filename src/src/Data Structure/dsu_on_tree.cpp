void dfs2(int x, int fa, bool keep){
	for(auto v : e[x]){
		if(v == fa || v == son[x]) continue;
		dfs2(v, x, false);
	}
	if(son[x]) dfs2(son[x], x, true);
	for(auto v : e[x]){
		if(v == fa || v == son[x]) continue;
		for(int i=id[v];i<id[v]+siz[v];i++) add(c[rev[i]]);
	}
	add(c[x]);
	// 回答询问
	if(!keep) for(int i=id[x];i<id[x]+siz[x];i++) del(c[rev[i]]);
}