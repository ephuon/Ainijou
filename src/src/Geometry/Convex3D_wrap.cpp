// 卷包裹法：精度越高，扰动次数越多
ld rd() {return ((ld)rand() / RAND_MAX - 0.5) * EPS;}
ld vol(cp o, cp a, cp b, cp c) {return mix(a-o, b-o, c-o); }
ld det2d(cp a, cp b) {return a.x * b.y - a.y * b.x;}
namespace Convex {
int n; bool used[MAXN]; bool e[MAXN][MAXN]; // 清空 used e？
void wrap(vector<point>& v, int a, int b) {
	if(!e[a][b]) {
		int c = -1;
		for(int i=0;i<n;i++) if(i != a && i != b)
			if(c == -1 || vol(v[c], v[a], v[b], v[i])>0) c = i;
		if(c == -1) return;
		// 求体积，求面积，新建面，...
		used[a] = 1, used[b] = 1, used[c] = 1;
		e[a][b] = 1, e[b][c] = 1, e[c][a] = 1;
		wrap(v, c, b), wrap(v, a, c);
} }
void make_convex(vector<point>& v) {
	n = v.size();
	for(int i=1;i<n;i++) if(v[i].x < v[0].x)
		swap(v[0], v[i]);
	for(int i=2;i<n;i++) if(det2d(v[i]-v[0], v[1]-v[0]) > 0)
		swap(v[1], v[i]);
	wrap(v, 0, 1);
} } // namespace Convex