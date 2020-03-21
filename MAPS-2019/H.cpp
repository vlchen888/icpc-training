#include <bits/stdc++.h>

using namespace std;

int main() {
  string s; cin >> s;
  set<char> s_chars;
  for(int i = 0; i<s.length(); ++i) {
    s_chars.insert(s[i]);
  }

  string perm; cin >> perm;
  int wrong = 0;
  for(int i = 0; i<perm.size(); ++i) {
    if(s_chars.find(perm[i]) == s_chars.end()) {
      // The ith guess isn't in the word
      wrong++;
      if(wrong >= 10) {
        cout << "LOSE" << endl;
        return 0;
      }
    }
    else {
      // The ith guess is in the word
      s_chars.erase(perm[i]);
      if(s_chars.empty()) {
        cout << "WIN" << endl;
        return 0;
      }
    }
  }
}
