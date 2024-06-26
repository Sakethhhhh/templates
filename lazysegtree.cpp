struct SegTree {
    int sz;
    vector<int64> t, lazy;
    int64 id, lazy_id;
    void init(int n, int64 id1, int id2) {
        sz = n;
        id = id1;
        lazy_id = id2;
        t.assign(4 * n, id);
        lazy.assign(4 * n, lazy_id);
    }
    void _build(int v, vector<int64>& a, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) >> 1;
            _build(2 * v, a, tl, tm);
            _build(2 * v + 1, a, tm + 1, tr);
            t[v] = max(t[2 * v], t[2 * v + 1]);
        }
    }
    void build(vector<int64>& a) {
        _build(1, a, 0, sz - 1);
    }
    void push(int v) {
        t[v * 2] += lazy[v];
        t[v * 2 + 1] += lazy[v];
        lazy[v * 2] += lazy[v];
        lazy[v * 2 + 1] += lazy[v];
        lazy[v] = lazy_id;
    }
    void _modify(int v, int tl, int tr, int l, int r, int val) {
        if (l > r) return;
        if (tl == l && tr == r) {
            t[v] += val;
            lazy[v] += val;
        }
        else {
            push(v);
            int tm = (tl + tr) >> 1;
            _modify(2 * v, tl, tm, l, min(tm, r), val);
            _modify(2 * v + 1, tm + 1, tr, max(tm + 1, l), r, val);
            t[v] = max(t[2 * v], t[2 * v + 1]);
        }
    }
    void modify(int l, int r, int val) {
        _modify(1, 0, sz - 1, l, r, val);
    }

    int64 _query(int v, int tl, int tr, int l, int r) {
        if (l > r) return id;
        if (tl == l && tr == r) {
            return t[v];
        }
        else {
            push(v);
            int tm = (tl + tr) >> 1;
            return max(_query(2 * v, tl, tm, l, min(tm, r)), _query(2 * v + 1, tm + 1, tr, max(tm + 1, l), r));
        }
    }
    int64 query(int l, int r) {
        return _query(1, 0, sz - 1, l, r);
    }
};
