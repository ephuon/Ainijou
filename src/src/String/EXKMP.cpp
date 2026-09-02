void init(){
	int l = 0, r = 0;
	z[1] = 0;
	for(int i=2;i<=n;i++){
		if(i <= r && z[i-l+1] < r-i+1) z[i] = z[i-l+1];
		else {
			z[i] = max(0, r-i+1);
			while(i+z[i]<=n && b[i+z[i]]==b[z[i]+1]) z[i]++;
		}
		if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}