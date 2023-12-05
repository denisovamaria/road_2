#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class DisjointSetUnion {
private:
    vector<int> parent;

public:
    explicit DisjointSetUnion(int n) : parent(n) {
        fill(parent.begin(), parent.end(), -1);
    }

    int FindSet(int x) {
        vector<int> buf;
        while (parent[x] >= 0) {
            buf.push_back(x);
            x = parent[x];
        }
        for (int i: buf) {
            parent[i] = x;
        }
        return x;
    }

    void Union(int x, int y) {
        x = FindSet(x);
        y = FindSet(y);

        if (x != y) {
            if (parent[x] > parent[y]) {
                swap(x, y);
            }

            parent[x] += parent[y];
            parent[y] = x;
        }
    }
    int UnitsCount() {
        int r = 0;
        for (int i: parent)
            if (i < 0) {
                r++;
            }
        return r;
    }
};

int main() {
    std::ifstream in("input.txt");
    int n, q;
    in >> n;
    in >> q;
    int k = 2;
    vector<vector<int>> a(k, vector<int>(q));

    for (int j = 0; j < q; j++) {
        in >> a[0][j];
        a[0][j]--;
        in >> a[1][j];
        a[1][j]--;
    }

    in.close();

    DisjointSetUnion country(n);

    ofstream out("output.txt");
    int t = country.UnitsCount();
    for (int i = 0; i < q; i++) {
        int s = a[0][i];
        int b = a[1][i];
        if (country.FindSet(s) == country.FindSet(b))
            out<<t<<'\n';
        else {
            country.Union(s, b);
            t--;
            out<<t<<'\n';
        }
    }
    out.close();
}