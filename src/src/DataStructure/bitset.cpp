template<int len = 1> // 动态size的bitset
void solve(int x) {
	if(siz[x] > len) return (void) solve<min(len*2, MAXN)>(x);
	bitset<len> dp; }