#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

ll factorials[21];

int main() {
    int n; scanf("%d", &n);
    double p[4];
    scanf("%lf %lf %lf %lf", p, p+1, p+2, p+3);
    factorials[0] = 1;
    for (int x = 1; x <= 20; x++) {
        factorials[x] = x * factorials[x-1]; 
    }
    priority_queue<pair<double, ll>,vector<pair<double,ll>>,greater<>> pq;
    for (int a=0; a<=n; a++) {
        for (int b=0; a+b<=n; b++) {
            for (int c=0; a+b+c<=n; c++) {
                int d = (n-a-b-c);
                double prob = pow(p[0],a)*pow(p[1],b)*pow(p[2],c)*pow(p[3],d);
                ll count = factorials[n]/factorials[a]/factorials[b]/factorials[c]/factorials[d];
                pq.push({prob, count});
            }
        }
    }
    double ev = 0;
    while (!pq.empty()) {
        double prob; ll count;
        tie(prob, count) = pq.top(); pq.pop();
        assert(count > 0);
        ev+=prob*((count/2)*2);
        if (count/2)
            pq.push({2*prob,count/2});
        if (count%2) {
            if (!pq.empty()) {
                double nextp; ll nextc;
                tie(nextp, nextc) = pq.top(); pq.pop();
                assert(nextc > 0);
                ev+=(nextp+prob);
                pq.push({nextp+prob,1});
                if (nextc-1)
                    pq.push({nextp,nextc-1});
            } 
        }
    }
    printf("%.8f\n", ev);
}
