#include<bits/stdc++.h>
using namespace std;

int MOD = 1000000007;

class segTree {
    vector<long long> Tree;
    vector<bool> lazy;
    int siz;
public:
    segTree(vector<long long> &arr)
    {
        siz = arr.size() - 1;
        Tree.resize(4 * siz + 10);
        lazy.resize(4 * siz + 10);
        buildTree(arr, 0, 0, siz);
    }

    void buildTree(vector<long long> &arr, int index, int l, int r)
    {
        if (l == r)
        {
            Tree[index] = 0;
            return;
        }
        int mid = (l + r) / 2;
        buildTree(arr, 2 * index + 1, l, mid);
        buildTree(arr, 2 * index + 2, mid + 1, r);
        Tree[index] = Tree[2 * index + 1] + Tree[2 * index + 2];
    }

    void UpdateHelper(int l, int r, int index, int le, int re)
    {
        if (lazy[index] == 1)
        {
            Tree[index] = (re - le + 1) - Tree[index];
            if (le != re)
            {
                lazy[2 * index + 1] = !lazy[2 * index + 1];
                lazy[2 * index + 2] = !lazy[2 * index + 2];
            }
            lazy[index] = 0;
        }
        if (l <= le and r >= re)
        {
            Tree[index] = (re - le + 1) - Tree[index];
            if (le != re)
            {
                lazy[2 * index + 1] = !lazy[2 * index + 1];
                lazy[2 * index + 2] = !lazy[2 * index + 2];
            }
            return;
        }
        if (l > re or r < le)
            return;
        int mid = (le + re) / 2;
        UpdateHelper(l, r, 2 * index + 1, le, mid);
        UpdateHelper(l, r, 2 * index + 2, mid + 1, re);
        Tree[index] = Tree[2 * index + 1] + Tree[2 * index + 2];
    }

    void update(int l, int r)
    {
        UpdateHelper(l, r, 0, 0, siz);
    }

    long long queryHelper(int val, int index, int le, int re)
    {
        if (lazy[index] == 1)
        {
            Tree[index] = (re - le + 1) - Tree[index];
            if (le != re)
            {
                lazy[2 * index + 1] = !lazy[2 * index + 1];
                lazy[2 * index + 2] = !lazy[2 * index + 2];
            }
            lazy[index] = 0;
        }
        if (le == re)
        {
            return le;
        }
        int mid = (le + re) / 2;
        int checkCount = (lazy[2 * index + 1] ? ((mid - le + 1) - Tree[2 * index + 1]) : Tree[2 * index + 1]);
        if (checkCount >= val)
            return queryHelper(val, 2 * index + 1, le, mid);
        else
            return queryHelper(val - checkCount, 2 * index + 2, mid + 1, re);
    }

    long long query(int val)
    {
        return queryHelper(val, 0 , 0, siz);
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<long long> arr(n, 0);
    segTree tree(arr);
    while (m--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            r--;
            tree.update(l, r);
        }
        else
        {
            int val;
            cin >> val;
            val++;
            cout << tree.query(val) << endl;
        }

    }
}