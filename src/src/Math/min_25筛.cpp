typedef long long ll;

ll n;
ll pri[N], sta[M], g[M]; int tot, mod;
int getid(ll x) {
	if(x <= sqrt(n)) return x;
	return tot + 1 - (n / x);
}

int solve(ll n, int id) {
	if(n < pri[id]) return 0;
	if(n / pri[id] < pri[id])
		return (g[getid(n)] - (id > 1 ? g[pri[id - 1]] : 0) + mod) % mod;

	ll e = n / pri[id]; int d = pri[id], Sum = 0;
	while(e) {
		Sum = (Sum + (ll)d * (d - 1 + mod) % mod * (solve(e, id + 1) + 1)) % mod;
		d = (ll)d * pri[id] % mod; e /= pri[id];
	}

	return (Sum + solve(n, id + 1)) % mod;
}

void init(){
	for(int i=1; i<=pri[0]; i++)
		for(int j=tot; j>=1; j--){
			if(sta[j] / pri[i] < pri[i]) break;
			int num = (g[getid(sta[j] / pri[i])] - g[pri[i] - 1] + mod) % mod;
			g[j] = (g[j] - (ll)pri[i] * pri[i] % mod * num % mod + mod) % mod;
		}
}