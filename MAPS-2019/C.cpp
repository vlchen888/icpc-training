#include <bits/stdc++.h>

using namespace std;

int length(long long x) {
  if(x == 0) return 1;

  int ret = 0;
  while(x) {
    x /= 10;
    ret++;
  }
  return ret;
}

int main() {
  // 2^18 is far under the time limit, so this is brute force-able
  // Be careful -- 18 digits doesn't fit in an int!
  //
  // To test this code, since it has a while(cin >> ) loop, it's useful to create an input file C.in and run $ ./a.out < C.in
  // so that it knows when to stop.

  vector<long long> nums;
  char plus;
  long long curr_num;
  cin >> curr_num;
  nums.push_back(curr_num);
  while(cin >> plus) {
    cin >> curr_num;
    nums.push_back(curr_num);
  }

  vector<int> lengths; // For easier concatenation
  for(int i = 0; i<nums.size(); ++i) {
    lengths.push_back(length(nums[i]));
  }

  set<long long> possibilities;
  for(long long bitmask = 0; bitmask<(1<<(nums.size()-1)); ++bitmask) {
    // The ith digit of the mask tells you whether you use + or [+] (concat.) on the ith operator
   
    // Concatenate first, and then add:
    vector<long long> new_nums;
    for(int i = 0; i<nums.size(); ++i) {
      long long curr = nums[i];
      while(i < nums.size()-1 && ((bitmask>>i)&1)) {
        // While the ith digit is on, we merge to the right
        curr *= pow(10, lengths[i+1]);
        curr += nums[i+1];
        i++;
      }
      new_nums.push_back(curr);
    }

    // Add it up!
    long long total = 0;
    for(int i = 0; i<new_nums.size(); ++i) {
      total += new_nums[i];
    }
    //cout << total << endl;
    possibilities.insert(total);
  }
  cout << possibilities.size() << endl;
}
