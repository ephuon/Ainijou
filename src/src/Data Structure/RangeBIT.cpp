struct BIT{
	#define lowbit(x) (x & (-x))
	ll d[MAXN], d1[MAXN];
	void _update(int x, ll k) {
		int pos = x;
		while(x <= n) d[x] += k, d1[x] += (pos-1)*k, x += lowbit(x);
	}
	void update(int l, int r, ll k) {_update(l, k), _update(r+1, -k);}
	ll _query(int x) {
		ll ret = 0, pos = x;
		while(x) ret += pos * d[x] - d1[x], x -= lowbit(x);
		return ret;
	}
	ll query(int l, int r) {return _query(r) - _query(l-1);}
}