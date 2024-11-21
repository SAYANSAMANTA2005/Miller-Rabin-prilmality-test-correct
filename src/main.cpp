

#include <iostream>
#include <vector>
#include <chrono> // For time measurement
using namespace std;

// Function to perform modular multiplication safely
long long modularMultiply(long long a, long long b, long long mod) {
    long long result = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1)
            result = (result + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return result;
}

// Function to perform modular exponentiation: (base^exp) % mod
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = modularMultiply(result, base, mod);
        exp /= 2;
        base = modularMultiply(base, base, mod);
    }
    return result;
}

// Deterministic Miller-Rabin test for numbers <= 10^18
bool millerRabin(long long n, long long a) {
    if (n % a == 0)
        return false;

    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    long long x = modularExponentiation(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1) {
        x = modularMultiply(x, x, n);
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

// Primality test for numbers <= 10^18
bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    // Deterministic bases for numbers <= 10^18
    vector<long long> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (long long a : bases) {
        if (a >= n) break;
        if (!millerRabin(n, a))
            return false;
    }

    return true;
}

int main() {
    long long num ;
    cout << "enter the number: " << endl;
    cin>>num;
    

    // Start time measurement
    auto start = chrono::high_resolution_clock::now();

    if (isPrime(num))
        cout << num << " is a prime number.\n";
    else
        cout << num << " is not a prime number.\n";

    // End time measurement
    auto end = chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Time taken to execute: " << duration << " microseconds.\n";

    return 0;
}