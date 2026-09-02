struct BIT{
	#define lowbit(x) (x & (-x))
	ll d[MAXN], d1[MAXN];
	void upd(int x, ll k) {
		for (int pos = x; x <= n; x += lowbit(x))
			d[x] += k, d1[x] += (pos - 1) * k;
	}
	void upd(int l, int r, ll k) {upd(l, k), upd(r+1, -k);}
	ll qry(int x) {
		ll ret = 0, pos = x;
		for (int pos = x; x; x -= lowbit(x))
			ret += d[x] * pos - d1[x];
		return ret;
	}
	ll qry(int l, int r) {return qry(r) - qry(l-1);}
};