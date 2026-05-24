// rikesh
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

using ll = long long;
constexpr ll mod = (1e9 + 7);

ll gcd(ll a, ll b) {
  if (a == 0) return abs(b);
  if (b == 0) return abs(a);
  a = abs(a);
  b = abs(b);

  while (b != 0) {
    a %= b;
    swap(a, b);
  }
  return a;
}

vector<bool> sieve(int n) {
  vector<bool> is_prime(n+1, true);
  is_prime[0] = false, is_prime[1] = false;
  for(int i = 2; i*i <= n; i++) {
    if(is_prime[i]) {
      for(int j = i*i; j<=n; j+=i) {
        is_prime[j] = false;
      }
    }
  }
  return is_prime;
}

ll binary_exponentiation(ll a, ll b, ll c) {
  if(c == 1) return 0;
  a %= c;
  ll  ans = 1;
  while(b) {
    if(b&1) ans =  (1LL*ans*a) % c;
    a = (1LL*a*a) % c;
    b >>= 1;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // code below

  return 0;
}