void ins(ll x){
	for(int i=62;i>=0;i--){
		if(!(x & (1ll<<i))) continue;
		if(a[i]) x ^= a[i];
		else {a[i] = x; break;}
	}
}