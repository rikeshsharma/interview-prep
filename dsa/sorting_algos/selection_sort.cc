// rikesh
#include <iostream>
#include <vector>
using namespace std;

void selection_sort(vector<int> &v) {
  int n = v.size();
  for(int i = 0; i<n; i++) {
    int min_val = v[i];
    int min_idx = i;
    for(int j = i; j<n; j++) {
      if(v[j] < min_val) {
        min_val = v[j];
        min_idx = j;
      }
    }
    int temp = v[i];
    v[i] = min_val;
    v[min_idx] = temp;
  }
}

int main() {

  vector<int> arr = {64, 25, 12, 22, 11, 11};
  selection_sort(arr);

  for(int a: arr) {
    cout << a << ", ";
  }
  cout << "\n";
  return 0;
}