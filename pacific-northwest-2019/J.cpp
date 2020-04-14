#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

#define PI 3.141592653589792328462643383279502884197

const int UP = 1, TURN = 2, DOWN = 3;
const double EPS = 1e-8;

double circle_angle(double x) {
    int f = int(x / (2*PI));
    x -= f * 2*PI;
    while (x < 0) x += 2*PI;
    while (x >= 2*PI) x -= 2*PI;
    assert(x >= 0);
    assert (x < 2*PI);
    return x;
}

double dist(double a, double b) {
    assert(a >= 0 && a < 2*PI && b >= 0 && b < 2*PI);
    if (b < a) b += 2*PI;
    assert(b - a >= 0);
    assert(b - a < 2*PI);
    return b - a;
}
bool equals(double a, double b) {
    return abs(a-b) < EPS;
}
bool between(double a, double b, double x) {
    return equals(dist(a,x) + dist(x,b),  dist(a,b));
}

int main() {
    srand(time(0));
    double f = (double(rand()) / RAND_MAX) * 2*PI;
    int N; cin >> N;
    vector<double> T(N), S(N), A(N);
    // angle, id, type
    vector<tuple<double, int, int>> events;
    double up_slopes = 0, down_slopes = 0;
    for (int i = 0; i < N; i++) {
        cin >> T[i] >> S[i] >> A[i];
        A[i] = circle_angle(A[i] + f);
        if (S[i] == 0) {
            continue;
        }
        double up_angle = circle_angle(A[i] - T[i]/S[i]);
        double turn_angle = circle_angle(A[i]);
        double down_angle = circle_angle(A[i] + T[i]/S[i]);
        if (T[i]/S[i] > PI) {
            up_angle = circle_angle(A[i] + PI + EPS);
            down_angle  = circle_angle(A[i] + PI - EPS);
            assert(T[i] - S[i] * PI >= 0);
        }
        if (equals(up_angle, 0)) {
            assert(false);
        } else if (equals(turn_angle, 0)) {
            assert(false);
        } else if (equals(down_angle, 0)) {
            assert(false);
        } else if (between(up_angle, turn_angle, 0)) {
            up_slopes += S[i];
        } else if (between(turn_angle, down_angle, 0)) {
            down_slopes += S[i];
        }
        events.push_back({up_angle, i, UP});
        events.push_back({turn_angle, i, TURN});
        events.push_back({down_angle, i, DOWN});
    }
    sort(all(events));
    double curr = 0;
    double curr_angle = 0;
    for (int i = 0; i < N; i++) {
        curr += max(0., T[i] - S[i] * min(dist(A[i], curr_angle), dist(curr_angle, A[i])));
    }
    double best = curr;

    for (int i = 0; i < events.size(); i++) {
        double angle; int id, type;
        tie(angle, id, type) = events[i];
        curr += (angle - curr_angle) * (up_slopes - down_slopes);
        if (type == UP) {
            up_slopes += S[id];
        } else if (type == TURN) {
            up_slopes -= S[id];
            down_slopes += S[id];
        } else if (type == DOWN) {
            down_slopes -= S[id];
        } else {
            assert(false);
        }
        curr_angle = angle;
        best = max(best, curr);
    }
    cout << fixed << setprecision(8) << best << '\n';
}
