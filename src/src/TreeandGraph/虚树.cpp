bool cmp(int x, int y) {return id[x] < id[y];}
void build(vector<int> v){
	sort(v.begin(), v.end(), cmp);
	int top = 0;
	s[top=1] = 1; vt::e[1].clear();
	for(auto x : v){
		if(x == 1) continue;
		int l = lca(x, s[top]);
		if(l != s[top]){
			while(id[l] < id[s[top-1]]) vt::push(s[top-1], s[top]), top--;
			if(l != s[top-1]) vt::e[l].clear(), vt::push(l, s[top]), s[top] = l;
			else vt::push(l, s[top--]);
		}
		s[++top] = x; vt::e[x].clear();
	}
	for(int i=1;i<top;i++) vt::push(s[i], s[i+1]);
}
