for(int i=1;i<=n;i++) {sum[i] = query(arr[i]) + sum[i-1]; add(i);}
sort(Q+1, Q+1+m, cmp);
int l = 1, r = 0;
for(int i=1;i<=m;i++){
	int ql = Q[i].l, qr = Q[i].r;
	if(l > ql) v[r].push_back({ql, l-1, i}), Q[i].ans -= sum[l-1] - sum[ql-1], l = ql;
	if(r < qr) v[l-1].push_back({r+1, qr, -i}), Q[i].ans += sum[qr] - sum[r], r = qr;
	if(l < ql) v[r].push_back({l, ql-1, -i}), Q[i].ans += sum[ql-1] - sum[l-1], l = ql;
	if(r > qr) v[l-1].push_back({qr+1, r, i}), Q[i].ans -= sum[r] - sum[qr], r = qr; 
}
// 清空贡献
for(int i=1;i<=n;i++){
	add(i);
	for(auto& [l, r, id] : v[i]){
		ll tmp = 0;
		for(int j=l;j<=r;j++){
			tmp += query(arr[j]);
			// 注意如果j <= i且会产生重复贡献的时候要扣去
		}
		if(id > 0) Q[id].ans += tmp;
		else Q[-id].ans -= tmp;
	}
} 
for(int i=1;i<=m;i++) Q[i].ans += Q[i-1].ans;
for(int i=1;i<=m;i++) ans[Q[i].id] = Q[i].ans;