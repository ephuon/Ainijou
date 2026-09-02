void init(){
	for(int i=1;i<=pri[0];i++)
		for(int j=tot;j>=1;j--){
			if(sta[j]/pri[i]<pri[i]) break;
			g1[j]=(g1[j]-(ll)pri[i]*pri[i]%mod * (g1[f(sta[j]/pri[i])]-g1[pri[i]-1]+mod)%mod+mod)%mod;
		}
}


// ll n,tmp;
// int f(ll x){
// 	if(x<=tmp) return x;
// 	return tot+1-(n/x);
// }

// int solve(ll n,int s){
// 	if(n<pri[s]) return 0;
// 	if(n/pri[s]<pri[s]) return (g[f(n)]-(s>1?g[pri[s-1]]:0)+mod)%mod;
	
// 	ll e=n/pri[s];int d=pri[s],Sum=0;
// 	while(e){
// 		Sum=(Sum+(ll)d*(d-1+mod)%mod*(solve(e,s+1)+1))%mod;
// 		d=(ll)d*pri[s]%mod;e/=pri[s];
// 	}
	
// 	return (Sum+solve(n,s+1))%mod;
// } 