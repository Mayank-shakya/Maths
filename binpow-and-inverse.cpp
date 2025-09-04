#include<bits/stdc++.h>
using namespace std;

#define int long long

ll binpowItr(ll a, ll x, ll p)  //(a^x)%p
{
  ll n, ans = 1;
  // prod= (a^(2^p1))
  while (x) {
    if (x % 2) {
      ans = ((ans % p) * (a % p)) % p;
    }
    a = ((a % p) * (a % p)) % p;
    x = x / 2;
  }
  return ans;
}

int binpow(int a,int b,int m){
    if(b==0)return 1;
    if(b%2==1){
        return a*binpow(a,b-1,m)%m;
    }
    else{
        int temp = binpow(a,b/2,m);
        return temp*temp%m;
    }
}
int inv(int a,int p){
    return binpow(a,p-2,p);
}

int f(int x,int n,int m){
    if(x==1)return (n+1)%m;
    if(n%2==0){
        return (1+ x * f(x,n-1,m))%m;
    }else{
        int val = (n+1)/2;
        int temp = (1+binpow(x,val,m))%m;
        return temp * f(x,n/2,m) % m;
    }
}

const int MOD = 1e9+7;

void solve(){
    int a,b,c,d,e,f,g;
    cin>>a>>b>>c>>d>>e>>f>>g;
    
    int num = (b-c)%MOD;
    num = binpow(num,d,MOD);
    num = num * inv(e,MOD) % MOD;

    int temp = (f*g)%MOD;
    num = (num-temp)%MOD;
    num = (a+num)%MOD;

    cout<<((num%MOD)+MOD)%MOD<<endl;
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t=1;
    //cin>>t;
    while(t--){
        solve();
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////

// Function to compute power of prime p in n!
int powerOfPInFactorial(int n, int p) { // O(log_p(n)) 
    int count = 0; 
    while (n >0) {
        count += n / p; // count multiples of p, p^2, p^3, ...
        n /= p;
    }
    return count; // total count of prime p in n!
}

// Example usage
int main() {
    int n, p;
    cin >> n >> p;
    cout << powerOfPInFactorial(n, p) << "\n";
}

/*
Notes:
- Formula: power of prime p in n! = floor(n/p) + floor(n/p^2) + floor(n/p^3) + ...
- Each term counts how many multiples of p, p^2, p^3, ... contribute to the factorial.
- Time Complexity: O(log_p(n))  (since n gets divided by p each loop).
- Use Cases:
    - Counting trailing zeros (use p=5 for base 10, combine with p=2).
    - Factorization of n! in competitive programming / combinatorics.
- Works up to n ~ 1e9 easily.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////
