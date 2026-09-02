int merge(int x, int y, int l, int r){
	if(!x || !y) return x+y;
	if(l == r){ /*合并x与y节点的贡献*/ del(y); return;}
	int mid = (l+r)>>1;
	ls[x] = merge(ls[x], ls[y], l, mid);
	rs[x] = merge(rs[x], rs[y], mid+1, r);
	// update(l, r, x, tag[y]); 李超合并
	del(y); push_up(x);
	return x; // 别忘了return x!!!!!!!
}
