namespace Li{ // 默认取max 可持久化李超记得从x转移而非p
	int tag[MAXN]; 
	double k[MAXN], b[MAXN];
	const double EPS = 1e-10;
	double calc(int i, double x) {return x * k[i] + b[i];}
	void update(int nl, int nr, int l, int r, int p, int x){
		if(l == r) {if(calc(tag[p], l) < calc(x, l)) tag[p] = x; return;}
		int mid = (l+r)>>1;
		if(nl <= l && r <= nr){
			if(!tag[p]) {tag[p] = x; return;}
			double l1 = calc(tag[p], l), l2 = calc(x, l), r1 = calc(tag[p], r), r2 = calc(x, r);
			if(abs(l1 - l2) < EPS && abs(r1 - r2) < EPS) return;
			if(l1 > l2 && r1 > r2) return;
			if(l2 > l1 && r2 > r1) tag[p] = x;
			if(calc(tag[p], mid) < calc(x, mid)) swap(x, tag[p]);
			if(k[x] > k[tag[p]]) update(nl, nr, mid+1, r, rs, x);
			if(k[x] < k[tag[p]]) update(nl, nr, l, mid, ls, x); 
			return;
		}
		if(nl <= mid) update(nl, nr, l, mid, ls, x);
		if(nr > mid) update(nl, nr, mid+1, r, rs, x);
	}
	double query(int pos, int l, int r, int p){
		if(l == r) return calc(tag[p], pos);
		int mid = (l+r)>>1;
		if(pos <= mid) return max(calc(tag[p], pos), query(pos, l, mid, ls));
		else return max(calc(tag[p], pos), query(pos, mid+1, r, rs));
	}
}