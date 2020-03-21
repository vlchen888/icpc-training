#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Multiply a polynomial a, by a (x - r)
vector<ll> multi(vector<ll> a, int r) {
    vector<ll> ans;
    for (int i = 0; i < a.size() + 1; i++) {
        if (i == a.size())
            ans.push_back(a[i-1]);
        else if (i == 0)
            ans.push_back(-r * a[0]);
        else
            ans.push_back(a[i-1] - r * a[i]);
    }
    return ans;
}
int main() {
    int count = 1;
    vector<ll> roots, poly;
    char cur, next, first_char;
    cin >> cur;
    first_char = cur;
    while( cin >> next) {
        if (next != cur) {
            roots.push_back(2 * count + 1);
        }
        count ++;
        cur = next;
    }

    if ((first_char == 'H' && roots.size() % 2 == 0) || 
            first_char == 'A' && roots.size() % 2 == 1) {

            poly.push_back(1);
        } else {
            poly.push_back(-1);
        }
    for (int i = 0; i < roots.size(); i++) {
        poly = multi(poly, roots[i]); 
    }
    cout << roots.size() << endl;
    for (int i = poly.size() - 1; i >= 0; i--) {
        if (i == 0)
            cout << poly[i];
        else
            cout << poly[i] << ' ';
    }
}