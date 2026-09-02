struct FHQ{
int val[N], dat[N], siz[N], ls[N], rs[N], tot = 0, rt;
void push_up(int x) {siz[x] = siz[ls[x]] + siz[rs[x]] + 1;}
int merge(int x, int y){
	if(!x || !y) return x+y;
	if(dat[x] < dat[y]) {push_down(x); rs[x] = merge(rs[x], y); push_up(x); return x;}
	else {push_down(y); ls[y] = merge(x, ls[y]); push_up(y); return y;} }
void splitVal(int p, int k, int& x, int& y){
	if(!p) {x = y = 0; return;}
	push_down(p);
	if(val[p] <= k) {x = p; splitVal(rs[x], k, rs[x], y);}
	else {y = p; splitVal(ls[y], k, x, ls[y]);}
	push_up(p);
}
void splitSiz(int p, int k, int& x, int& y){
	if(!p) {x = y = 0; return;}
	push_down(p);
	if(siz[ls[p]] < k) {x = p; splitSiz(rs[p], k-siz[ls[p]]-1, rs[x], y);}
	else {y = p; splitSiz(ls[p], k, x, ls[y]);}
	push_up(p);
}
int new_node(int v){
	siz[++tot] = 1; val[tot] = v; 
	dat[tot] = rd(); return tot;}
void ins(int v){
	int x, y; splitVal(rt, v, x, y);
	rt = merge(merge(x, new_node(v)), y); }
void del(int v){
	int x, y, z;
	splitVal(rt, v, x, z), splitVal(x, v-1, x, y);
	y = merge(ls[y], rs[y]); rt = merge(merge(x, y), z); }
int rk(int v){
	int x, y; splitVal(rt, v-1, x, y);
	int t = siz[x] + 1; rt = merge(x, y); return t; }
int kth(int p, int k){
	if(!p) return 0;
	while(true){
		if(siz[ls[p]] >= k) p = ls[p];
		else if(siz[ls[p]] + 1 == k) return val[p];
		else k -= siz[ls[p]] + 1, p = rs[p]; } }
int pre(int v){
	int x, y; splitVal(rt, v-1, x, y);
	int t = kth(x, siz[x]); rt = merge(x, y); return t; }
int nxt(int v){
	int x, y; splitVal(rt, v, x, y);
	int t = kth(y, 1); rt = merge(x, y); return t; }
int s[MAXN]; // 线性建立FHQ
int build(int n){
	int top = 0;
	for(int i=1;i<=n;i++){
		int tmp = new_node(a[i]), last = 0;
		while(top && dat[s[top]] > dat[tmp])
			push_up(s[top]), last = s[top--];
		if(top) rs[s[top]] = tmp; ls[tmp] = last, s[++top] = tmp;
	}
	while(top) push_up(s[top--]); return s[1]; }
} tr;