#include <bits/stdc++.h>

using namespace std;

set<int> not_done;
vector<bool> seen;

void dfs(int curr, vector<vector<int> > &adj) {
  seen[curr] = true;
  for(int i = 0; i<adj[curr].size(); ++i) {
    if(!seen[adj[curr][i]]) dfs(adj[curr][i], adj);
  }
}

int main() {
  // If you draw a directed edge from every animal to its corresponding enclosure, you've got an Eulerian path problem.
  // Recall that there exists an Eulerian path as long as at most two nodes have indegree != outdegree, the source and the sink
  // which have indegree == outdegree-1 and indegree == outdegree+1 respectively.  However, you also need the graph to
  // be connected -- i.e., the source can reach all vertices and all vertices can reach the sink.  One way of checking this
  // is by running a dfs on the forward graph from the source and one on the reverse graph from the sink.
  int n, m; cin >> n >> m;

  map<string, int> lookup;
  vector<string> correct(n);
  vector<vector<string> > enclosures(n);
  for(int i = 0; i<n; ++i) {
    cin >> correct[i];
    lookup[correct[i]] = i;

    int num_in; cin >> num_in;
    enclosures[i].resize(num_in);
    for(int j = 0; j<num_in; ++j) {
      cin >> enclosures[i][j];
    }
  }

  // Now actually draw the edges
  vector<vector<int> > adj(n), adj_back(n);
  for(int i = 0; i<n; ++i) {
    not_done.insert(i);
    for(int j = 0; j<enclosures[i].size(); ++j) {
      adj[i].push_back(lookup[enclosures[i][j]]);      // One animal goes from i to its enclosure
      adj_back[lookup[enclosures[i][j]]].push_back(i); // Reverse edge
    }
  }

  for(int i = 0; i<n; ++i) {
    // Is this animal already in its enclosure?
    bool is_in = true;
    if(adj[i].size() != adj_back[i].size()) is_in = false;
    for(int j = 0; j<adj[i].size(); ++j) {
      if(adj[i][j] != i) is_in = false;
    }
    if(is_in) {
      // We shouldn't consider it
      not_done.erase(i);
    }
  }

  if(not_done.empty()) {
    // All animals in their enclosures already
    cout << "FALSE ALARM" << endl;
    return 0;
  }

  int source = -1, sink = -1;
  bool works = true;
  for(int i = 0; i<n; ++i) {
    if(not_done.find(i) == not_done.end()) continue;
    if(adj[i].size() != adj_back[i].size()) {
      if(adj[i].size() == adj_back[i].size() + 1) {
        // One more outgoing edge: this should be the source
        if(source != -1) works = false;
        source = i;
      }
      else if(adj[i].size() == adj_back[i].size() - 1) {
        // One more incoming edge: this should be the sink
        if(sink != -1) works = false;
        sink = i;
      }
      else {
        works = false;
      }
    }
  }
  if(source == -1 || sink == -1) {
    if(source == -1 && sink == -1) {
      // Pick a node to be both the source and the sink
      source = *not_done.begin();
      sink = *not_done.begin();
    }
    else works = false;
  }

  if(works == false) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  // Now run dfs to make sure the graph is connected
  seen.assign(n, false);
  dfs(source, adj);
  for(auto x : not_done) {
    if(!seen[x]) works = false;
  }

  seen.assign(n, false);
  dfs(sink, adj_back);
  for(auto x : not_done) {
    if(!seen[x]) works = false;
  }

  if(works == false) {
    cout << "IMPOSSIBLE" << endl;
  }
  else {
    cout << "POSSIBLE" << endl;
  }
}
