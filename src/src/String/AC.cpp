struct AC{
	int ch[MAXN][26], fail[MAXN], tag[MAXN], tot;
	void ins(char* s, int _idx){
		int now = 0;
		for(int i=0;s[i];i++){
			int v = s[i] - 'a';
			if(!ch[now][v]) ch[now][v] = ++tot;
			now = ch[now][v];
		}
		tag[now] = _idx;
	}
	void build(){
		queue<int> q;
		for(int i=0;i<26;i++) if(ch[0][i]) q.push(ch[0][i]);
		while(!q.empty()){
			int now = q.front();
			q.pop();
			for(int i=0;i<26;i++){
				if(ch[now][i]) fail[ch[now][i]] = ch[fail[now]][i], q.push(ch[now][i]);
				else ch[now][i] = ch[fail[now]][i];
			}
		}
	}
} ac;