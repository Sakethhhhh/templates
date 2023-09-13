int log2_floor(unsigned long long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}
template<class T>
class LazySegTree{
	private:
		const T id = 0;
		vector<T> segtree;
		vector<T> lazy;
	public:
		int len;
		LazySegTree(int l){
			int n = 1 << log2_floor(l);
			if(l != n){
				n = 1 << (log2_floor(l)+1);
			}
			len = n;
			
			segtree.resize(len*2, id);
			lazy.resize(len*2, id);
		}

		void update(int ind, T val){
			ind+= len;
			segtree[ind] = val;
			for(; ind > 1; ind /= 2){
				segtree[ind/2] = segtree[ind] + segtree[ind^1];
			}
		}
		void pull(int node){
			int ind = node;
			for(; ind > 1; ind /= 2){
				segtree[ind/2]=segtree[ind] + segtree[ind^1];
			}
		}
		void push(int v){
			lazy[2*v] += lazy[v];
			lazy[2*v+1] += lazy[v];
			lazy[v] = id;
		}
		void rupdate(int node, int nL,int nR, int l, int r, T val){
			if(l > r) return;
			if(nL == nR){
				lazy[node]+= val;
				segtree[node] += (r - l + 1) * lazy[node];
				lazy[node] = id;
				pull(node);
			}
			else if(l==nL && r==nR){
				lazy[node]+=val;
				segtree[node] += (r - l + 1) * lazy[node];
				push(node);
				pull(node);
			}
			else{
				push(node);
				int m = (nL+nR)/2;
				rupdate(2*node,nL,m,l,min(r,m),val);
				rupdate(2*node+1,m+1,nR,max(l,m+1),r,val);
			}
		}
		void display(){
			for(int i=0;i<len*2;i++){
				cout<<lazy[i]<<" ";
			}
			cout<<"\n";
		}
		T _query(int node, int nL, int nR, int l, int r){
			if(l > r) return id;
			else if(nL==nR){
				segtree[node]+=(r-l+1)*lazy[node];
				lazy[node]=id;
				pull(node);
				return segtree[node];
			}
			else if(l==nL && r==nR){
				segtree[node] += (r-l+1)*lazy[node];
				push(node);
				pull(node);
				return segtree[node];
			}
			else{
				push(node);
				int m = (nL+nR)/2;
				return (_query(node*2,nL,m,l,min(r,m))+_query(node*2+1,m+1,nR,max(l,m+1),r));
			}
		}
		T query(int l, int r){
			return _query(1,0,len-1,l,r);
		}
		void range_update(int l, int r, T val){
			rupdate(1, 0, len-1,l,r,val);
		}
		
};