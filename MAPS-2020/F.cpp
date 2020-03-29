#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  string temp;
  getline(cin, temp);
  set<string> st;
  for(int i = 0; i<n; ++i) {
    string s;
    getline(cin, s);
    for(int j = 0; j<s.length(); ++j) {
      if(s[j] >= 'A' && s[j] <= 'Z') {
        s[j] = s[j] - 'A' + 'a';
      }
      if(s[j] == '-') s[j] = ' ';
    }
    st.insert(s);
  }
  cout << st.size() << endl;
}
