// 3 30
// 0 10
// 50 60
// 100 35
// answer needs to be around (50, 60)
// there's some way to balance between left and right to get an average of 55
// so it's definitely not true that the best window is always anchored to a point
// (and that's why WA)
// my thinking was that if a point isn't on one edge of the window, you can slide
// the window, getting a better average height, and eventually hit a point
// here, that's not the case
// wait a minute.....
// scrap that line of thought
// I did the math wrong, it's better to be around the point
// the best window is 40-70, which is to be expected
// the problem is that slope isn't the only thing that matters when shifting a window,
// the two relative heights on the two sides of the window are critical too


#include <bits/stdc++.h>

using namespace std;

long double cy(long double x1, long double x2, long double y1, long double y2, long double x) {
  long double left = (x-x1)/(x2-x1)*y2;
  long double right = (x2-x)/(x2-x1)*y1;
  return (left + right);
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  int n; cin >> n;
  long double W; cin >> W;

  long double xs[n], ys[n];
  for(int i = 0; i<n; ++i) {
    cin >> xs[i] >> ys[i];
  }
  long double areas[n-1], cumulative_areas[n];
  cumulative_areas[0] = 0;
  for(int i = 0; i<n-1; ++i) {
    areas[i] = (xs[i+1] - xs[i]) * 0.5 * (ys[i+1] + ys[i]);
    cumulative_areas[i+1] = 0;
    cumulative_areas[i+1] += areas[i] + cumulative_areas[i];
  }

  long double best = 0;
  for(int i = 0; i<n; ++i) {
    // Window starting at i and going to the right
    {
      long double x = xs[i];
      long double area = 0;
      if(x + W >= xs[n-1]) {
        area = cumulative_areas[n-1] - cumulative_areas[i];
        area /= W;
        best = max(best, area);
      }
      else {
        int right_pos = lower_bound(xs, xs+n, x + W) - xs;
        area = cumulative_areas[right_pos] - cumulative_areas[i];
        cout << area << endl;
        area = area - (xs[right_pos] - (x + W)) * 0.5 * (ys[right_pos] + cy(xs[right_pos-1], xs[right_pos], ys[right_pos-1], ys[right_pos], x+W));
        area /= W;
        best = max(best, area);
      }
      cout << i << " " << area << endl;
    }
    // Window starting at i and going to the left
    {
      long double x = xs[i];
      long double area = 0;
      if(x - W <= xs[0]) {
        area = cumulative_areas[i];
        area /= W;
        best = max(best, area);
      }
      else {
        int left_pos = lower_bound(xs, xs+n, x - W) - xs;
        area = cumulative_areas[i] - cumulative_areas[left_pos];
        area = area + (xs[left_pos] - (x - W)) * 0.5 * (ys[left_pos] + cy(xs[left_pos-1], xs[left_pos], ys[left_pos-1], ys[left_pos], x-W));
        area /= W;
        best = max(best, area);
      }
      cout << i << " " << area << endl;
    }
  }
  cout << fixed << setprecision(9) << best << endl;
}
