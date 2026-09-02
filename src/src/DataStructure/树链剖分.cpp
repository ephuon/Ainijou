Node query_len(int x, int y){
	Node res1 = Node(0), res2 = Node(0);
	while(top[x] != top[y]){
		if(dep[top[x]] > dep[top[y]]){
			res1 = query(id[top[x]], id[x], 1, n, 1) + res1;
			x = f[top[x]];
		}else{
			res2 = query(id[top[y]], id[y], 1, n, 1) + res2;
			y = f[top[y]];
		}
	}
	if(dep[x] <= dep[y]) res2 = query(id[x], id[y], 1, n, 1) + res2;
	else res1 = query(id[y], id[x], 1, n, 1) + res1;
	swap(res1.l, res1.r);
	return res1 + res2;
}