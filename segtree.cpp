int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}
template<class T>
class SegTree{
	private:
		const T id = int_max;
		vector<T> segtree;
		
	public:
		int len;
		SegTree(int l){
			int n = 1 << log2_floor(l);
			if(l != n){
				n = 1 << (log2_floor(l)+1);
			}
			len = n;
			
			segtree.resize(len*2, id);
		}

		void update(int ind, T val){
			ind+= len;
			segtree[ind] = val;
			//cout<<ind<<"\n";
			for(; ind > 1; ind /= 2){
				segtree[ind/2] = min(segtree[ind], segtree[ind^1]);
			}
		}
		void display(){
			cout<<len<<segtree.size()<<"\n";
		}
		T query(int node, int nL, int nR, int l, int r){
			if(l > r) return id;
			if(l==nL && r==nR){

				return segtree[node];
			}
			int m = (nL+nR)/2;
			return min(query(node*2,nL,m,l,min(r,m)),query(node*2+1,m+1,nR,max(l,m+1),r));
		}
		
};