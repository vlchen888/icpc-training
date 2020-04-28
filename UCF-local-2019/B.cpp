#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  string s; cin >> s;
  int freq[26];
  for(int i = 0; i<26; ++i) freq[i] = 0;
  for(int i = 0; i<s.length(); ++i) {
    freq[s[i]-'a']++;
  }

  for(int i = 0; i<s.length(); ++i) {
    for(int j = 1; j<s.length(); ++j) {
      if(freq[s[j-1]-'a'] < freq[s[j]-'a']) {
        swap(s[j-1], s[j]);
      }
      if(freq[s[j-1]-'a'] == freq[s[j]-'a'] && s[j-1]>s[j]) {
        swap(s[j-1], s[j]);
      }
    }
  }
  cout << s << endl;
}
