void init(){
	for(int i=1;i<=n;i++) lg[i] = lg[i-1] + ((1<<lg[i-1]) == i);
	for(int i=1;i<=n;i++) f[i][0] = arr[i];
	for(int i=1;i<lg[n];i++){
		for(int j=1;j<=n;j++){
			int k = j+(1<<i-1);
			if(k + (1<<i-1) > n+1) break;
			f[j][i] = max(f[j][i-1], f[k][i-1]);
		}
	}
}
ll query(int l, int r) {
	int len = lg[r-l+1] - 1;
	return max(f[l][len], f[r-(1<<len)+1][len])
}