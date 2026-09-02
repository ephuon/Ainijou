struct AC{
int ch[N][26], fail[N], tag[N], tot;
void ins(string s, int _idx){
	int x = 0;
	for(auto c : s){
		int v = c - 'a';
		if(!ch[x][v]) ch[x][v] = ++tot;
		x = ch[x][v]; } tag[x] = _idx; }
void build(){
	queue<int> q;
	for(int i=0;i<26;i++) if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i=0;i<26;i++) {
			if(ch[x][i]) fail[ch[x][i]] = ch[fail[x]][i], q.push(ch[x][i]);
			else ch[x][i] = ch[fail[x]][i]; } } }
} ac;
