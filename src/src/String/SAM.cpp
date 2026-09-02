struct SAM{ // 别忘记空间是两倍 改字符集记得全改了
	int last = 1, tot = 1;
	int ch[MAXN<<1][26], len[MAXN<<1], f[MAXN<<1];
	void ins(char c){
		c -= 'a';
		int p = last, cur = last = ++tot;
		len[cur] = len[p] + 1;
		for(;p && !ch[p][c];p=f[p]) ch[p][c] = cur;
		if(!p) {f[cur] = 1; return;}
		int q = ch[p][c];
		if(len[q] == len[p] + 1) {f[cur] = q; return;}
		int clone = ++tot; 
		for(int i=0;i<26;i++) ch[clone][i] = ch[q][i];
		f[clone] = f[q], len[clone] = len[p] + 1;
		f[q] = f[cur] = clone;
		for(;p && ch[p][c] == q;p=f[p]) ch[p][c] = clone;
	}
} sam;
