#include <bits/stdc++.h>

using namespace std;

long long n;

enum OPTYPE {
  INS,
  DEL,
};

struct op {
  OPTYPE type;
  long long pos;
  char c;
};

vector<op> readops() {
  char optype;
  vector<op> ret;
  while(cin >> optype) {
    op oper;
    if(optype == 'E') {
      return ret;
    }

    cin >> oper.pos;
    if(optype == 'I') {
      oper.type = INS;
      cin >> oper.c;
    }
    else {
      oper.type = DEL;
      oper.c = '_';
    }
    ret.push_back(oper);
  }
}

vector<op> sortops(vector<op> ops) {
  // bubble sort: we want all DELs before all INSs, the INS block to be sorted in decreasing order, and the DEL block
  // to be sorted in increasing order, to avoid situations like INS 4 C, INS 5 D which can also be written as
  // INS 4 D, INS 4 C (and vice versa for the DEL block)
  int iters = ops.size();
  for(int i = 0; i<iters; ++i) {
    for(int j = 0; j<(int)ops.size()-1; ++j) {
      if(ops[j].type == INS && ops[j+1].type == INS) {
        if(ops[j].pos < ops[j+1].pos) {
          swap(ops[j], ops[j+1]);
          ops[j].pos--;
        }
      }
      if(ops[j].type == INS && ops[j+1].type == DEL) {
        if(ops[j].pos == ops[j+1].pos) {
          ops.erase(ops.begin() + j);
          ops.erase(ops.begin() + j);
          break;
        }
        else if(ops[j].pos > ops[j+1].pos) {
          swap(ops[j], ops[j+1]);
          ops[j+1].pos--;
        }
        else {
          swap(ops[j], ops[j+1]);
          ops[j].pos--;
        }
      }
      if(ops[j].type == DEL && ops[j+1].type == INS) {
        // do nothing
      }
      if(ops[j].type == DEL && ops[j+1].type == DEL) {
        if(ops[j].pos > ops[j+1].pos) {
          swap(ops[j], ops[j+1]);
          ops[j+1].pos--;
        }
      }
    }
  }
  return ops;
}

bool equal(vector<op> o1, vector<op> o2) {
  /*
  cout << o1.size() << " " << o2.size() << endl;
  if(o1.size() <= 209) {
    for(int i = 0; i<o1.size(); ++i) {
      cout << (o1[i].type == INS ? "INS " : "DEL ");
      cout << o1[i].pos << " ";
      cout << o1[i].c << "    ";
      if(i < o2.size()) {
        cout << (o2[i].type == INS ? "INS " : "DEL ");
        cout << o2[i].pos << " ";
        cout << o2[i].c << endl;
      }
    }
  }
  */
  if(o1.size() != o2.size()) return false;
  for(int i = 0; i<o1.size(); ++i) {
    if(o1[i].type != o2[i].type) return false;
    if(o1[i].pos != o2[i].pos) return false;
    if(o1[i].c != o2[i].c) return false;
  }
  return true;
}

int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);

  while(cin >> n) {
    vector<op> p1 = sortops(readops()), p2 = sortops(readops());
    cout << (equal(p1, p2) ? "Identical" : "Different") << endl;
  }
}
