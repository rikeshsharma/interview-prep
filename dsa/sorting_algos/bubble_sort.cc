// rikesh
#include <iostream>
#include <vector>
using namespace std;

void bubble_sort(vector<int> &v) {
  int n = v.size();
  for(int i = 0; i<n; i++) {
    for(int j = 0; j < n-i-1; j++) {
        if(v[j] > v[j+1]) {
          int temp = v[j];
          v[j] = v[j+1];
          v[j+1] = temp;
        }
    }
    for(int a: v) {
      cout << a << ", ";
    }
    cout << "\n";
  }
}

void print(const vector<int>& v) {
  for(int a: v) {
    cout << a << ", ";
  }
  cout << "\n";
}

int main() {

  vector<int> arr = {64, 25, 12, 22, 11, 11};
  print(arr);
  cout << "-----\n";
  bubble_sort(arr);
  cout << "-----\n";
  print(arr);
  return 0;
}