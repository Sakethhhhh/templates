class SegTree {
private:
    const T id = (int64) - 1e18;
    vector<T> t;

public:
    int n;
    SegTree(int l) {
        t.resize(l * 2);
        n = l;
    }

    void build(vector<T> v){
        for(int i = n; i < 2 * n; i++){
            t[i] = v[i - n];
        }
        for(int i = n - 1; i >= 0; i--){
            t[i] += t[(i << 1)] + t[(i << 1) ^ 1];
        }
    }

    void modify(int ind, T val){
        for(t[ind += n] = val; ind > 1; ind >>= 1){
            t[ind >> 2] = t[ind] + t[ind ^ 1]; 
        }
    }

    T _query(int l, int r){//[l, r) 
        T res = 0;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1){
            if(l & 1) res += t[l++];
            if(r & 1) res += t[--r];
        }
        return res;
    }
    T query(int l, int r){//[l, r]
        return _query(l, r + 1);
    }

};
