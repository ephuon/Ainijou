ll KM(int n, int m){
	fill(p, p+1+m, 0);
	fill(r, r+1+m, 0);
	for(int i=1;i<=n;i++) 
		r[0] -= l[i] = *max_element(e[i]+1, e[i]+1+m);
	for(int i=1;i<=n;i++){
		fill(s, s+m+1, inf*2);
		fill(v, v+m+1, false);
		int y = 0, t; p[0] = i;
		do{
			v[y] = true; int x = p[y]; ll d = inf*2;
			for(int j=1;j<=m;j++) if(!v[j]){
				ll c = l[x] + r[j] - e[x][j];
				if(c < s[j]) s[j] = c, f[j] = y;
				if(s[j] < d) d = s[j], t = j;
			}
			if(e[p[f[t]]][t] == -inf) return -inf;
			for(int j=0;j<=m;j++){
				if(v[j]) l[p[j]] -= d, r[j] += d; else s[j] -= d;
			}
		}while (p[y = t]);
		while(y) p[y] = p[f[y]], y = f[y];
	}
	return -r[0];
}