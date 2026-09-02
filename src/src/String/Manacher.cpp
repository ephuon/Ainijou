void read(){ // 两倍空间
	s[0] = '~', s[++n] = '|';
	char c = getchar();
	while(c < 'a' || c > 'z') c = getchar();
	while('a' <= c && c <= 'z') s[++n] = c, s[++n] = '|', c = getchar();
}
void manacher(){
	int mx = 0, mid = -1, ans = 0;
	for(int i=1;i<=n;i++){
		if(i <= mx) h[i] = min(h[(mid<<1)-i], mx-i+1);
		else h[i] = 1;
		while(s[i-h[i]] == s[i+h[i]]) ++h[i];
		if(h[i] + i - 1 > mx) mx = h[i] + i - 1, mid = i; } }
