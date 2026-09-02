struct SAM{
	int ch[MAXN<<1][26], f[MAXN<<1], len[MAXN<<1], tot = 1;
	int ins(int c, int last){
		c -= 'a';
		int cur, p;
		if(ch[last][c]){
			p = last, cur = ch[p][c];
			if(len[p] + 1 == len[cur]) return cur;
			int q = cur, clone = ++tot;
			for(int i=0;i<26;i++) ch[clone][i] = ch[q][i];
			len[clone] = len[p] + 1;
			f[clone] = f[q], f[q] = clone;
			for(;p&&ch[p][c]==q;p=f[p]) ch[p][c] = clone;
			return clone;
		}
		p = last, cur = ++tot;
		len[cur] = len[p] + 1;
		for(;p&&!ch[p][c];p=f[p]) ch[p][c] = cur;
		if(!p) {f[cur] = 1; return cur;}
		int q = ch[p][c];
		if(len[p] + 1 == len[q]) {f[cur] = q; return cur;}
		int clone = ++tot; 
		for(int i=0;i<26;i++) ch[clone][i] = ch[q][i];
		len[clone] = len[p] + 1;
		f[clone] = f[q], f[q] = f[cur] = clone;
		for(;p&&ch[p][c]==q;p=f[p]) ch[p][c] = clone;
		return cur;
	}
	void ins(char* s){
		int last = 1;
		for(int i=0;s[i];i++) last = ins(s[i], last);
	}
} sam;