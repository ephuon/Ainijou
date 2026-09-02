#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e6+100,maxn=1e6,mod=1e9+7;
ll sta[N];int pri[N],tot=0;bool bk[N];
map<ll,int> B;int g[N],g1[N],g2[N];

int mi(int x,int t){
	int d=1;
	while(t){
		if(t%2) d=(ll)d*x%mod;
		x=(ll)x*x%mod;t/=2;
	}
	return d;
}
int ni(int x) {return mi(x,mod-2);}

ll n,tmp;
int f(ll x){
	if(x<=tmp) return x;
	return tot+1-(n/x);
}

int solve(ll n,int s){
	if(n<pri[s]) return 0;
	if(n/pri[s]<pri[s]) return (g[f(n)]-(s>1?g[pri[s-1]]:0)+mod)%mod;
	
	ll e=n/pri[s];int d=pri[s],Sum=0;
	while(e){
		Sum=(Sum+(ll)d*(d-1+mod)%mod*(solve(e,s+1)+1))%mod;
		d=(ll)d*pri[s]%mod;e/=pri[s];
	}
	
	return (Sum+solve(n,s+1))%mod;
} 

int main()
{
	freopen("a.in","r",stdin);
	
	memset(bk,true,sizeof(bk));
	for(int i=2;i<=maxn;i++){
		if(bk[i]) pri[++pri[0]]=i;
		for(int j=1;j<=pri[0];j++){
			if(maxn/pri[j]<i) break;
			bk[i*pri[j]]=false;
			if(i%pri[j]==0) break;
		}
	}
	
	scanf("%lld",&n);tmp=sqrt(n);
	for(ll i=1;i<=n;i=n/(n/i)+1) sta[++tot]=n/(n/i),B[sta[tot]]=tot;
	
	int Ni6=ni(6),Ni2=ni(2);
	for(int i=1;i<=tot;i++){
		int t=sta[i]%mod;
		int t1=(ll)t*(t+1)%mod*(2*t+1)%mod*Ni6%mod;
		int t2=(ll)t*(t+1)%mod*Ni2%mod;
		g1[i]=t1; g2[i]=t2;
	}
	for(int i=1;i<=pri[0];i++)
		for(int j=tot;j>=1;j--){
			if(sta[j]/pri[i]<pri[i]) break;
			g1[j]=(g1[j]-(ll)pri[i]*pri[i]%mod*(g1[f(sta[j]/pri[i])]-g1[pri[i]-1]+mod)%mod+mod)%mod;
		}
	for(int i=1;i<=pri[0];i++)
		for(int j=tot;j>=1;j--){
			if(sta[j]/pri[i]<pri[i]) break;
			g2[j]=(g2[j]-(ll)pri[i]*(g2[f(sta[j]/pri[i])]-g2[pri[i]-1]+mod)%mod+mod)%mod;
		}
	for(int i=1;i<=tot;i++) g[i]=(g1[i]-g2[i]+mod)%mod;
	
//	return 0;
		
	printf("%d\n",(solve(n,1)+1)%mod);
	
	return 0;
}
