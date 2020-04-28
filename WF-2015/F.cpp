#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto &a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair< int, int > pii;
typedef vector< int > vi;

const int MAXRC = 50;
const int MAXL = 10000;

char board[MAXRC+1][MAXRC+1];
bool visited[MAXRC+1][MAXRC+1][MAXL+2];
string s;

pii edge[4][MAXRC+1][MAXRC+1];
const int U = 0, L = 1, D = 2, R = 3;

int main() {
    int r, c; cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> board[i][j];
        }
    }
    cin >> s;
    s = s + "*";
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (i == 1) edge[U][i][j] = {0,0};
            else if (board[i][j] != board[i-1][j]) {
                edge[U][i][j] = {i-1,j};
            } else {
                edge[U][i][j] = edge[U][i-1][j];
            }
            if (j == 1) edge[L][i][j] = {0,0};
            else if (board[i][j] != board[i][j-1]) {
                edge[L][i][j] = {i,j-1};
            } else {
                edge[L][i][j] = edge[L][i][j-1];
            }
        }
    }
    for (int i = r; i >= 1; i--) {
        for (int j = c; j >= 1; j--) {
            if (i == r) edge[D][i][j] = {0,0};
            else if (board[i][j] != board[i+1][j]) {
                edge[D][i][j] = {i+1,j};
            } else {
                edge[D][i][j] = edge[D][i+1][j];
            }
            if (j == c) edge[R][i][j] = {0,0};
            else if (board[i][j] != board[i][j+1]) {
                edge[R][i][j] = {i,j+1};
            } else {
                edge[R][i][j] = edge[R][i][j+1];
            }
        }
    }

    queue<tuple<int,int,int,int>> q;
    q.push({1,1,0,0});
    visited[1][1][0] = 1;
    while(!q.empty()) {
        int i, j, num_match, dist;
        tie(i, j, num_match, dist) = q.front(); q.pop();
        /* cerr << i << " " << j << " " << num_match << " " << dist << " " << board[i][j] << endl; */
        if (num_match == s.length()) {
            cout << dist << endl;
            return 0;
        }
        if (board[i][j] == s[num_match]) {
            visited[i][j][num_match+1] = 1;
            q.push({i,j,num_match+1,dist+1});
        } 
        else {
            for (int dir = 0; dir < 4; dir++) {
                int nexti, nextj;
                tie(nexti, nextj) = edge[dir][i][j];
                if (nexti == 0 && nextj == 0) continue;
                if (visited[nexti][nextj][num_match])  continue;
                visited[nexti][nextj][num_match]=1;
                q.push({nexti, nextj, num_match, dist+1});
            }
        }
    }
}
