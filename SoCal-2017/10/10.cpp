#include <bits/stdc++.h>

using namespace std;

long long calc(vector<pair<int, int> > chain) {
  int n = chain.size();

  long long dp[n][n], best_split[n][n];
  for(int len = 1; len<=n; ++len) {
    for(int start = 0; start+len<=n; ++start) {
      int end = start+len;
      if(len == 1) {
        dp[start][end-1] = 0;
        continue;
      }
      long long fixed = chain[start].first * chain[end-1].second;
      long long min_split_cost = LLONG_MAX/10;

      for(int i = start; i<end-1; ++i) {
        long long split_cost = dp[start][i] + dp[i+1][end-1];
        if(split_cost < min_split_cost) {
          min_split_cost = split_cost;
          best_split[start][end-1] = i;
        }
      }

      dp[start][end-1] = fixed + min_split_cost;

      // Shows that Knuth DP doesn't work
      /*
      if(len > 2 && (best_split[start][end-1] < best_split[start][end-2] || best_split[start][end-1] > best_split[start+1][end-1])) {
        cout << "!!!!! KNUTH BAD !!!!!" << endl;
        for(int i = 0; i<n; ++i) {
          cout << chain[i].first << " " << chain[i].second << endl;
        }
        cout << start << " " << end << endl;
        cout << best_split[start][end-2] << " " << best_split[start][end-1] << " " << best_split[start+1][end-1] << endl;
        return -1;
      }
      */
    }
  }

  return dp[0][n-1] - chain[0].first * chain[n-1].second;
}

// INCORRECT greedy solution
long long calc_greedy(vector<pair<int, int> > chain) {
  long long ret = 0;
  queue<pair<int, int> > q;
  q.push(make_pair(0, chain.size()-1));

  while(!q.empty()) {
    pair<int, int> range = q.front(); q.pop();
    if(range.first == range.second) continue;

    // special cases
    long long best = chain[range.first+1].first * chain[range.second].second;
    int bindex = range.first+1;

    long long next = chain[range.first].first * chain[range.second-1].second;
    if(best > next) {
      best = next;
      bindex = range.second;
    }

    // body cases
    for(int i = range.first+2; i<range.second; ++i) {
      long long curr = chain[range.first].first * chain[i-1].second + chain[i].first * chain[range.second].second;
      if(best > curr) {
        best = curr;
        bindex = i;
      }
    }
    q.push(make_pair(range.first, bindex-1));
    q.push(make_pair(bindex, range.second));
    ret += chain[range.first].first * chain[range.second].second;
  }

  return ret - chain[0].first * chain[chain.size()-1].second;
}

pair<int, int> process(string matrix) {
  matrix = matrix.substr(1, matrix.length()-2);
  stringstream stream(matrix);
  string dim;
  vector<int> mat;
  while(getline(stream, dim, ',')) {
    mat.push_back(stoi(dim));
  }
  return make_pair(mat[0], mat[1]);
}

int main() {
  string line;
  while(getline(cin, line)) {
    stringstream stream(line);
    string matrix;
    vector<pair<int, int> > chain;

    while(getline(stream, matrix, '*'))
    {
       chain.push_back(process(matrix));
    }

    cout << calc(chain) << endl;
  }
}
