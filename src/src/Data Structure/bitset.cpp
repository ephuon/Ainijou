b.reset(); // 全部赋0
b.set(); // 全部赋1
b.count(); // 返回bitset内1的个数
b.filp(); // 全部取反
b._Find_first(); // 返回第一个1的位置
b._Find_next(); // 返回下一个1的位置，没有返回size
template<int len = 1> // 动态size的bitset
void solve(int x){
	if(siz[x] > len) return (void) solve<min(len*2, MAXN)>(x);
	bitset<len> dp;
}