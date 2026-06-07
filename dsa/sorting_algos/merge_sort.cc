// rikesh
#include <iostream>
#include <vector>
using namespace std;

void print(const vector<int>& v) {
  for(int a: v) {
    cout << a << ", ";
  }
  cout << "\n";
}
void merge(vector<int> &v, int l, int m, int h) {
  int i = l, j = m+1;
  vector<int> temp_arr;
  while(i<=m && j<=h) {
    if(v[i]<=v[j]){
      print(temp_arr);
      temp_arr.push_back(v[i]);
      i++;
    } else{
      print(temp_arr);
      temp_arr.push_back(v[j]);
      j++;
    }
  }
  while(i<=m){
    print(temp_arr);
    temp_arr.push_back(v[i]);
    i++;
  }
  while(j<=h) {
    print(temp_arr);
    temp_arr.push_back(v[j]);
    j++;
  }
  for(int i = l; i<=h; i++) {
    v[i] = temp_arr[i-l];
  }
}

void merge_sort(vector<int> &v, int i, int j) {
  print(v);
  if(i>=j) return;
  int mid = i + (j-i)/2 ;
  merge_sort(v, i, mid);
  merge_sort(v, mid+1, j);
  merge(v,i,mid,j);
}


int main() {

  vector<int> arr = {64, 23, 43, 5};
  print(arr);
  cout << "-----\n";
  merge_sort(arr, 0, arr.size()-1);
  cout << "-----\n";
  print(arr);
  return 0;
}