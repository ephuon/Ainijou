void split(int& x, int& y, int nl, int nr, int l, int r){
	if(nl <= l && r <= nr) {y = x, x = 0; return;}
	y = new_node();
	int mid = (l+r)>>1;
	if(nl <= mid) split(ls[x], ls[y], nl, nr, l, mid);
	if(nr > mid) split(rs[x], rs[y], nl, nr, mid+1, r);
	push_up(x), push_up(y);
}