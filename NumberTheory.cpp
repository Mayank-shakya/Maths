

// Multiples of x in [l, r] using only floor

// Largest multiple of x ≤ r:
// m = floor(r / x) * x

// Smallest multiple of x ≥ l:
// m = floor((l + x - 1) / x) * x
// (this is equivalent to ceil(l / x) * x, but written with floor)

// Condition that a multiple exists in [l, r]:
// floor((l + x - 1) / x) * x <= r


/////////////////////////////////////

// max factors of a number is max 2sqrt(n) n=a*b atleast one of a or b is ≤ sqrt(n) 

// max primes of a number is max log n base 2 

//////////////////////////////////////////////////////////////////////////////////////////////////

60 = 2^2 ⋅ 3^1 ⋅ 5^1
48 = 2^4 ⋅ 3^1

HCF = 2^2 ⋅ 3^1 = 12
LCM = 2^4 ⋅ 3^1 ⋅ 5^1 = 240

Rule for GCD and LCM using prime powers:

Let
A = ∏ p_i^a_i
B = ∏ p_i^b_i

GCD(A, B) = ∏ p_i^min(a_i, b_i)   // take minimum exponent for each prime
LCM(A, B) = ∏ p_i^max(a_i, b_i)   // take maximum exponent for each prime

//////////////////////////////////////////////////////////////////////////////////////////////////

int gcd(int a, int b) { //  O(log(min(a,b))), Euclidean algorithm  //  0 ≤ gcd(a, b) ≤ min(|a|, |b|) 
// - gcd is 0 only when both numbers are 0.Otherwise gcd is ≥ 1.

    if (b == 0) return a;
    return gcd(b, a % b);
}

////////////////////////////////////////////////////////////////////////////////////////////////

int gcd_steps(int a, int b) { // counts steps in Euclidean algorithm, O(log(min(a,b))),
    
    int steps = 0;
    while (a && b) {
        if (a > b) {
            steps += a / b;  // how many times we reduce a by b
            a %= b;
        } else {
            steps += b / a;  // how many times we reduce b by a
            b %= a;
        }
    }
    cout << "Steps = " << steps << endl;
    return a + b; // since one becomes 0, the other is gcd
}

int main() {
    int a = 48, b = 18;
    int g = gcd_steps(a, b);
    cout << "GCD = " << g << endl;
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

int lcm(int a, int b) { //  O(log(min(a,b))), Euclidean algorithm // 0 ≤ lcm(a, b) ≤ |a * b|
    // If gcd(a, b) = 1 → lcm(a, b) = |a·b|. 
//     LCM properties and range:

// 1. lcm(a, b) ≥ max(|a|, |b|)
// 2. lcm(a, b) ≤ |a * b|
// 3. lcm(a, b) = 0 if any input = 0

    if (a == 0 || b == 0) return 0; // lcm is 0 if either number is 0.
    return (a / gcd(a, b)) * b; // to prevent overflow
}

////////////////////////////////////////////////////////////////////////////////////////////////

void primeFactor(int n, vector<int> &factors) { // O(√n) n<=1e12  // returns prime factors with multiplicity
    // Example: 60 = 2^2 * 3^1 * 5, so factors = {2, 2, 3, 5}
    // If you want distinct prime factors, use a set instead of a vector.
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) {
        factors.push_back(n);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> distinctPrimeFactors(long long n) {
    vector<int> f;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            f.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> divisors[1000100];

void pre() {
    for (int i = 1; i <= 1000000; i++) { // O(n log n), n = 1e6, precomputation, fills divisors array, 
    // divisors[i] contains all divisors of i in sorted order
        for (int j = i; j <= 1000000; j += i) {
            divisors[j].push_back(i);
        }
    }
}

bool is_prime(int x) {
    if (divisors[x].size() == 2) return 1; // O(1)
    else return 0;
}

void factors2(int x) {
    for (auto v : divisors[x]) { // O(d(x)) where d(x) is number of divisors of x worse case O(√x)
        cout << v << " ";  // prints all divisors of x in sorted order 
    }
    cout << endl;
}
// O(√n) for a single number n <= 1e12
// O(n log n) for all numbers from 1 to n, n <= 1e6 // (using pre() and factors2())  



///////////////////////////////////////////////////////////////////////////////////////////////////

int prime[1000100];

void sieve() { // Sieve of Eratosthenes, O(n log log n), n = 1e6
    // After calling this function, prime[i] will be 1 if i is prime, else 0, 
    prime[0] = prime[1] = 0; // 0 and 1 are not prime numbers 
    for (int i = 2; i <= 1000000; i++) {
        prime[i] = 1;
    }

    for (int i = 2; i <= 1000000; i++) {
        if (prime[i]) {
            for (int j = 2 * i; j <= 1000000; j += i) {
                prime[j] = 0;  // mark multiples of i as not prime
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

int spf[1000100];  // stores smallest prime factor

void spfFill() {// O(n log log n), n = 1e6
    // After calling this function, spf[i] will contain the smallest prime factor of i
    spf[0] = spf[1] = -1; // 0 and 1 do not have prime factors

    for (int i = 2; i <= 1000000; i++) {
        spf[i] = i;   // initialize
    }

    for (int i = 2; i * i <= 1000000; i++) {
        if (spf[i] == i) {  // i is prime
            for (int j = i * i; j <= 1000000; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;  // set smallest prime factor
                }
            }
        }
    }
}

void primefactors2(int x) { // log x , x <= 1e6 once spfFill() is called
    // prints prime factors of x along with their powers

    while (x != 1) {
        int i = spf[x];   // smallest prime factor of x
        int ipow = 0;
        while (x % i == 0) {
            ipow++;
            x /= i;
        }
        cout << i << " " << ipow << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////

const int N = 2e5 + 10;

int hsh[N];
int multiples_ct[N]; // multiples_ct[i] = count of numbers in input array that are multiples of i

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        hsh[x]++;   // count frequency of numbers
    }

    for (int i = 1; i < N; ++i) { // O(N log N) N=2e5
        multiples_ct[i] = 0; // initialize 

        for (int j = i; j < N; j += i) {
            multiples_ct[i] += hsh[j];  // count how many multiples of i are present in input array 
        }
    }
    // Now multiples_ct[i] contains count of numbers in input array that are multiples of i
    // j ismultiples of i and i is divisor of j
    // multiples_ct[i] = how many numbers in input are multiples of i
/

    int q;
    cin >> q;
    while (q--) {
        int p;
        cin >> p;
        cout << multiples_ct[p] << endl;  // answer queries
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

const int N = 200'010;
int hsh[N];
int canRemove[N]; // canRemove[i] = 1 if i can be removed, else 0 // i.e., i is a power of some prime present in input array 

// call this AFTER filling hsh[]
void markCanRemove() { // O(N log N) N=2e5
    // marks canRemove[i] = 1 if i is a power of some prime present in input array
    // i.e., i = p^k for some prime p present in input array and k >= 1
    // else canRemove[i] = 0        
    for (int i = 2; i < N; ++i) { // i is potential prime, time complexity O(N log N)
        if (hsh[i]) { // i is present in input array then only mark all its powers else skip
            for (long long j = i; j < N; j *= i) {
                canRemove[j] = 1;  // mark all powers of i as removable, j can be int as j < N, but to prevent overflow use long long, 
            }
        }
    }
}


