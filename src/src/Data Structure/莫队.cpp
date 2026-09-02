int siz, bcnt, belong[MAXN];
struct Query{
	int l, r, id;
} Q[MAXN];
bool cmp(const Query& a, const Query& b) {
	return (belong[a.l] ^ belong[b.l]) ? belong[a.l] < belong[b.l] : ((belong[a.l] & 1) ? a.r < b.r : a.r > b.r);
}
void init(int n){
	siz = sqrt(n);
	bcnt = ceil(double(n) / siz);
	for(int i=1;i<=bcnt;i++) for(int j=(i-1)*siz+1;j<=n&&j<=i*siz;j++) belong[j] = i;
}
int main(){
	int l = 1, r = 0;
	for(int i = 1; i <= m; ++i) {
		int ql = Q[i].l, qr = Q[i].r;
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(l < ql) del(l++);
		while(r > qr) del(r--);
		// 回答询问
	}
}