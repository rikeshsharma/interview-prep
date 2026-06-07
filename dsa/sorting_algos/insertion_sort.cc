// rikesh
#include <iostream>
#include <vector>
using namespace std;

void insertion_sort(vector<int> &v) {
  int n = v.size();

  for(int i = 0; i<n; i++) {
    
    for(int j = i+1; j>0 && j <n; j--) {
      if(v[j-1] > v[j]) {
        int temp = v[j-1];
        v[j-1] = v[j];
        v[j] = temp;
      } else {
        break;
      }
    }
  }
}

int main() {
  
  vector<int> arr = {64, 25, 12, 22, 11, 11, 5, 6};
  insertion_sort(arr);

  for(int a: arr) {
    cout << a << ", ";
  }
  cout << "\n";
  return 0;
}