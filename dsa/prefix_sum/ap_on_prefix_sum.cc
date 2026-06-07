/*
Your are given a fixed array A of size N, You need to answer Q queries of the
form: ? L R -> find the value of following expression modulo 1e9+7. 
A[L] + 2*A[L+1] + 3*A[L+2] + ... + (k-L+1)*A[k] + ... + (R-L+1)*A[R]
*/

// rikesh
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

using ll = long long;
constexpr ll mod = (1e9 + 7);

int calc(vector<int> &a, int l, int r) {
  int ans = 0;
  
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // code below
  vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  cout << calc(arr, 2, 7);
  return 0;
}