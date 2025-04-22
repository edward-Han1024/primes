unsigned long mod_exp(unsigned long base, unsigned long exp, unsigned long mod) {
    unsigned long result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

bool miller_rabin(unsigned long n, unsigned int k) {
    if (n == 2 || n == 3) return true;
    if ( n<=1 || !(n & 1) ) return false;

    // Write n-1 as d*2^r
    unsigned long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // Perform the test 'k' times
    for (int i = 0; i < k; i++) {
        // Choose a random number a in the range [2, n-2]
        unsigned long a = 2;
        // Compute a^d % n
        unsigned long x = mod_exp(a, d, n);
        if (x == 1 || x == n - 1) {
            continue; // This round is passed
        }
        // Continue squaring x and checking
        bool is_composite = true;
        for (int j = 0; j < r - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                is_composite = false;
                break;
            }
        }
        if (is_composite) {
            return false; // n is composite
        }
        a++;
    }

    return true; // n is probably prime
}