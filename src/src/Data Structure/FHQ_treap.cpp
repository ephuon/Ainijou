struct FHQ{
	int val[MAXN], dat[MAXN], siz[MAXN], ls[MAXN], rs[MAXN], tot = 0, root;

	void push_up(int x) {siz[x] = siz[ls[x]] + siz[rs[x]] + 1;}
	int merge(int x, int y){
		if(!x || !y) return x+y;
		if(dat[x] < dat[y]) {push_down(x); rs[x] = merge(rs[x], y); push_up(x); return x;}
		else {push_down(y); ls[y] = merge(x, ls[y]); push_up(y); return y;}
	}
	void splitByVal(int now, int k, int& x, int& y){
		if(!now) {x = y = 0; return;}
		push_down(now);
		if(val[now] <= k) {x = now; splitByVal(rs[x], k, rs[x], y);}
		else {y = now; splitByVal(ls[y], k, x, ls[y]);}
		push_up(now);
	}
	void splitBySiz(int now, int k, int& x, int& y){
		if(!now) {x = y = 0; return;}
		push_down(now);
		if(siz[ls[now]] < k) {x = now; splitBySiz(rs[now], k-siz[ls[now]]-1, rs[x], y);}
		else {y = now; splitBySiz(ls[now], k, x, ls[y]);}
		push_up(now);
	}
	int new_node(int v){
		siz[++tot] = 1, val[tot] = v;
		dat[tot] = rand(); return tot;
	}
	void ins(int v){
		int x, y;
		splitByVal(root, v, x, y);
		root = merge(merge(x, new_node(v)), y);
	}
	void del(int v){
		int x, y, z;
		splitByVal(root, v, x, z), splitByVal(x, v-1, x, y);
		y = merge(ls[y], rs[y]);
		root = merge(merge(x, y), z);
	}
	int rk(int v){
		int x, y;
		splitByVal(root, v-1, x, y);
		int ret = siz[x] + 1;
		root = merge(x, y);
		return ret;
	}
	int kth(int now, int k){
		if(!now) return 0;
		while(true){
			if(siz[ls[now]] >= k) now = ls[now];
			else if(siz[ls[now]] + 1 == k) return val[now];
			else k -= siz[ls[now]] + 1, now = rs[now];
		}
	}
	int pre(int v){
		int x, y;
		splitByVal(root, v-1, x, y);
		int ret = kth(x, siz[x]);
		root = merge(x, y);
		return ret;
	}
	int nxt(int v){
		int x, y;
		splitByVal(root, v, x, y);
		int ret = kth(y, 1);
		root = merge(x, y);
		return ret;
	}
	int s[MAXN]; // 线性建立FHQ
	int build(int n){
		int top = 0;
		for(int i=1;i<=n;i++){
			int tmp = new_node(a[i]), last = 0;
			while(top && dat[s[top]] > dat[tmp]) push_up(s[top]), last = s[top--];
			if(top) rs[s[top]] = tmp;
			ls[tmp] = last, s[++top] = tmp;
		}
		while(top) push_up(s[top--]);
		return s[1];
	}
} tr;