int fact[1000100];
int invfact[1000100];
void pre(){
    fact[0]=1;
    for(int i=1;i<=1000000;i++)
        fact[i] = 1LL*i*fact[i-1]%MOD;
    invfact[1000000] = inv(fact[1000000],MOD);
    for(int i=1000000-1;i>=0;i--){
        invfact[i] = 1LL*invfact[i+1]*(i+1)%MOD;
    }
}

int ncr(int n,int r){  // for r,n 10^6 with prime mod O(1)
    if(r<0||r>n) return 0;
    int ans = fact[n];
    ans = 1LL*ans*invfact[n-r]%MOD;
    ans = 1LL*ans*invfact[r]%MOD;
    return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////

// Computes nCr for small r (r <= 30) and large n (n up to 10^18) in O(r) time without any modulus.
// Use this when n is too large to precompute factorials.
long long ncr(int n, int r) {  // for r 30 no mod // n (≤ 10^6) if no modulus is involved. O(r)
    if (r > n || r<0) return 0;
    long long ans = 1;
    for (int i = 0; i < min(r, n - r); i++) {
        ans *= (n - i);
        ans /= (i + 1);
    }
    return ans;
}


////////////////////////////////////////////////////////////////////////////////////////////////

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000; // example non-prime modulus
const int MAXN = 500; // adjust depending on constraints

long long C[MAXN+1][MAXN+1];

void precompute() {  // Pascal DP method is only practical for small n (≤ 2000–5000), but works for any modulus, not just primes, O(n^2, mod), no inv, no fact, no invfact, 
    // Pascal DP method is only practical for small n (≤ 2000–5000), but works for any modulus
    //  and r (≤ n) in O(n^2) time and O(n^2) space.
    //  It does not require the modulus to be prime, and does not involve factorials or modular inverses.
    //  This method is efficient for small values of n and r, but becomes impractical for large n due to its O(n^2) time and space complexity.

    for (int n = 0; n <= MAXN; n++) {
        C[n][0] = C[n][n] = 1 % MOD;
        for (int r = 1; r < n; r++) {
            C[n][r] = (C[n-1][r-1] + C[n-1][r]) % MOD;
        }
    }
}

/////////

 #define ll long long
 const int M=1e9;

vector<int> solve(int n) { // pascal dp method O(n^2) time and O(n) space
    vector<int>prev(n+1,0);
    prev[0]=1;
    
    
    for(int row=1;row<=n;row++){
        vector<int>fwd(n+1,0);
        
        for(int j=0;j<n+1;j++){
            fwd[j]=prev[j]%M;
            if(j-1>=0)fwd[j]=(fwd[j]%M + prev[j-1]%M)%M;
            
        }
        
        prev=fwd;
    }
    return prev;
}
////////////////////////////////////////////////////////////////


long long ncr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return C[n][r];
}

int main() {
    precompute();
    int n, r;
    cin >> n >> r;
    cout << ncr(n, r) << endl;
    return 0;
}

tc and max n,r

