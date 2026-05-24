#include <iostream>
using namespace std;

constexpr long long mod = (1e9 + 7);

long long binary_exponentiation(long long A, long long B, long long C) {
    if(A==0) return 0;
    if(B==0) return 1;

    int ans = 1;
    A %= C;
    while(B) {
        if(B%2) ans = (ans%C * A%C) %C ;
        A = (A%C * A%C) % C;
        B >>= 1;
    }
    return ans;
}

int main() {
    long long dividened, divisor;
    cout << "Calculate A^B mod C:\n";
    cout << " Enter dividened A: "; cin >> dividened;
    cout << " Enter power B: "; cin >> divisor;
    cout << " A^B mod C: " << binary_exponentiation(dividened, divisor, mod) << "\n";

    return 0;
}