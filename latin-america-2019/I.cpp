#include <bits/stdc++.h>

using namespace std;

long long N, K, set_size[2000];

vector<vector<int>> edges;
set<int> touched;
int recurse(int index) {
    if (index > K){
        touched.insert(index);
        return 1;
    } 
    else {
        if (set_size[index] > 0) {
            return set_size[index];
        }
        long long ans = 0;
        for (int neigh : edges[index]) {
            ans += recurse(neigh);
        }
        ans = ans % (1000000000 + 7);
        set_size[index] = ans;
        return ans;
    }
}
int main() {
    cin >> N >> K;
    vector<int> v;
    edges.push_back(v);

    for (int i = 1; i < 2000; i ++) {
        set_size[i] = 0;
    }
    for (int i = 0; i < K; i++) {
        vector<int> neighbors;
        int num, neigh;
        cin >> num;
        for (int j = 0; j < num; j++) {
            cin >> neigh;
            neighbors.push_back(neigh);
        }
        edges.push_back(neighbors);
    }
    cout << recurse(1) << ' ' << touched.size();
}

