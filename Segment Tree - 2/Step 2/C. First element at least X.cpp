#include <bits/stdc++.h>
using namespace std;

class segmentTree {
    vector<long long> tree;
    int left, right, siz;
public:
    segmentTree(vector<int> &arr)
    {
        siz = arr.size() - 1;
        tree.resize(siz * 4 + 10);
        left = 0, right = siz;
        buildTree(0, siz, 0, arr);
    }

    void buildTree(int l, int r, int index, vector<int> &arr)
    {
        if (l == r)
        {
            tree[index] = arr[l];
            return;
        }
        int mid = (l + r) / 2;

        buildTree(l, mid, 2 * index + 1, arr);
        buildTree(mid + 1, r, 2 * index + 2, arr);
        tree[index] = max(tree[2 * index + 1] , tree[2 * index + 2]);
    }

    void updateHelper(int pos, int val, int l, int r, int index)
    {
        if (r == l)
        {
            tree[index] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos >= l and pos <= mid)
            updateHelper(pos, val, l, mid, 2 * index + 1);
        else
            updateHelper(pos, val, mid + 1, r, 2 * index + 2);
        tree[index] = max(tree[2 * index + 1] , tree[2 * index + 2]);
    }

    void update(int pos, int val)
    {
        updateHelper(pos, val, 0, right, 0);
    }

    long long queryHelper(int val, int index, int le, int re)
    {
        if (le == re) {
            return le;
        }
        int mid = (le + re) / 2;
        if (val > tree[2 * index + 1])
            return queryHelper(val, 2 * index + 2, mid + 1, re);
        else
            return queryHelper(val, 2 * index + 1, le, mid);
    }

    long long query(int val)
    {
        if (val > tree[0])
            return -1;
        return queryHelper(val, 0, 0, siz);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (auto &i : arr)
    {
        cin >> i;
    }
    segmentTree tree(arr);
    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int pos, val;
            cin >> pos >> val;
            tree.update(pos, val);
        }
        else if (t == 2)
        {
            int k;
            cin >> k;
            cout << tree.query(k) << endl;
        }
    }
}