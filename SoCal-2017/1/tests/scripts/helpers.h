#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > generateSmall(int n);
vector<vector<int> > generateLarge(int n);
void reduce(vector<vector<int> > &square);
bool isLatin(vector<vector<int> > square);
bool isReduced(vector<vector<int> > square);
void writeSquare(vector<vector<int> > square, ofstream &out);
void writeSquareType(vector<vector<int> > square, ofstream &out);
